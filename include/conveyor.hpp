#ifndef _CONVEYOR_H_
#define _CONVEYOR_H_

// ----------- SETTINGS FOR AUTO LIFT CONTROL -------
// go here

// Set voltage of conveyor motor without programmed stop, takes int from -127 to 127
void conveyorMove(int voltage);

// Sets voltage of conveyor motor to 0
void conveyorStop();

//void conveyorSpinForEncoder(int speed, int encDegrees); // move roller forward or backward in given increment at speed in RPM

#endif
