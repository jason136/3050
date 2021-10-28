#include "main.h"
#include "chassis.hpp"
#include "portdef.hpp"

// Setup the motor definitions for the motors on the chassis
pros::Motor front_right_motor(FRONT_RIGHT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor front_left_motor(FRONT_LEFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor back_right_motor(BACK_RIGHT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor back_left_motor(BACK_LEFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);

// Chassis Speciic Function definitions
void chassisMove(int voltage) {
  // This function drives the robot forward/backwards at given speed
  front_right_motor.move(voltage);
  front_left_motor.move(-voltage);
  back_right_motor.move(-voltage);
  back_left_motor.move(voltage);
}

void setIndividualMotor(int FRight, int FLeft, int BRight, int BLeft) {
  // Function to set voltage of each motor individually, used in opcontrol
  // This function deals in voltage, and takes arguments from -127 to 127
  front_right_motor.move(FRight);
  front_left_motor.move(-FLeft);
  back_right_motor.move(-BRight);
  back_left_motor.move(BLeft);
}

void chassisStopDrive() {
  front_right_motor.move(0);
  front_left_motor.move(0);
  back_right_motor.move(0);
  back_left_motor.move(0);

  if(DEBUG_ON) {
    std::cout << "chassis stop \n";
  }
}

void resetChassisEncoders() {
  front_right_motor.tare_position();
  front_left_motor.tare_position();
  back_right_motor.tare_position();
  back_left_motor.tare_position();

  if(DEBUG_ON) {
    std::cout << "chassis clear encoders \n";
  }
}

void driveForDistancePID(int distance, int speed) {
/**
 * drive the robot using the build in PID control on the drive base for a given
 * distance. Distance is supplied in inches, and speed is givin in velocity
 * meaning depending on your installed cartidege to be either +- 100 (RED), +-200 (GREEN) +-600 (BLUE) cartridge
 *
 * We are using motors in degree settings of the PID controller
 *
 * TODO/CHECK -- if we give negative distance wil lwe drive backwards?
**/

  float wheelCircum = WHEEL_DIAMETER * 3.14;           // global WHEEL_DIAMETER is set in chassis.h
  float motorDegree = (distance / wheelCircum) * 360;  // cast into full degrees

  // Calculate the lower and uppor bounds for the while loop ensuring robot drives
  // desired distance
  float motorUpper = motorDegree + 5;
  float motorLower = motorDegree - 5;

  if(DEBUG_ON) {
    std::cout << "Dist: " << motorDegree ;
    std::cout << " Upper: " << motorUpper << " Lower: " << motorLower << "\n";
  }

  // First, reset all the encoders
  resetChassisEncoders();

  front_right_motor.move_absolute(motorDegree, speed);    // Moves motorDegree units forward
  front_left_motor.move_absolute(motorDegree, speed);     // Moves motorDegree units forward
  back_right_motor.move_absolute(motorDegree, speed);     // Moves motorDegree units forward
  back_left_motor.move_absolute(motorDegree, speed);      // Moves motorDegree units forward

  while (!((front_left_motor.get_position() < motorUpper) && (front_left_motor.get_position() > motorLower))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
  // we have reached our desired distance, stop the motors.
  chassisStopDrive();

  if(DEBUG_ON) {
    std::cout << "Encoder Left: " << front_left_motor.get_position();
    std::cout << " Encoder Right: " << front_right_motor.get_position() << "\n";
  }
}

void pivotTurn(int speed, long turnAngle) {
/**
  * speed -- Max 100, 200 or 600 RPM depending on cartridge
  * speed should always be positive
  * angle -- desired turn angle in degrees - -359 -- +359
  * negative angle (-45) will turn robot CC (to the left)
  * positive angle (45) will turn Clockwise (to the right)
**/

  // incoming speed variable sanity check
  speed = abs(speed);               // speed is always absolute
  int absAngle = abs(turnAngle);    // used for calculations

  // pivotTurn - turn radius is 1/2 * dimaeter of wheel base
  float turnCircum = WHEEL_BASE * 3.14;           // wheel_base is defind in chassis.h
  float wheelCircum = WHEEL_DIAMETER * 3.14;      // wheel_diameter is defined in chassis.h
  float maxDegrees = 360.0;                       // use .0 for forced float arithmetic
  float turnRatio = turnAngle / maxDegrees;

  double motorDegree = ((turnRatio * turnCircum) / wheelCircum) * maxDegrees;

  if(DEBUG_ON) {
    std::cout << "TurnCircum: " << turnCircum;
    std::cout << " Angle: " << turnAngle;
    std::cout << " absAngle: " << absAngle;
    std::cout << " MotorDegrees: " << motorDegree;
    std::cout << " Speed: " << speed;
    std::cout << " Turn Angle: " << turnRatio;
    std::cout << " Div by Wheel: " << ((turnRatio * turnCircum) / wheelCircum) << "\n";;
  }

  // Calculate the lower and uppor bounds for the while loop ensuring robot drives
  // desired distance
  double motorUpper = fabs(motorDegree) + 5;
  double motorLower = fabs(motorDegree) - 5;

  // reset all encoders
  resetChassisEncoders();

  // we are making turns - pivot left turns opposite of right motor
  front_right_motor.move_absolute(-motorDegree, speed);   // Moves motorDegree units forward
  front_left_motor.move_absolute(motorDegree, speed);     // Moves motorDegree units forward
  back_right_motor.move_absolute(-motorDegree, speed);    // Moves motorDegree units forward
  back_left_motor.move_absolute(motorDegree, speed);      // Moves motorDegree units forward

  // we are moving untill both sides of the robot have reached their target - we are using abs
  // values of both the bounds and the desired distance so we become "insensitive" to to
  // the direction of turns.
  while ((!((fabs(front_right_motor.get_position()) < fabs(motorUpper)) && (fabs(front_right_motor.get_position()) > fabs(motorLower)))) &&
      (!((fabs(front_left_motor.get_position()) < fabs(motorUpper)) && (fabs(front_left_motor.get_position()) > fabs(motorLower)))))  {
      // Continue running this loop as long as the motor is not within +-5 units of its goal
      pros::delay(2);
      // uncomment below for debugging
      /* if(DEBUG_ON){
        std::cout << "Encoder Left: " << front_right_motor.get_position();
        std::cout << " Encoder Right: " << front_left_motor.get_position() << "\n";
      } */
  }
  if(DEBUG_ON) {
      std::cout << "Encoder Left: " << front_left_motor.get_position();
      std::cout << " Encoder Right: " << front_right_motor.get_position() << "\n";
  }

  // we have reached our desired distance, so stop the motors.
  chassisStopDrive();
}

void getChassisDiag(double * buffer) {
  buffer[0] = front_right_motor.get_actual_velocity();
  buffer[1] = front_left_motor.get_actual_velocity();
  buffer[2] = back_right_motor.get_actual_velocity();
  buffer[3] = back_left_motor.get_actual_velocity();
  buffer[4] = back_left_motor.get_temperature();
  buffer[5] = back_left_motor.get_temperature();
  buffer[6] = back_left_motor.get_temperature();
  buffer[7] = back_left_motor.get_temperature();
  buffer[8] = back_left_motor.get_efficiency();
  buffer[9] = back_left_motor.get_efficiency();
  buffer[10] = back_left_motor.get_efficiency();
  buffer[11] = back_left_motor.get_efficiency();
}
