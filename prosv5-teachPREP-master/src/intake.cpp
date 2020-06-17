#include "main.h"    // includes API.h and other headers
#include "intake.h" // ensures that the corresponding header file (intake.h) is included
#include "portdef.h" // All port defintions on the cortex need to be included

pros::Motor intakeMotor(INTAKE_MOTOR_PORT);

void intakeForward(int speed){
  intakeMotor.move_velocity(speed);
}

void intakeBackward(int speed) {
  intakeMotor.move_velocity(-speed);
}

void intakeStop(int speed) {
  intakeMotor.move_velocity(0);
}
