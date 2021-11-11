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
    std::cout << " Lift Encoder: " << frontRightLiftMotor.get_position() << std::endl; 
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
    std::cout << " Lift Encoder: " << backLiftMotor.get_position() << std::endl; 
  }
}

void backLiftLock() {
  backLiftMotor.move(0);
  if(backLiftMotor.get_brake_mode() != 2 ) {
    backLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
}

void liftResetEncoder() {
  frontRightLiftMotor.tare_position();
  frontLeftLiftMotor.tare_position();

  if(DEBUG_ON){
    std::cout << "lift encoder reset" << std::endl; 
  }
}

void liftRaiseForEncoder(int voltage, int encDegrees) {
  // raise the lift to a given position as specified by encDegrees at speed indicated
  // by variable speed.  Lift will protect agaisnt lower and upper mechanical bounds

  // allow movement we are within bounderies
  int upperBound = encDegrees + 5;
  int lowerBound = encDegrees - 5;

  // reset lift encoders
  frontRightLiftMotor.tare_position();
  frontLeftLiftMotor.tare_position();
  frontRightLiftMotor.move(voltage);
  frontLeftLiftMotor.move(-voltage);
  while (!((frontRightLiftMotor.get_position() < upperBound) && (frontRightLiftMotor.get_position() > lowerBound))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);

    if(DEBUG_ON) {
      std::cout << "EncDegrees " << encDegrees;
      std::cout << " Current Deg: " << frontRightLiftMotor.get_position() << std::endl; 
    }
  }
  frontLiftMove(0);
}

void liftRaise(int speed, int level) {
  int lowTowerUpper = LIFT_LEVEL_LOW + 5;
  int lowTowerLower = LIFT_LEVEL_LOW - 5;

  int highTowerUpper = LIFT_LEVEL_HIGH + 5;
  int highTowerLower = LIFT_LEVEL_HIGH - 5;

  int zeroPointUpper = LIFT_FULL_RETRACT + 5;
  int zeroPointLower = LIFT_FULL_RETRACT;

  switch(level) {
    case 0:
      // move all the way back down
      frontRightLiftMotor.move_absolute(0, speed); 
      frontLeftLiftMotor.move_absolute(0, speed); 
      while (!((frontRightLiftMotor.get_position() < zeroPointUpper) && (frontRightLiftMotor.get_position() > zeroPointLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }

      break;

    case 1:
      // move to middle pole position
      frontRightLiftMotor.move_absolute(LIFT_LEVEL_LOW, speed); 
      frontLeftLiftMotor.move_absolute(LIFT_LEVEL_LOW, speed); 
      while (!((frontRightLiftMotor.get_position() < lowTowerUpper) && (frontRightLiftMotor.get_position() > lowTowerLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }
      break;

    case 2:
      // move to heigh pole position
      frontRightLiftMotor.move_absolute(LIFT_LEVEL_HIGH, speed); 
      frontLeftLiftMotor.move_absolute(LIFT_LEVEL_HIGH, speed); 
      while (!((frontRightLiftMotor.get_position() < highTowerUpper) && (frontRightLiftMotor.get_position() > highTowerLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }
      break;
  }
  if(DEBUG_ON){
    std::cout << "Lift Encoder: " << frontRightLiftMotor.get_position() << std::endl; ;
  }
  frontRightLiftMotor.move(0);
  frontLeftLiftMotor.move(0);
}

pros::motor_brake_mode_e_t getliftBrakeMode() {
  return frontRightLiftMotor.get_brake_mode();
}