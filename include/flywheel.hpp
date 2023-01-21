#ifndef _LIFT_H_
#define _LIFT_H_

#include "api.h"

// spin the Fhywheel, range: +-600
void spinFlywheel(bool pressed);

void setFlywheelSpeed(int speed);

void flywheelPIDTask(void * param);

// stop the flywheel with the given brake mode
void stopFlywheel();

void resetFlywheelEncoders();

// Get the current lift lock mode of the break
pros::motor_brake_mode_e_t getliftLockMode();

void displayFlywheelData();

void toggleVariableFlywheel(bool input);

#endif
