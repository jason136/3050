#ifndef _LIFT_H_
#define _LIFT_H_

#include "api.h"

// ----------- SETTINGS FOR AUTO LIFT CONTROL -------
#define LIFT_FULL_RETRACT 0
#define LIFT_MAX_HEIGHT 550
#define LIFT_LEVEL_LOW 100
#define LIFT_LEVEL_HIGH 400

// Resets encoders of the lift Motor
void liftResetEncoder();

// Move lift to specific degree position at given speed in RPM
void liftRaiseForEncoder(int speed, int encDegrees);

// Set voltage of lift without programmed stop, takes int from -127 to 127
void liftMove(int voltage);

// Set lift to braked
void liftLock();

// Get the current lift lock mode of the break
pros::motor_brake_mode_e_t getliftLockMode();

#endif
