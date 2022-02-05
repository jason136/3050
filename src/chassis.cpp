#include "main.h"
#include "chassis.hpp"
#include "portdef.hpp"
#include <cmath>

// Setup the motor definitions for the motors on the chassis
pros::Motor frontRightDriveMotor(FRONT_RIGHT_DRIVE_MOTOR, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor frontLeftDriveMotor(FRONT_LEFT_DRIVE_MOTOR, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backRightDriveMotor(BACK_RIGHT_DRIVE_MOTOR, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backLeftDriveMotor(BACK_LEFT_DRIVE_MOTOR, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Imu intertialSensor(INERTIAL_PORT);
pros::ADIEncoder lateralEncoder(LATERAL_BASE_ENCODER_TOP, LATERAL_BASE_ENCODER_BOTTOM, false);

// Chassis Speciic Function definitions
void chassisMove(int voltage) {
    // This function drives the robot forward/backwards at given speed
    frontRightDriveMotor.move(voltage);
    frontLeftDriveMotor.move(-voltage);
    backRightDriveMotor.move(voltage);
    backLeftDriveMotor.move(-voltage);
}

void chassisMoveIndividuals(int FRight, int FLeft, int BRight, int BLeft) {
    // Function to set voltage of each motor individually, used in opcontrol
    // This function deals in voltage, and takes arguments from -127 to 127
    frontRightDriveMotor.move(-FRight);
    frontLeftDriveMotor.move(FLeft);
    backRightDriveMotor.move(-BRight);
    backLeftDriveMotor.move(BLeft);
}

void chassisLockDrive(int FRight, int FLeft, int BRight, int BLeft) {
    if (FRight == 0) {
        frontRightDriveMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        frontRightDriveMotor.move_velocity(0);
    }
    else if (FLeft == 0) {
        frontLeftDriveMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        frontLeftDriveMotor.move_velocity(0);
    }
    else if (BRight == 0) {
        backRightDriveMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        backRightDriveMotor.move_velocity(0);
    }
    else if (BLeft == 0) {
        backLeftDriveMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        backLeftDriveMotor.move_velocity(0);
    }
}

void trackSpeed(double * coords) {
    coords[0] = ((frontRightDriveMotor.get_actual_velocity() + backRightDriveMotor.get_actual_velocity()) / 2.0);
    coords[1] = ((frontLeftDriveMotor.get_actual_velocity() + backLeftDriveMotor.get_actual_velocity()) / 2.0);
    coords[2] = lateralEncoder.get_value();
}

void chassisGyroPark() {
    //std::cout << "gyro things: ";
    //std::cout << intertialSensor.get_pitch() << " --  " << intertialSensor.get_yaw() << " --  " << intertialSensor.get_roll() << " --  " << std::endl;

    double pitch = intertialSensor.get_pitch();

    if (pitch < -10) chassisMove(-50);
    else if (pitch > 10) chassisMove(50);

    //std::cout << accel.x << " - " << accel.y << " - " << accel.z << std::endl;
}

void chassisStopDrive() {
    frontRightDriveMotor.move(0);
    frontLeftDriveMotor.move(0);
    backRightDriveMotor.move(0);
    backLeftDriveMotor.move(0);
}

void resetChassisEncoders() {
    frontRightDriveMotor.tare_position();
    frontLeftDriveMotor.tare_position();
    backRightDriveMotor.tare_position();
    backLeftDriveMotor.tare_position();
}

void driveForDistancePID(int distance, int speed) {
/**
 * drive the robot using the build in PID control on the drive base for a given
 * distance. Distance is supplied in inches, and speed is givin in velocity
 * meaning depending on your installed cartidege to be either +- 100 (RED), +-200 (GREEN) +-600 (BLUE) cartridge
 *
 * We are using motors in degree settings of the PID controller
 *
**/

    float wheelCircum = WHEEL_DIAMETER * 3.14;           // global WHEEL_DIAMETER is set in chassis.h
    float motorDegree = (distance / wheelCircum) * 360;  // cast into full degrees

    float motorUpper = motorDegree + 5;
    float motorLower = motorDegree - 5;

    resetChassisEncoders();

    frontRightDriveMotor.move_absolute(-motorDegree, speed);
    frontLeftDriveMotor.move_absolute(motorDegree, speed);
    backRightDriveMotor.move_absolute(-motorDegree, speed);
    backLeftDriveMotor.move_absolute(motorDegree, speed);

    while (!((frontLeftDriveMotor.get_position() < motorUpper) && (frontLeftDriveMotor.get_position() > motorLower))) {
        // Continue running this loop as long as the motor is not within +-5 units of its goal
        pros::delay(2);
    }

    chassisStopDrive();
}

void pivotTurn(int turnAngle, int speed) {
/**
  * speed -- Max 100, 200 or 600 RPM depending on cartridge
  * speed should always be positive
  * angle -- desired turn angle in degrees - -359 -- +359
  * negative angle (-45) will turn robot CC (to the left)
  * positive angle (45) will turn Clockwise (to the right)
**/

    // incoming speed variable sanity check
    speed = abs(speed);               // speed is always absolute

    // pivotTurn - turn radius is 1/2 * dimaeter of wheel base
    float turnCircum = WHEEL_BASE * 3.14;           // wheel_base is defind in chassis.h
    float wheelCircum = WHEEL_DIAMETER * 3.14;      // wheel_diameter is defined in chassis.h
    float maxDegrees = 360.0;
    float turnRatio = turnAngle / maxDegrees;

    double motorDegree = ((turnRatio * turnCircum) / wheelCircum) * maxDegrees;

    double motorUpper = fabs(motorDegree) + 5;
    double motorLower = fabs(motorDegree) - 5;

    resetChassisEncoders();

    // we are making turns - pivot left turns opposite of right motor
    frontRightDriveMotor.move_absolute(motorDegree, speed);
    frontLeftDriveMotor.move_absolute(motorDegree, speed);
    backRightDriveMotor.move_absolute(motorDegree, speed);
    backLeftDriveMotor.move_absolute(motorDegree, speed);

    // we are moving until both sides of the robot have reached their target - we are using abs
    // values of both the bounds and the desired distance so we become "insensitive" to to
    // the direction of turns.
    while ((!((fabs(frontRightDriveMotor.get_position()) < fabs(motorUpper)) && (fabs(frontRightDriveMotor.get_position()) > fabs(motorLower)))) &&
            (!((fabs(frontLeftDriveMotor.get_position()) < fabs(motorUpper)) && (fabs(frontLeftDriveMotor.get_position()) > fabs(motorLower)))))  {
            // Continue running this loop as long as the motor is not within +-5 units of its goal
            pros::delay(2);
    }

    chassisStopDrive();
}

void getChassisDiag(double * buffer) {
    buffer[0] = frontRightDriveMotor.get_actual_velocity();
    buffer[1] = frontLeftDriveMotor.get_actual_velocity();
    buffer[2] = backRightDriveMotor.get_actual_velocity();
    buffer[3] = backLeftDriveMotor.get_actual_velocity();
    buffer[4] = backLeftDriveMotor.get_temperature();
    buffer[5] = backLeftDriveMotor.get_temperature();
    buffer[6] = backLeftDriveMotor.get_temperature();
    buffer[7] = backLeftDriveMotor.get_temperature();
    buffer[8] = backLeftDriveMotor.get_efficiency();
    buffer[9] = backLeftDriveMotor.get_efficiency();
    buffer[10] = backLeftDriveMotor.get_efficiency();
    buffer[11] = backLeftDriveMotor.get_efficiency();
}
