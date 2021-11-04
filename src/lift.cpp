#include "main.h"
#include "portdef.hpp"
#include "lift.hpp"

// Setup the motor definition for the lift motor
pros::Motor frontRightLiftMotor(FRONT_RIGHT_LIFT_MOTOR);
pros::Motor frontLeftLiftMotor(FRONT_LEFT_LIFT_MOTOR);
pros::Motor backLiftMotor(BACK_LIFT_MOTOR);

void frontLiftMove(int voltage) {
  // Raises lift manual based using voltage provided
  // Don't allow movement past lowest point and past upper point of mechanical limits of lift
  frontRightLiftMotor.move(voltage);
  frontLeftLiftMotor.move(-voltage);

  if(DEBUG_ON){
    std::cout << "life manual raise speed: " << voltage ;
    std::cout << " Lift Encoder: " << frontRightLiftMotor.get_position() << "\n";
  }
}

void frontLiftLock() {
  frontRightLiftMotor.move(0);
  frontLeftLiftMotor.move(0);
  if (frontRightLiftMotor.get_brake_mode() != 2 ) {
    frontRightLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    frontLeftLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
}

void backLiftMove(int voltage) {
  // Raises lift manual based using voltage provided
  // Don't allow movement past lowest point and past upper point of mechanical limits of lift
  backLiftMotor.move(voltage);

  if(DEBUG_ON){
    std::cout << "life manual raise speed: " << voltage ;
    std::cout << " Lift Encoder: " << backLiftMotor.get_position() << "\n";
  }
}

void backLiftLock() {
  backLiftMotor.move(0);
  if(backLiftMotor.get_brake_mode() != 2 ) {
    backLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
}