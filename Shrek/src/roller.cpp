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

void rollerLock(int speed) {
  // lock the lift where it is right now
  // We need to make sure that the lift is on BREAK_HOLD
  if(rightRollerMotor.get_brake_mode() != 2 ) {
    rightRollerMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftRollerMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  rightRollerMotor.move_velocity(0);
  leftRollerMotor.move_velocity(0);
  pros::delay(2);
}
