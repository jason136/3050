#include "main.h"    // includes API.h and other headers
#include "chassis.h" // ensures that the corresponding header file (chassis.h) is included
#include "portdef.h" // All port defintions on the cortex need to be included

// Setup the motor definitions for the motors on the chassis, including GEARSET,
// which in this case is GRREN cartridge - 200 RPM gear set.
pros::Motor left_wheel_1 (DRIVE_LEFT_MOTOR_PORT);
pros::Motor left_wheel_2 (DRIVE_LEFT_MOTOR_PORT2);
pros::Motor right_wheel_1 (DRIVE_RIGHT_MOTOR_PORT);
pros::Motor right_wheel_2 (DRIVE_RIGHT_MOTOR_PORT2);


// Place all chassis specific functions here, forexample
// void driveForDistancePD(int speed, int distance) {}

void driveRobot(int speed) {
  // This function drives the robot forward/backwards at given speed
  left_wheel_1.move_velocity(speed);
  left_wheel_2.move_velocity(speed);
  right_wheel_1.move_velocity(speed);
  right_wheel_2.move_velocity(speed);
}

void chassisSetOpcontrol(int left, int right) {
  // requires input for the left motor and right motor, typical from thei
  // the joystick
  left_wheel_1.move(left);
  left_wheel_2.move(left);
  right_wheel_1.move(right);
  right_wheel_2.move(right);
  /*
  if(DEBUG_ON){
    std::cout << "Left RPM: " << left_wheel_1.get_actual_velocity();
    std::cout << "Right RPM: " << right_wheel_1.get_actual_velocity() << "\n";
  }
  */
}

void chassisStopDrive(){
  // convienance fucntion to stop fhe drive train from moving
  left_wheel_1.move(0);
  left_wheel_2.move(0);
  right_wheel_1.move(0);
  right_wheel_2.move(0);
}

void driveForDistancePID(int distance, int speed) {
  // drive the robot using the build in PID control on the drive base for a given
  // distance. Distance is supplied in inches, and speed is givin in velocity
  // meaning depending on your installed cartidege to be either +- 100 (RED), +-200 (GREEN)
  // +-600 (BLUE) cartridge
  //
  // We are using motors in degree settings of the PID controller
  //
  // TODO/CHECK -- if we give negative distance wil lwe drive backwards?


  float wheelCircum = WHEEL_DIAMETER * 3.14;    // global WHEEL_DIAMETER is set in chassis.h
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
  left_wheel_1.tare_position();
  left_wheel_2.tare_position();
  right_wheel_1.tare_position();
  right_wheel_2.tare_position();

  left_wheel_1.move_absolute(motorDegree, speed);    // Moves motorDegree units forward
  left_wheel_2.move_absolute(motorDegree, speed);    // Moves motorDegree units forward
  right_wheel_1.move_absolute(motorDegree, speed);   // Moves motorDegree units forward
  right_wheel_2.move_absolute(motorDegree, speed);   // Moves motorDegree units forward

  while (!((left_wheel_1.get_position() < motorUpper) && (left_wheel_1.get_position() > motorLower))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
  // we have reached our desired distance, so stop the motors.

  left_wheel_1.move(0);
  left_wheel_2.move(0);
  right_wheel_1.move(0);
  right_wheel_2.move(0);

  if(DEBUG_ON){
    std::cout << "Encoder Left: " << left_wheel_1.get_position();
    std::cout << " Encoder Right: " << right_wheel_1.get_position() << "\n";
  }
}

void pivotTurn(int speed, long turnAngle) {
  //
  // speed -- Max 100, 200 or 600 RPM depending on cartridge
  // speed should always be positive
  // angle -- desired turn angle in degrees - -359 -- +359
  //          negative angle (-45) will turn robot CC (to the left)
  //          positive angle (45) will turn Clockwise (to the right)

  // incoming speed variable sanity check
  speed = abs(speed);         // speed is always absolute

  int absAngle = abs(turnAngle);  // used for calculations

  // pivotTurn - turn radius is 1/2 * dimaeter of wheel base
  float turnCircum = WHEEL_BASE * 3.14;           // wheel_base is defind in chassis.h
  float wheelCircum = WHEEL_DIAMETER * 3.14;      // wheel_diameter is defined in chassis.h
  float maxDegrees = 360.0;                       // if you do not do .0 on end divisions fail.....
  float turnRatio = turnAngle / maxDegrees;

  double motorDegree = ((turnRatio * turnCircum) / wheelCircum) * maxDegrees;
  std::cout << "Turn Angle: " << turnRatio;
  std::cout << " Div by Wheel: " << ((turnRatio * turnCircum) / wheelCircum) << "\n";

  //motorDegree = 200;

  if(DEBUG_ON) {
    std::cout << "TurnCircum: " << turnCircum;
    std::cout << " wheelCircum: " << wheelCircum;
    std::cout << " Angle: " << turnAngle;
    std::cout << " absAngle: " << absAngle;
    std::cout << " MotorDegrees: " << motorDegree;
    std::cout << " Speed: " << speed << "\n";
  }

  // Calculate the lower and uppor bounds for the while loop ensuring robot drives
  // desired distance
  double motorUpper = fabs(motorDegree) + 5;
  double motorLower = fabs(motorDegree) - 5;

  // We first need to reset all the encoders
  left_wheel_1.tare_position();
  left_wheel_2.tare_position();
  right_wheel_1.tare_position();
  right_wheel_2.tare_position();

  if(DEBUG_ON){
    std::cout << " RESET -- Encoder Left: " << left_wheel_1.get_position();
    std::cout << " Encoder Right: " << right_wheel_1.get_position() << "\n";
    std::cout << "motorUpper: " << motorUpper << " motorLower: " << motorLower << "\n";
  }

  // we are making turns - pivot left turns opposite of right motor
  left_wheel_1.move_absolute(motorDegree, speed);   // Moves motorDegree units forward
  left_wheel_2.move_absolute(motorDegree, speed);   // Moves motorDegree units forward
  right_wheel_1.move_absolute(-motorDegree, speed);   // Moves motorDegree units forward
  right_wheel_2.move_absolute(-motorDegree, speed);   // Moves motorDegree units forward

  //we are moving untill both sides of the robot have reached thier target - we are usign abs
  // values of both the bounds and the desired distance so we become "incensitive" to to
  // the direction of turns.
  while ((!((fabs(right_wheel_1.get_position()) < fabs(motorUpper)) && (fabs(right_wheel_1.get_position()) > fabs(motorLower)))) &&
      (!((fabs(left_wheel_1.get_position()) < fabs(motorUpper)) && (fabs(left_wheel_1.get_position()) > fabs(motorLower)))))  {
      // Continue running this loop as long as the motor is not within +-5 units of its goal
      pros::delay(2);
      // uncomment below if you wnat detaield encoder data for debugging
      // your terminal will be flooted with data!
      /* if(DEBUG_ON){
        std::cout << "Encoder Left: " << left_wheel_1.get_position();
        std::cout << " Encoder Right: " << right_wheel_1.get_position() << "\n";
      } */
  }
  if(DEBUG_ON){
      std::cout << "Encoder Left: " << left_wheel_1.get_position();
      std::cout << " Encoder Right: " << right_wheel_1.get_position() << "\n";
  }

  // we have reached our desired distance, so stop the motors.
  left_wheel_1.move(0);
  left_wheel_2.move(0);
  right_wheel_1.move(0);
  right_wheel_2.move(0);
}
