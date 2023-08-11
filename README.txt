//IMPORTANT
There exist two versions of the project. The board and the simulation versions. This is because the screen of the LPC2478 will still produce scanlines while the LED ladder is being driven, DESPITE using the recommended ladder LEDs. Our current peripherals are mapped to:
Blind 1	- LED ladder P2.6
Blind 2 - LED ladder P2.7
Blind 3 - LED ladder P2.8
Sprinkler - LED ladder P2.1
Light 1 - right RGB LED
Light 2 - left RGB LED


The simulation version is for Jonah's nyansim. It is fully functional with the exception of the onboard clock, which is not supported, so a timer with a delay is used instead, which is very inefficient because it eats up polling time but at the point im too tired to care. This will provide a much better interface for checking the capabilities of the system.

The board version is an exact copy of the simulation but implements the on-board clock to keep track of time. This version was included for the sake of completeness.



//IMPORTANT IMPLEMENTATION LOCATIONS
main.c | acts as a driver for the rest of the modules, initialises and calls everything else.
profile.h | defines structs to be used in the system
data.c | holds data for automation task
automation.c | functions for driving the daughter board and the light sensor
gui.c | functions for drawing the screen and interpreting presses
drawtime.c | functions for drawing the clock onto the screen
timer.c |functions related to the timers and the on-board clock

