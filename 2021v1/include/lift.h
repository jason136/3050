#ifndef _LIFT_H_
#define _LIFT_H_

// ----------- SETTINGS FOR AUTO LIFT CONTROL -------
#define LIFT_FULL_RETRACT 0
#define LIFT_MAX_HEIGHT 550
#define LIFT_LEVEL_LOW 100
#define LIFT_LEVEL_HIGH 400


void liftSetZero(int speed);

void liftRaise(int speed, int level);  // 0 for full retract. 1 for shorter tower. 2 for higher tower

void liftRaiseForEncoder(int speed, int encDegrees); // more left up or down in given increment at speed in RPM

void liftEncoderValue();

void liftRaiseManual(int speed); // manual raise the lift up and down

void liftLock();

void liftLockMode();

#endif
