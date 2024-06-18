#include <stdio.h>
#include <raylib.h>

#define X 1000
#define Y 800 

#define scale 3

#define R 8.31
#define n 2.5

int clicked(Vector2 mouse_pos, Rectangle button) {
	if (CheckCollisionPointRec(mouse_pos, button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return 1;
	else if (CheckCollisionPointRec(mouse_pos, button) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) return 2;
}

float isochoric(bool check[], float temp, float vol, float press, float dtemp) {
	if (check[0] && check[1]) {
		DrawText("ISOCHORIC TRANSFORMATION", 10,770,20,WHITE);
		return (temp/(temp-dtemp))*press;
	}
	return press;
}

float isothermic(bool check[], float temp, float vol, float press, float dvol) {
	if (check[0] && check[1]) {
		DrawText("ISOTHERMIC TRANSFORMATION", 10,770,20,WHITE);
		return ((vol+dvol)/vol)*press;
	}
	return press;
}

float isobar(bool check[], float temp, float vol, float press, float dtemp) {
	if (check[0] && check[1]) {
		DrawText("ISOBAR TRANSFORMATION", 10,770,20,WHITE);
		return (temp/(temp-dtemp))*vol;
	}
	return vol;
}


int main() {
	const int width = 100*scale;
	const int height = 20*scale;
	const int depth = 90*scale;
	const float central_y = Y/2-(height+depth)/2;

	float temp = 220.0;
	float press = 1.01325e5;
	float vol = 1;
	float area = 2;

	int MX = GetMouseX();
	int MY = GetMouseY();

	// Buttons color
	Color button_col[] = {RED, RED, RED};

	bool draw_flame = false;
	float vel = 0.0f;

	// Temp, press, vol
	bool check_isochoric[] = {false, false};
	bool check_isotherm[] = {false, true};
	bool check_isobar[] = {false, false};

	InitWindow(X,Y, "Piston");
	SetTargetFPS(60);

	Rectangle piston = {X/2-width/2, central_y, width, height};
	Rectangle cilinder = {piston.x, piston.y, width, height + depth};

	Image flame_img = LoadImage("flame.png");
	ImageResize(&flame_img, 10*scale,20*scale);
	Texture2D flame_tex = LoadTextureFromImage(flame_img);
	UnloadImage(flame_img);
	

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		float h = vol / area;
		float dvol = vel/267;
		float dtemp = 0.5/26.7;

		printf("pist %f, centr %f\n", piston.y+0.4, central_y - 0.2);
		if (piston.y < central_y + depth - 10 && piston.y > central_y - 0.2) {
			piston.y += vel;
			vol -= dvol;
		}

		if (draw_flame) {
			DrawTexture(flame_tex, X/2-10, central_y + depth + height + 20, WHITE); // Flame
			DrawText("FLAME", X/2-30, central_y + depth + height + 120, 20,WHITE);
			if (temp <= 500.f) temp += dtemp;
		}
		else {
			DrawRectangleLinesEx((Rectangle){X/2-width/2-30*scale, Y/2-width/2-30*scale-10, width+60*scale, width+60*scale+10}, 30*scale, (Color){0,155,255,60});
			DrawText("THERMOSTATIC BATH", X/2-120, central_y + depth + height + 120, 20,WHITE);
		}

		// Draw gas in the chamber
		DrawRectangle(piston.x, piston.y+10, width, central_y + depth + height - piston.y-10, (Color){255,255,0,150});

		// Draw piston and cilinder
		DrawRectangleRounded(piston, 0.4, 10, WHITE);
		DrawRectangleLinesEx(cilinder, 4, RED);

		if (check_isotherm[0] && check_isotherm[1]) {
			press = isothermic(check_isotherm, temp, vol, press, dvol);
		} if (check_isochoric[0] && check_isochoric[1]) {
			press = isochoric(check_isochoric, temp, vol, press, dtemp);
		}

		/* float changing_vol = isobar(check_isobar, temp, vol, press, dtemp); */
		/* float dvol1 = -(vol - changing_vol)*2000; */
		/* if (check_isobar && !check_isotherm) { */
		/* 	piston.y -= vel; */
		/* 	vol += dvol; */
		/* } */

		DrawText(TextFormat("Temperature: %.2f K", temp), 10,10,20,WHITE);
		DrawText(TextFormat("Pressure: %.2f Pa", press), 10,30,20,WHITE);
		DrawText(TextFormat("Volume: %.2f m3", vol), 10,50,20,WHITE);

		Vector2 mouse_pos = GetMousePosition();

		// Button to block the piston
		DrawText("Block the piston:", X-270,10,20,WHITE);

		Rectangle button0 = {945, 12, 15, 15};

		bool check_no_transf = (check_isotherm[0] && check_isochoric[1]);

		if (clicked(mouse_pos, button0) == 1 || check_no_transf) {
			button_col[0] = GREEN;
			button_col[2] = RED;
			vel = 0;
			check_isochoric[0] = true;
			check_isotherm[0] = false;
			check_isobar[0] = false;
		}
		else if (clicked(mouse_pos, button0) == 2) {
			button_col[0] = RED;
			check_isochoric[0] = false;
			check_isobar[0] = true;
		}

		DrawRectangleRounded(button0, 0.8, 40, button_col[0]);


		// Button to heat up the gas
		DrawText("Heat the gas:", X-270,30,20,WHITE);

		Rectangle button1 = {945, 32, 15, 15};

		if (clicked(mouse_pos, button1) == 1) {
			button_col[1] = GREEN;
			draw_flame = true;
			check_isochoric[1] = true;
			check_isotherm[1] = false;
			check_isobar[1] = true;
			if (check_isobar && !check_isochoric[0]) vel = -0.2f;
		}
		else if (clicked(mouse_pos, button1) == 2) {
			button_col[1] = RED;
			draw_flame = false;
			check_isochoric[1] = false;
			check_isotherm[1] = true;
			check_isobar[1] = false;
			if (check_isobar) vel = 0.f;
		}

		DrawRectangleRounded(button1, 0.8, 40, button_col[1]);

		// Button to compress the gas
		DrawText("Compress the gas:", X-270,50,20,WHITE);

		Rectangle button2 = {945, 55, 15, 15};

		if (clicked(mouse_pos, button2) == 1) {
			button_col[2] = GREEN;
			button_col[0] = RED;
			vel = 0.2f;
			check_isochoric[0] = false;
			check_isotherm[0] = true;
			check_isobar[0] = false;
		}
		else if (clicked(mouse_pos, button2) == 2) {
			button_col[2] = RED;
			vel = 0;
			check_isotherm[0] = false;
			check_isobar[0] = true;
		}

		DrawRectangleRounded(button2, 0.8, 40, button_col[2]);

		EndDrawing();
	}

	UnloadTexture(flame_tex);
	CloseWindow();
	return 0;
}
