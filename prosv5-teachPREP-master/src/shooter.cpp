#include "main.h"    // includes API.h and other headers
#include "shooter.h" // ensures that the corresponding header file (chassis.h) is included
#include "portdef.h" // All port defintions on the cortex need to be included

pros::Motor shooterMotor(SHOOTER_MOTOR_PORT);

void shootBall(int speed) {
  if(DEBUG_ON){
    std::cout << "Shooter running \n" ;
  }
  int shooterUpper = SHOOTER_TARGET + 5;
  int shooterLower = SHOOTER_TARGET - 5;

  shooterMotor.tare_position();
  shooterMotor.move_absolute(SHOOTER_TARGET, speed);          // Moves SHOOTER_TARGET units forward at
                                                              // speed == RPM
  while (!((shooterMotor.get_position() < shooterUpper) && (shooterMotor.get_position() > shooterLower))) {
     pros::delay(2);
  }
  if(DEBUG_ON){
    std::cout << "Shooter Encoder: -- M1: " << shooterMotor.get_position();
    pros::delay(2);
  }
}
