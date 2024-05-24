#include <stdio.h>
#include <raylib.h>

#define X 1000
#define Y 800 

#define scale 3

// Tipi di trasformazioni:
// ISOTERMA: temperatura costante -> bagno termico
// ISOCORA: volume costante -> fiamma che scalda e pistone bloccato
// ISOBARA: pressione costante

int clicked(Vector2 mouse_pos, Rectangle button) {
	if (CheckCollisionPointRec(mouse_pos, button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return 1;
	else if (CheckCollisionPointRec(mouse_pos, button) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) return 2;
}

float isochoric(float ) {
		
}


int main() {
	const int width = 100*scale;
	const int height = 20*scale;
	const int depth = 90*scale;
	const float central_y = Y/2-(height+depth)/2;

	float temp = 300.0;
	float press = 1.01325e5;
	float vol = 0.01;

	int MX = GetMouseX();
	int MY = GetMouseY();

	// Buttons color
	Color button_col[] = {RED, RED, RED};

	bool draw_flame = false;
	float vel = 0.0f;


	InitWindow(X,Y, "Pistone");
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

		if (piston.y < central_y + depth - 10) piston.y += vel;

		if (draw_flame) {
			DrawTexture(flame_tex, X/2-10, central_y + depth + height + 20, WHITE); // Flame
			DrawText("FLAME", X/2-30, central_y + depth + height + 120, 20,WHITE);
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

		// Draw text
		DrawText(TextFormat("Temperature: %.2f K", temp), 10,10,20,WHITE);
		DrawText(TextFormat("Pressure: %.2f Pa", press), 10,30,20,WHITE);
		DrawText(TextFormat("Volume: %.2f m3", vol), 10,50,20,WHITE);

		// Options
		Vector2 mouse_pos = GetMousePosition();

		// Button to block the piston
		DrawText("Block the piston:", X-270,10,20,WHITE);

		Rectangle button0 = {945, 12, 15, 15};

		if (clicked(mouse_pos, button0) == 1) {
			button_col[0] = GREEN;
			button_col[2] = RED;
			vel = 0;
		}
		else if (clicked(mouse_pos, button0) == 2) {
			button_col[0] = RED;
		}

		DrawRectangleRounded(button0, 0.8, 40, button_col[0]);


		// Button to heat up the gas
		DrawText("Heat the gas:", X-270,30,20,WHITE);

		Rectangle button1 = {945, 32, 15, 15};


		if (clicked(mouse_pos, button1) == 1) {
			button_col[1] = GREEN;
			draw_flame = true;
		}
		else if (clicked(mouse_pos, button1) == 2) {
			button_col[1] = RED;
			draw_flame = false;
		}

		DrawRectangleRounded(button1, 0.8, 40, button_col[1]);

		// Button to compress the gas
		DrawText("Compress the gas:", X-270,50,20,WHITE);

		Rectangle button2 = {945, 55, 15, 15};

		if (clicked(mouse_pos, button2) == 1) {
			button_col[2] = GREEN;
			button_col[0] = RED;
			vel = 0.2f;
		}
		else if (clicked(mouse_pos, button2) == 2) {
			button_col[2] = RED;
			vel = 0;
		}

		DrawRectangleRounded(button2, 0.8, 40, button_col[2]);

		EndDrawing();
	}

	UnloadTexture(flame_tex);
	CloseWindow();
	return 0;
}

