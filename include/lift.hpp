#ifndef _LIFT_H_
#define _LIFT_H_

#include "api.h"

// ----------- SETTINGS FOR AUTO LIFT CONTROL -------
#define LIFT_FULL_RETRACT 0
#define LIFT_MAX_HEIGHT 550
#define LIFT_LEVEL_LOW 100
#define LIFT_LEVEL_HIGH 400

void moveLift(int LTop, int LBottom, int RTop, int RBottom);

// lock the front lift where it is right now....
void liftLock(pros::motor_brake_mode_e_t brakeType, bool left, bool right);

void resetLiftEncoders();

// Get the current lift lock mode of the break
pros::motor_brake_mode_e_t getliftLockMode();

// Control method for differential mechanism on lift
void liftComplex(int right, int left);

#endif
