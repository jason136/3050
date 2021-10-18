#include "main.hpp"
#include "roller.hpp"
#include "portdef.hpp"

// Setup the motor definition for the roller motor
pros::Motor rightRollerMotor(RIGHT_ROLLER_MOTOR);
pros::Motor leftRollerMotor(LEFT_ROLLER_MOTOR);

void rollerMove(int voltage) {
  rightRollerMotor.move(voltage);
  leftRollerMotor.move(voltage);
}

void rollerStop() {
  rightRollerMotor.move(0);
  leftRollerMotor.move(0);
}

// void rollerSpinForEncoder(int speed, int encDegrees) {
//   leftRollerMotor.move_absolute(encDegrees, speed);
//   rightRollerMotor.move_absolute(encDegrees, speed);
// }
