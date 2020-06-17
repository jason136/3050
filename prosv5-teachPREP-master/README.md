# prosv5-teachPREP

This is a prototype project for the PREP V5 based robot.  It is setup where the code is organized by physical sub system.  Each subsystem has it's own header (.h) and source (.cpp) file pair.

The file portdef.h is the critical V5 port definition setup file, defining all devices plugged into the V5 brain.

Please note that any motor must be setup in initialize() to ensure that the proper gearset, directions and encoder units are set.

For testing purposes the opcontrol() function contains a way to force autonomous to run, and select which routine runs - as normally would be selected via the LCD display.

The code in chassis.c (combined with chassis.h) is critical for movements.  It relies on accurate measurement of the wheel diameter, as well as the chassis width as measured between left front wheel and right back wheel - representing the the turn circle when the robot pivot turns.

Further the function used for forward movement assumes the distance to be input in inches.  All speeds are in RPM in relationship to the motor cartridges.  red - +-100RPM, green - +-200RPM, blue - +- 600RPM.
