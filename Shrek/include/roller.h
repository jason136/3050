#ifndef _ROLLER_H_
#define _ROLLER_H_

// ----------- SETTINGS FOR AUTO LIFT CONTROL -------

void rollerForward(int speed);

void rollerBackward(int speed);

void rollerStop(int speed);

void rollerLock(int speed);
/*
void rollerSpinForEncoder(int speed, int encDegrees); // move roller forward or backward in given increment at speed in RPM
*/
#endif
