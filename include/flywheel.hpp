#ifndef _LIFT_H_
#define _LIFT_H_

#include "api.h"

void spinFlywheel(int speed);

// lock the front lift where it is right now....
void stopFlywheel(pros::motor_brake_mode_e_t brakeType);

void resetFlywheelEncoders();

// Get the current lift lock mode of the break
pros::motor_brake_mode_e_t getliftLockMode();

// Control method for differential mechanism on lift
// void liftComplex(int right, int left);

#endif
