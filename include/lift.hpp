#ifndef _LIFT_H_
#define _LIFT_H_

#include "api.h"

// ----------- SETTINGS FOR AUTO LIFT CONTROL -------
#define LIFT_FULL_RETRACT 0
#define LIFT_MAX_HEIGHT 550
#define LIFT_LEVEL_LOW 100
#define LIFT_LEVEL_HIGH 400

// Set voltage of front lift without programmed stop, takes int from -127 to 127
void frontLiftMove(int voltage);

// lock the front lift where it is right now....
void frontLiftLock();

// Set voltage of back lift without programmed stop, takes int from -127 to 127
void backLiftMove(int voltage);

// lock the back lift where it is right now....
void backLiftLock();

// Resets encoders of the lift Motor
void liftResetEncoder();

// Move lift to specific degree position at given voltage
void liftRaiseForEncoder(int voltage, int encDegrees);

// Move lift to specific location specified by level parameter
// 0 -- fully retracted back to 0
// 1 -- raise to lower pole height
// 2 -- raise to upper pole height
// Speed determined by voltage parameter
void liftRaise(int voltage, int level);

// Get the current lift lock mode of the break
pros::motor_brake_mode_e_t getliftLockMode();

#endif
