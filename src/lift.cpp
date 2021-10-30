#include "main.h"
#include "portdef.hpp"
#include "lift.hpp"

// Setup the motor definition for the lift motor
pros::Motor frontLiftMotor(FRONT_LIFT_MOTOR);
pros::Motor backLiftMotor(BACK_LIFT_MOTOR);

void frontLiftMove(int voltage) {
  // Raises lift manual based using voltage provided
  // Don't allow movement past lowest point and past upper point of mechanical limits of lift
  frontLiftMotor.move(voltage);

  if(DEBUG_ON){
    std::cout << "life manual raise speed: " << voltage ;
    std::cout << " Lift Encoder: " << frontLiftMotor.get_position() << "\n";
  }
}

void frontLiftLock() {
  if(frontLiftMotor.get_brake_mode() != 2 ) {
    frontLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  frontLiftMotor.move_velocity(0);
  // Slight delay is due to problems we had in the past with
  // very jerky movements
  pros::delay(5);
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
  if(backLiftMotor.get_brake_mode() != 2 ) {
    backLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  backLiftMotor.move_velocity(0);
  // Slight delay is due to problems we had in the past with
  // very jerky movements
  pros::delay(5);
}

void liftResetEncoder() {
  frontLiftMotor.tare_position();

  if(DEBUG_ON){
    std::cout << "lift encoder reset \n";
  }
}

void liftRaiseForEncoder(int voltage, int encDegrees) {
  // raise the lift to a given position as specified by encDegrees at speed indicated
  // by variable speed.  Lift will protect agaisnt lower and upper mechanical bounds

  // allow movement we are within bounderies
  int upperBound = encDegrees + 5;
  int lowerBound = encDegrees - 5;

  // reset lift encoders
  frontLiftMotor.tare_position();
  frontLiftMotor.move(voltage);
  while (!((frontLiftMotor.get_position() < upperBound) && (frontLiftMotor.get_position() > lowerBound))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);

    if(DEBUG_ON) {
      std::cout << "EncDegrees " << encDegrees;
      std::cout << " Current Deg: " << frontLiftMotor.get_position() << "\n";
      pros::delay(2);
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
      frontLiftMotor.move_absolute(0, speed); 
      while (!((frontLiftMotor.get_position() < zeroPointUpper) && (frontLiftMotor.get_position() > zeroPointLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }

      break;

    case 1:
      // move to middle pole position
      frontLiftMotor.move_absolute(LIFT_LEVEL_LOW, speed); 
      while (!((frontLiftMotor.get_position() < lowTowerUpper) && (frontLiftMotor.get_position() > lowTowerLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }
      break;

    case 2:
      // move to heigh pole position
      frontLiftMotor.move_absolute(LIFT_LEVEL_HIGH, speed); 
      while (!((frontLiftMotor.get_position() < highTowerUpper) && (frontLiftMotor.get_position() > highTowerLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }
      break;
  }
  if(DEBUG_ON){
    std::cout << "Lift Encoder: " << frontLiftMotor.get_position();
  }
  frontLiftMotor.move(0);
}

pros::motor_brake_mode_e_t getliftBrakeMode() {
  return frontLiftMotor.get_brake_mode();
}