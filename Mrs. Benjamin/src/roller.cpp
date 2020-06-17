#include "main.h"
#include "roller.h"
#include "portdef.h"

pros::Motor rightRollerMotor(RIGHT_ROLLER_MOTOR_PORT);
pros::Motor leftRollerMotor(LEFT_ROLLER_MOTOR_PORT);

void rollerForward(int speed) {
  rightRollerMotor.move_velocity(speed);
  leftRollerMotor.move_velocity(speed);
}

void rollerBackward(int speed) {
  rightRollerMotor.move_velocity(-speed);
  leftRollerMotor.move_velocity(-speed);
}

void rollerStop() {
  rightRollerMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftRollerMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rightRollerMotor.move_velocity(0);
  leftRollerMotor.move_velocity(0);
}
