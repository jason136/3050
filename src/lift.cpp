#include "main.hpp"
#include "portdef.hpp"
#include "lift.hpp"

// Setup the motor definition for the lift motor
pros::Motor liftMotor(LIFT_MOTOR);

void liftResetEncoder() {
  liftMotor.tare_position();

  if(DEBUG_ON){
    std::cout << "lift encoder reset \n";
  }
}

void liftMove(int voltage) {
  // Raises lift manual based using voltage provided
  // Don't allow movement past lowest point and past upper point of mechanical limits of lift
  // We can't use encoder for that as it will bypass it - we need likely mechanical switch for safety
  // For now there is NO SAFETY stop
  liftMotor.move(voltage);

  if(DEBUG_ON){
    std::cout << "life manual raise speed: " << voltage ;
    std::cout << " Lift Encoder: " << liftMotor.get_position() << "\n";
  }
}

void liftRaiseForEncoder(int speed, int encDegrees) {
  // raise the lift to a given position as specified by encDegrees at speed indicated
  // by variable speed.  Lift will protect agaisnt lower and upper bound of lift
  // mechanical cability
  int moveDegrees = liftMotor.get_position() + encDegrees;   // take current position and add
                                                             // requested movement to it
  // allow movement we are within bounderies
  int upperBound = moveDegrees + 5;
  int lowerBound = moveDegrees - 5;
  if(lowerBound < 0 ) {
    lowerBound = 0;
    moveDegrees = 0;  // Can't move past below 0 point!
  }

  // reset lift encoders
  liftMotor.tare_position();
  if (!((moveDegrees > lowerBound) && (moveDegrees < upperBound))) {
    // we can move
    liftMotor.move_absolute(moveDegrees, speed); // Moves given position
    while (!((liftMotor.get_position() < upperBound) && (liftMotor.get_position() > lowerBound))) {
      // Continue running this loop as long as the motor is not within +-5 units of its goal
      pros::delay(2);

      if(DEBUG_ON) {
        std::cout << "EncDegrees " << encDegrees << " moveDegrees: " << moveDegrees;
        std::cout << " Current Deg: " << liftMotor.get_position() << "\n";
        pros::delay(2);
      }
    }
  }
}

pros::motor_brake_mode_e_t getliftBrakeMode() {
  return liftMotor.get_brake_mode();
}

void liftLock() {
  // lock the lift where it is right now....
  // We need to make sure that the lift is on BREAK_HOLD
  if(liftMotor.get_brake_mode() != 2 ) {
    liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  liftMotor.move_velocity(0);
  // Slight delay is due to problems we had in the past with
  // very jerky movements
  pros::delay(5);
}

void liftRaise(int speed, int level) {
  // move the lift up and down where levle is:
  // 0 -- fully retracted back to 0
  // 1 -- raise to lower pole height
  // 2 -- raise to upper pole height

  int lowTowerUpper = LIFT_LEVEL_LOW + 5;
  int lowTowerLower = LIFT_LEVEL_LOW - 5;

  int highTowerUpper = LIFT_LEVEL_HIGH + 5;
  int highTowerLower = LIFT_LEVEL_HIGH - 5;

  int zeroPointUpper = LIFT_FULL_RETRACT + 5;
  int zeroPointLower = LIFT_FULL_RETRACT;

  switch(level) {
    case 0:
      // move all the way back down
      liftMotor.move_absolute(0, speed); // Moves LIFT_LOW_POLE units forward
      while (!((liftMotor.get_position() < zeroPointUpper) && (liftMotor.get_position() > zeroPointLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }

      break;

    case 1:
      // move to middle pole position
      liftMotor.move_absolute(LIFT_LEVEL_LOW, speed); // Moves LIFT_LOW_POLE units forward
      while (!((liftMotor.get_position() < lowTowerUpper) && (liftMotor.get_position() > lowTowerLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }
      break;

    case 2:
      // move to heigh pole position
      liftMotor.move_absolute(LIFT_LEVEL_HIGH, speed); // Moves LIFT_LOW_POLE units forward
      while (!((liftMotor.get_position() < highTowerUpper) && (liftMotor.get_position() > highTowerLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }
      break;
  }
  if(DEBUG_ON){
    std::cout << "Lift Encoder: " << liftMotor.get_position();
  }
}
