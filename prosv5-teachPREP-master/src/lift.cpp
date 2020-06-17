#include "main.h"
#include "portdef.h"
#include "lift.h"

pros::Motor liftMotor1(LIFT_RIGHT_MOTOR_PORT);
pros::Motor liftMotor2(LIFT_RIGHT_MOTOR_PORT_TWO);
pros::Motor liftMotor3(LIFT_LEFT_MOTOR_PORT);

void liftSetZero(int speed) {
  // reset zero position of each encoded motor.
  liftMotor1.tare_position();
  liftMotor2.tare_position();
  liftMotor3.tare_position();
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
    std::cout << " Current Encoder: " << liftMotor1.get_position() << "\n";
  }
  liftMotor1.move_velocity(speed);
  liftMotor2.move_velocity(speed);
  liftMotor3.move_velocity(speed);
  pros::delay(2);

}

void liftRaiseForEncoder(int speed, int encDegrees) {
  // raise the lift to a given position as specified by encDegrees at speed indicated
  // by variable speed.  Lift will protect agaisnt lower and upper bound of lift
  // mechanical cability
  int moveDegrees = liftMotor1.get_position() + encDegrees;   // take current position and add
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
    liftMotor1.move_absolute(moveDegrees, speed); // Moves given position
    liftMotor2.move_absolute(moveDegrees, speed); // Moves given position
    liftMotor3.move_absolute(moveDegrees, speed); // Moves given position
    while (!((liftMotor1.get_position() < upperBound) && (liftMotor1.get_position() > lowerBound))) {
        // Continue running this loop as long as the motor is not within +-5 units of its goal
        pros::delay(2);
    }
  }
  if(DEBUG_ON) {
    std::cout << "EncDegrees " << encDegrees << " moveDegrees: " << moveDegrees;
    std::cout << " Current Deg: " << liftMotor1.get_position() << "\n";
    pros::delay(2);
  }
}

void liftRaiseStep(int speed, int direction){
  // move lift in given increments up or down - as defiend by LIFT_STEP_SIZE
  // Lift direction is given by variable direction - 0 - means down, 1 - means up
  // movement is protected by upper and lower bound of mechanical lift properties

  int upperBound;
  int lowerBound;
  int moveDegrees;

  // Calculate the movment Step
  if(direction == 0) {
    // moving downwards so current position minus the LIFT_STEP_SIZE
    moveDegrees = liftMotor1.get_position() - LIFT_STEP_SIZE;
    upperBound = moveDegrees + 5;
    lowerBound = moveDegrees - 5;
    if(lowerBound < 0 ) {
      lowerBound = 0;
      moveDegrees = 0;  // Can't move past (below 0 point!
    }
  }
  if(direction == 1) {
    // moving upwards so current position plus the LIFT_STEP_SIZE
    moveDegrees = liftMotor1.get_position() + LIFT_STEP_SIZE;
    upperBound = moveDegrees + 5;
    lowerBound = moveDegrees - 5;
    if(upperBound > LIFT_MAX_HIEGHT ) {
      upperBound = LIFT_MAX_HIEGHT - 5;     // we need to give a bit of room to settle
                                            // id we don't motor may stall in "locked" mode not able to
                                            // to reach encoder setings
      moveDegrees = LIFT_MAX_HIEGHT - 5;    // Can't move past maximum mechanical height
    }
  }

  if(moveDegrees > 0 && moveDegrees < LIFT_MAX_HIEGHT) {
     // Only allow move if we are not hitting 0 or max height
     liftMotor1.move_absolute(moveDegrees, speed); // Moves LIFT_LOW_POLE units forward
     liftMotor2.move_absolute(moveDegrees, speed); // Moves LIFT_LOW_POLE units forward
     liftMotor3.move_absolute(moveDegrees, speed); // Moves LIFT_LOW_POLE units forward
     while (!((liftMotor1.get_position() < upperBound) && (liftMotor1.get_position() > lowerBound))) {
       // Continue running this loop as long as the motor is not within +-5 units of its goal
       pros::delay(2);
     }
  }

  if(DEBUG_ON) {
    std::cout << "Direction: " << direction << " moveDegrees: " << moveDegrees;
    std::cout << " Current Deg: " << liftMotor1.get_position() << "\n";
    pros::delay(2);
  }
}

void liftLockMode() {
  // get the current lift lock mode of the break
  std::cout << "Brake Mode: " << liftMotor1.get_brake_mode() << "\n";
  pros::delay(10);
}

