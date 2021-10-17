#include "main.h"
#include "chassis.h"
#include "portdef.h"

// Setup the motor definitions for the motors on the chassis
pros::Motor front_right_motor (FRONT_RIGHT_MOTOR_PORT);
pros::Motor front_left_motor (FRONT_LEFT_MOTOR_PORT);
pros::Motor back_right_motor (BACK_RIGHT_MOTOR_PORT);
pros::Motor back_left_motor (BACK_LEFT_MOTOR_PORT);

// Chassis Speciic Function definitions
void driveRobot(int speed) {
  // This function drives the robot forward/backwards at given speed
  front_right_motor.move_velocity(speed);
  front_left_motor.move_velocity(speed);
  back_right_motor.move_velocity(speed);
  back_left_motor.move_velocity(speed);
}

void chassisSetOpcontrol(int left, int right) {
  // requires input for the left motor and right motor, typicaly from the
  // the joysticks
  front_right_motor.move(right);
  front_left_motor.move(left);
  back_right_motor.move(right);
  back_left_motor.move(left);

  if(true) {
    std::cout << "Right RPM: " << front_right_motor.get_actual_velocity();
    std::cout << "Left RPM: " << front_left_motor.get_actual_velocity() << "\n";
    std::cout << typeid(front_right_motor.get_actual_velocity()).name() << '\n';
  }
}

void setIndividualMotor(int FRight, int FLeft, int BRight, int BLeft) {
  front_right_motor.move_velocity(FRight);
  front_left_motor.move_velocity(FLeft);
  back_right_motor.move_velocity(BRight);
  back_left_motor.move_velocity(BLeft);

  if(DEBUG_ON) {
    std::cout << "Front Right RPM: " << front_right_motor.get_actual_velocity();
    std::cout << "Front Left RPM: " << front_left_motor.get_actual_velocity();
    std::cout << "Back Right RPM: " << back_right_motor.get_actual_velocity();
    std::cout << "Back Left RPM: " << back_left_motor.get_actual_velocity() << "\n";
  }
}

void chassisStopDrive() {
  // convienance fucntion to stop the drive train from moving
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
 * meaning depending on your installed cartidege to be either +- 100 (RED), +-200 (GREEN)
 *
 * +-600 (BLUE) cartridge
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

  // We first need to reset all the encoders
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

  // We first need to reset all the encoders
  resetChassisEncoders();

  if(DEBUG_ON) {
    std::cout << " RESET -- Encoder Left: " << front_left_motor.get_position();
    std::cout << " Encoder Right: " << front_right_motor.get_position() << "\n";
    std::cout << "motorUpper: " << motorUpper << " motorLower: " << motorLower << "\n";
  }

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
      // uncomment below if you wnat detaield encoder data for debugging
      // your terminal will be flooted with data!
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

void getDiag(double * buffer) {
  // buffer[0] = front_right_motor.get_actual_velocity();
  // buffer[1] = front_left_motor.get_actual_velocity();
  // buffer[2] = back_right_motor.get_actual_velocity();
  // buffer[3] = back_left_motor.get_actual_velocity();
  buffer[0] = 5.0;
  buffer[1] = 5.0;
  buffer[2] = 5.0;
  buffer[3] = 5.0;
}

int average(int x, int y) {
  return((x + y) / 2);
}
