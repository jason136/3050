#include "main.h"
#include "chassis.hpp"
#include "portdef.hpp"

// Setup the motor definitions for the motors on the chassis
pros::Motor frontRightMotor(FRONT_RIGHT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor frontLeftMotor(FRONT_LEFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backRightMotor(BACK_RIGHT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backLeftMotor(BACK_LEFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);

// Chassis Speciic Function definitions
void chassisMove(int voltage) {
  // This function drives the robot forward/backwards at given speed
  frontRightMotor.move(voltage);
  frontLeftMotor.move(-voltage);
  backRightMotor.move(-voltage);
  backLeftMotor.move(voltage);
}

void setIndividualMotor(int FRight, int FLeft, int BRight, int BLeft) {
  // Function to set voltage of each motor individually, used in opcontrol
  // This function deals in voltage, and takes arguments from -127 to 127
  frontRightMotor.move(FRight);
  frontLeftMotor.move(-FLeft);
  backRightMotor.move(-BRight);
  backLeftMotor.move(BLeft);
}

void chassisLockDrive(int FRight, int FLeft, int BRight, int BLeft) {
  if (FRight == 0 && frontRightMotor.get_brake_mode() != 2) {
      frontRightMotor.move(0);
      frontRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  else if (FLeft == 0 && frontLeftMotor.get_brake_mode() != 2) {
      frontLeftMotor.move(0);
      frontLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  else if (BRight == 0 && backRightMotor.get_brake_mode() != 2) {
      backRightMotor.move(0);
      backRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  else if (BLeft == 0 && backLeftMotor.get_brake_mode() != 2) {
      backLeftMotor.move(0);
      backLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }

  // Slight delay is due to problems we had in the past with
  // very jerky movements
  pros::delay(5);
}

void chassisStopDrive() {
    frontRightMotor.move(0);
    frontLeftMotor.move(0);
    backRightMotor.move(0);
    backLeftMotor.move(0);
}

void resetChassisEncoders() {
  frontRightMotor.tare_position();
  frontLeftMotor.tare_position();
  backRightMotor.tare_position();
  backLeftMotor.tare_position();

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

  frontRightMotor.move_absolute(motorDegree, speed);    // Moves motorDegree units forward
  frontLeftMotor.move_absolute(motorDegree, speed);     // Moves motorDegree units forward
  backRightMotor.move_absolute(motorDegree, speed);     // Moves motorDegree units forward
  backLeftMotor.move_absolute(motorDegree, speed);      // Moves motorDegree units forward

  while (!((frontLeftMotor.get_position() < motorUpper) && (frontLeftMotor.get_position() > motorLower))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
  // we have reached our desired distance, stop the motors.
  chassisStopDrive();

  if(DEBUG_ON) {
    std::cout << "Encoder Left: " << frontLeftMotor.get_position();
    std::cout << " Encoder Right: " << frontRightMotor.get_position() << "\n";
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
  frontRightMotor.move_absolute(-motorDegree, speed);   // Moves motorDegree units forward
  frontLeftMotor.move_absolute(motorDegree, speed);     // Moves motorDegree units forward
  backRightMotor.move_absolute(-motorDegree, speed);    // Moves motorDegree units forward
  backLeftMotor.move_absolute(motorDegree, speed);      // Moves motorDegree units forward

  // we are moving untill both sides of the robot have reached their target - we are using abs
  // values of both the bounds and the desired distance so we become "insensitive" to to
  // the direction of turns.
  while ((!((fabs(frontRightMotor.get_position()) < fabs(motorUpper)) && (fabs(frontRightMotor.get_position()) > fabs(motorLower)))) &&
      (!((fabs(frontLeftMotor.get_position()) < fabs(motorUpper)) && (fabs(frontLeftMotor.get_position()) > fabs(motorLower)))))  {
      // Continue running this loop as long as the motor is not within +-5 units of its goal
      pros::delay(2);
      // uncomment below for debugging
      /* if(DEBUG_ON){
        std::cout << "Encoder Left: " << frontRightMotor.get_position();
        std::cout << " Encoder Right: " << frontLeftMotor.get_position() << "\n";
      } */
  }
  if(DEBUG_ON) {
      std::cout << "Encoder Left: " << frontLeftMotor.get_position();
      std::cout << " Encoder Right: " << frontRightMotor.get_position() << "\n";
  }

  // we have reached our desired distance, so stop the motors.
  chassisStopDrive();
}

void getChassisDiag(double * buffer) {
  buffer[0] = frontRightMotor.get_actual_velocity();
  buffer[1] = frontLeftMotor.get_actual_velocity();
  buffer[2] = backRightMotor.get_actual_velocity();
  buffer[3] = backLeftMotor.get_actual_velocity();
  buffer[4] = backLeftMotor.get_temperature();
  buffer[5] = backLeftMotor.get_temperature();
  buffer[6] = backLeftMotor.get_temperature();
  buffer[7] = backLeftMotor.get_temperature();
  buffer[8] = backLeftMotor.get_efficiency();
  buffer[9] = backLeftMotor.get_efficiency();
  buffer[10] = backLeftMotor.get_efficiency();
  buffer[11] = backLeftMotor.get_efficiency();
}
