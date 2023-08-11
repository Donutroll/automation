//IMPORTANT
There exist two versions of the project. The board and the simulation versions. 
The simulation version is for Jonah's nyansim. It is fully functional with the exception of the onboard clock, which is not supported, so a timer with a delay is used instead, which is very inefficient because it eats up polling time but at the point im too tired to care. This will provide a much better interface for checking the capabilities of the system.

The board version is an exact copy of the simulation but implements the on-board clock to keep track of time. This version was included for the sake of completeness and will function on the board, but with many strange errors.

This is because the screen of the LPC2478 will still produce scanlines while the LED ladder is being driven, DESPITE using the recommended ladder LEDs. Our current peripherals are mapped to:

Blind 1	- LED ladder P2.6
Blind 2 - LED ladder P2.7
Blind 3 - LED ladder P2.8
Sprinkler - LED ladder P2.1
Light 1 - right RGB LED
Light 2 - left RGB LED

(assumes blinds are open when led is on)
There are two modes of operation, automation and manual. Transitioning between modes will turn off what was on in the previous mode. Tranisitioning between modes uses the "manual" button.
automation - peripherals will update every hour according to a fixed schedule, BUT the lights will update based on what the light sensor reads
manual - peripherals will only update when user presses the onscreen buttons



//IMPORTANT IMPLEMENTATION LOCATIONS
main.c | acts as a driver for the rest of the modules, initialises and calls everything else.
profile.h | defines structs to be used in the system
data.c | holds data for automation task
automation.c | functions for driving the daughter board and the light sensor
gui.c | functions for drawing the screen and interpreting presses
drawtime.c | functions for drawing the clock onto the screen
timer.c |functions related to the timers and the on-board clock