void liftDropCap(int speed){
  // We will move down set vlaue LIFT_DROP_DELTA to help auto drop the cap.

  int movePosition = liftMotor1.get_position() - LIFT_DROP_DELTA;
  int lowerBound = movePosition - 5;
  int upperBound = movePosition + 5;

  liftMotor1.move_absolute(movePosition, speed); // Moves LIFT_LOW_POLE units forward
  liftMotor2.move_absolute(movePosition, speed); // Moves LIFT_LOW_POLE units forward
  liftMotor3.move_absolute(movePosition, speed); // Moves LIFT_LOW_POLE units forward
  while (!((liftMotor1.get_position() < upperBound) && (liftMotor1.get_position() > lowerBound))) {
      // Continue running this loop as long as the motor is not within +-5 units of its goal
      pros::delay(2);
  }
  if(DEBUG_ON){
    std::cout << "Drop Cap Auto Fucntion -- speed: " << speed << " New Encoder Target: ";
    std::cout << liftMotor1.get_position() << " Moved: " << LIFT_DROP_DELTA << "\n";
   }
}

void liftLock() {
  // lock the lift where it is right now....
  // We need to make sure that the lift is on BREAK_HOLD
  if(liftMotor1.get_brake_mode() != 2 ) {
    liftMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    liftMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    liftMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  liftMotor1.move_velocity(0);
  liftMotor2.move_velocity(0);
  liftMotor3.move_velocity(0);
  pros::delay(2);
}

void liftEncoderValue() {
  // gets the encoder value and prints it to the std::std::cout
  std::cout << "Lift Encoder: -- M1: " << liftMotor1.get_position();
  std::cout << " M2: " << liftMotor2.get_position();
  std::cout << " M23 " << liftMotor3.get_position() << "\n";
  pros::delay(2);
}

void liftRaise(int speed, int level) {
  // move the lift up and down where levle is:
  // 0 -- fully retracted back to 0
  // 1 -- raise to lower pole height
  // 2 -- raise to upper pole height

  int lowPoleUpper = LIFT_LOW_POLE + 5;
  int lowPoleLower = LIFT_LOW_POLE - 5;

  int highPoleUpper = LIFT_HIGH_POLE + 5;
  int highPoleLower = LIFT_HIGH_POLE - 5;

  int zeroPointUpper = LIFT_FULL_RETRACT + 5;
  int zeroPointLower = LIFT_FULL_RETRACT;

  switch(level) {
    case 0:
      // move all the way back down
      liftMotor1.move_absolute(0, speed); // Moves LIFT_LOW_POLE units forward
      liftMotor2.move_absolute(0, speed); // Moves LIFT_LOW_POLE units forward
      liftMotor3.move_absolute(0, speed); // Moves LIFT_LOW_POLE units forward
      while (!((liftMotor1.get_position() < zeroPointUpper) && (liftMotor1.get_position() > zeroPointLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }

      break;

    case 1:
      // move to middle pole position
      liftMotor1.move_absolute(LIFT_LOW_POLE, speed); // Moves LIFT_LOW_POLE units forward
      liftMotor2.move_absolute(LIFT_LOW_POLE, speed); // Moves LIFT_LOW_POLE units forward
      liftMotor3.move_absolute(LIFT_LOW_POLE, speed); // Moves LIFT_LOW_POLE units forward
      while (!((liftMotor1.get_position() < lowPoleUpper) && (liftMotor1.get_position() > lowPoleLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }
      break;

    case 2:
      // move to heigh pole position
      liftMotor1.move_absolute(LIFT_HIGH_POLE, speed); // Moves LIFT_LOW_POLE units forward
      liftMotor2.move_absolute(LIFT_HIGH_POLE, speed); // Moves LIFT_LOW_POLE units forward
      liftMotor3.move_absolute(LIFT_HIGH_POLE, speed); // Moves LIFT_LOW_POLE units forward
      while (!((liftMotor1.get_position() < highPoleUpper) && (liftMotor1.get_position() > highPoleLower))) {
          // Continue running this loop as long as the motor is not within +-5 units of its goal
          pros::delay(2);
      }
      break;
  }
  if(DEBUG_ON){
    std::cout << "Lift Encoder: -- M1: " << liftMotor1.get_position();
    std::cout << " M2: " << liftMotor2.get_position();
    std::cout << " M23 " << liftMotor3.get_position() << "\n";
    pros::delay(2);           // Give thread time to catch up.
  }
}
