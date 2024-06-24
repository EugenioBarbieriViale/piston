# Graphical interface of a piston
Through this program written in C using the library [raylib](https://www.raylib.com/) you will be able to move a piston to compress a perfect gas, heat it with a flame and put it in a thermic bath to mantain costant its temperature.
In this way you will be able to visualize the transformations to which a perfect gas can be subjected.

When a perfect gas is compressed or heated, its macroscopic characteristics (pressure, volume and temperature) change. The equation that describes this changes is the following: **pV = nRT** (*with R = 8.31 J/(mol)K*). More info [here](https://en.wikipedia.org/wiki/Ideal_gas_law).

Here it is a screenshot:

![piston](https://github.com/EugenioBarbieriViale/piston/assets/82298389/46118c8e-6cd1-48aa-a1ae-50e45c7c03a5)
# How to use it
There is a command panel at the top right corner. Green means enabled, red means disabled. To enable right-click, to disable left-click. It is possible to display only the following three transformations:
- ISOCHORIC: the piston is blocked and the flame heats the gas. The pressure starts to increase
- ISOTHERM: the piston compresses the gas, which is mantained at costant temperature with the thermic bath. The pressure starts to increase
- ISOBAR: the flame heats the gas. Since the piston is free to move and the gas starts expanding, it goes up. The volume starts to increase
