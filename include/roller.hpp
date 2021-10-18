#ifndef _ROLLER_H_
#define _ROLLER_H_

// ----------- SETTINGS FOR AUTO LIFT CONTROL -------
// go here

// Set voltage of roller motor without programmed stop, takes int from -127 to 127
void rollerMove(int voltage);

// Sets voltage of roller motor to 0
void rollerStop();

//void rollerSpinForEncoder(int speed, int encDegrees); // move roller forward or backward in given increment at speed in RPM

#endif
