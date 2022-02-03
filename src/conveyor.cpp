#include "main.h"
#include "conveyor.hpp"
#include "portdef.hpp"

// Setup the motor definition for the roller motor
pros::Motor conveyorMotor(CONVEYOR_MOTOR);

void conveyorMove(int voltage) {
  conveyorMotor.move(voltage);
}

void conveyorStop() {
  conveyorMotor.move(0);
}

void conveyorSpinForEncoder(int speed, int encDegrees) {
  leftRollerMotor.move_absolute(encDegrees, speed);
  rightRollerMotor.move_absolute(encDegrees, speed);
}