#include "main.h"
#include "roller.h"
#include "portdef.h"

pros::Motor rightRollerMotor(RIGHT_ROLLER_MOTOR);
pros::Motor leftRollerMotor(LEFT_ROLLER_MOTOR);

void rollerForward(int speed) {
  rightRollerMotor.move_velocity(speed);
  leftRollerMotor.move_velocity(speed);
}

void rollerBackward(int speed) {
  rightRollerMotor.move_velocity(-speed);
  leftRollerMotor.move_velocity(-speed);
}

void rollerStop(int speed) {
  rightRollerMotor.move_velocity(0);
  leftRollerMotor.move_velocity(0);
}

/*
void rollerSpinForEncoder(int speed, int encDegrees) {
  leftRollerMotor.move_absolute(encDegrees, speed);
  rightRollerMotor.move_absolute(encDegrees, speed);
}
*/
