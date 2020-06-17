#include "main.h"
#include "portdef.h"
#include "lift.h"

pros::Motor rightliftMotor(RIGHT_LIFT_MOTOR);
pros::Motor leftliftMotor(LEFT_LIFT_MOTOR);

void liftSetZero(int speed) {
  // resets encoders of the lift Motor
  rightliftMotor.tare_position();
  leftliftMotor.tare_position();
  if(DEBUG_ON){
    std::cout << "Lift ZERO point reset \n";
  }
}

void liftRaiseManual(int speed) {
  // Raises lift manual based using speed provided
  // Don't allow movement past lowest point and past upper point of mechanical limits of lift
  // We can't use encoder for that as it will bypass it - we need likely mechanical switch for safety
  // So for now there is NO SAFETY stop
  if(DEBUG_ON){
    std::cout << "In Lift Raise Manual function -- Speed: " << speed ;
    std::cout << " Current Encoder: " << rightliftMotor.get_position() << "\n";
  }
  rightliftMotor.move_velocity(speed);
  leftliftMotor.move_velocity(speed);
  pros::delay(2);
}

void liftRaiseForEncoder(int speed, int encDegrees) {
  // raise the lift to a given position as specified by encDegrees at speed indicated
  // by variable speed.  Lift will protect agaisnt lower and upper bound of lift
  // mechanical cability
  int moveDegrees = rightliftMotor.get_position() + encDegrees;   // take current position and add
                                                             // requested movement to it
  // allow movement we are within bounderies
  int upperBound = moveDegrees + 5;
  int lowerBound = moveDegrees - 5;
  if(lowerBound < 0 ) {
    lowerBound = 0;
    moveDegrees = 0;  // Can't move past below 0 point!
  }

  if (!((moveDegrees > lowerBound) && (moveDegrees < upperBound))) {
    // we can move
    rightliftMotor.move_absolute(moveDegrees, speed); // Moves given position
    leftliftMotor.move_absolute(moveDegrees, speed); // Moves given position
    while (!((rightliftMotor.get_position() < upperBound) && (rightliftMotor.get_position() > lowerBound))) {
        // Continue running this loop as long as the motor is not within +-5 units of its goal
        pros::delay(2);
    }
  }
  if(DEBUG_ON) {
    std::cout << "EncDegrees " << encDegrees << " moveDegrees: " << moveDegrees;
    std::cout << " Current Deg Lift Right: " << rightliftMotor.get_position() << "\n";
    std::cout << " Current Deg Lift Left: " << leftliftMotor.get_position() << "\n";
    pros::delay(2);
  }
}

void liftLockMode() {
  // get the current lift lock mode of the break
  std::cout << "Brake Mode Lift Right: " << rightliftMotor.get_brake_mode() << "\n";
  std::cout << "Brake Mode Lift Left: " << leftliftMotor.get_brake_mode() << "\n";
  pros::delay(10);
}

void liftLock() {
  // lock the lift where it is right now....
  // We need to make sure that the lift is on BREAK_HOLD
  if(rightliftMotor.get_brake_mode() != 2 ) {
    rightliftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftliftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  rightliftMotor.move_velocity(0);
  leftliftMotor.move_velocity(0);
  pros::delay(2);
}

void liftEncoderValue() {
  // gets the encoder value and prints it to the std::std::cout
  std::cout << "Lift Encoder: -- MRight: " << rightliftMotor.get_position();
  std::cout << "Lift Encoder: -- MLeft: " << leftliftMotor.get_position();
  pros::delay(2);
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
      rightliftMotor.move_absolute(0, speed); // Moves LIFT_LOW_POLE units forward
      while (!((rightliftMotor.get_position() < zeroPointUpper) && (rightliftMotor.get_position() > zeroPointLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }

      break;

    case 1:
      // move to middle tower position
      rightliftMotor.move_absolute(LIFT_LEVEL_LOW, speed); // Moves LIFT_LOW_POLE units forward
      while (!((rightliftMotor.get_position() < lowTowerUpper) && (rightliftMotor.get_position() > lowTowerLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }
      break;

    case 2:
      // move to heigh tower position
      rightliftMotor.move_absolute(LIFT_LEVEL_HIGH, speed); // Moves LIFT_LOW_POLE units forward
      while (!((rightliftMotor.get_position() < highTowerUpper) && (rightliftMotor.get_position() > highTowerLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }
      break;
  }
  if(DEBUG_ON){
    std::cout << "Lift Encoder: -- MRIGHT: " << rightliftMotor.get_position();
    std::cout << "Lift Encoder: -- MLEFT: " << rightliftMotor.get_position();
    pros::delay(2);           // Give thread time to catch up.
  }
}
