#include "main.h"
#include "chassis.hpp"
#include "portdef.hpp"
#include <cmath>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

// Setup the motor definitions for the motors on the chassis
pros::Motor frontRightDriveMotor(FRONT_RIGHT_DRIVE_MOTOR, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor frontLeftDriveMotor(FRONT_LEFT_DRIVE_MOTOR, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backRightDriveMotor(BACK_RIGHT_DRIVE_MOTOR, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backLeftDriveMotor(BACK_LEFT_DRIVE_MOTOR, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Gps gpsSensor(GPS_PORT, 0.065, -0.23);

pros::Imu inertialSensor(INERTIAL_PORT);
pros::ADIEncoder lateralEncoder(LATERAL_BASE_ENCODER_TOP, LATERAL_BASE_ENCODER_BOTTOM, false);

extern pros::Vision visionSensor;

// Chassis Speciic Function definitions
void chassisMove(int voltage) {
    // This function drives the robot forward/backwards at given speed
    frontRightDriveMotor.move(voltage);
    frontLeftDriveMotor.move(voltage);
    backRightDriveMotor.move(voltage);
    backLeftDriveMotor.move(voltage);
}

void chassisMoveIndividuals(int FRight, int FLeft, int BRight, int BLeft) {
    // Function to set voltage of each motor individually, used in opcontrol
    // This function deals in voltage, and takes arguments from -127 to 127
    frontRightDriveMotor.move(FRight);
    frontLeftDriveMotor.move(FLeft);
    backRightDriveMotor.move(BRight);
    backLeftDriveMotor.move(BLeft);
}

void trackSpeed(double * coords) {
    coords[0] = ((frontRightDriveMotor.get_actual_velocity() + backRightDriveMotor.get_actual_velocity()) / 2.0);
    coords[1] = ((frontLeftDriveMotor.get_actual_velocity() + backLeftDriveMotor.get_actual_velocity()) / 2.0);
    coords[2] = lateralEncoder.get_value();
}
 
void chassisGyroPark() {
    //std::cout << "gyro things: ";
    //std::cout << inertialSensor.get_pitch() << " --  " << inertialSensor.get_yaw() << " --  " << inertialSensor.get_roll() << " --  " << std::endl;

    double pitch = inertialSensor.get_pitch();

    if (pitch < -10) chassisMove(-50);
    else if (pitch > 10) chassisMove(50);

    //std::cout << accel.x << " - " << accel.y << " - " << accel.z << std::endl;
}

void chassisStopDrive(pros::motor_brake_mode_e_t brakeType, bool left, bool right) {
  if (left) {
    frontLeftDriveMotor.set_brake_mode(brakeType);
    backLeftDriveMotor.set_brake_mode(brakeType);
    frontLeftDriveMotor.move_velocity(0);
    backLeftDriveMotor.move_velocity(0);
  }
  if (right) {
    frontRightDriveMotor.set_brake_mode(brakeType);
    backRightDriveMotor.set_brake_mode(brakeType);
    frontRightDriveMotor.move_velocity(0);
    backRightDriveMotor.move_velocity(0);
  }
}

void resetChassisEncoders() {
    frontRightDriveMotor.tare_position();
    frontLeftDriveMotor.tare_position();
    backRightDriveMotor.tare_position();
    backLeftDriveMotor.tare_position();
}

void driveForDistancePID(int distance, int speed, int maxTime) {
/**
 * drive the robot using the build in PID control on the drive base for a given
 * distance. Distance is supplied in inches, and speed is givin in velocity
 * meaning depending on your installed cartidege to be either +- 100 (RED), +-200 (GREEN) +-600 (BLUE) cartridge
 *
 * We are using motors in degree settings of the PID controller
 *
**/

    float wheelCircum = WHEEL_DIAMETER * 3.14;
    float motorDegree = (distance / wheelCircum) * 360;

    float motorUpper = motorDegree + 5;
    float motorLower = motorDegree - 5;

    resetChassisEncoders();

    frontRightDriveMotor.move_absolute(motorDegree, speed);
    frontLeftDriveMotor.move_absolute(motorDegree, speed);
    backRightDriveMotor.move_absolute(motorDegree, speed);
    backLeftDriveMotor.move_absolute(motorDegree, speed);

    int timer = 0;
    while (!((frontLeftDriveMotor.get_position() < motorUpper) && (frontLeftDriveMotor.get_position() > motorLower))) {        
        if (maxTime != 0 && timer >= maxTime) break;
        maxTime += 2;
        pros::delay(2);
    }

    chassisStopDrive(pros::E_MOTOR_BRAKE_BRAKE);
}

void pivotTurn(int turnAngle, int speed) {
/**
  * speed -- Max 100, 200 or 600 RPM depending on cartridge
  * speed should always be positive
  * angle -- desired turn angle in degrees - -359 -- +359
  * negative angle (-45) will turn robot CC (to the left)
  * positive angle (45) will turn Clockwise (to the right)
**/

    float turnCircum = WHEEL_BASE * 3.14;
    float wheelCircum = WHEEL_DIAMETER * 3.14;
    float maxDegrees = 360.0;
    float turnRatio = turnAngle / maxDegrees;

    double motorDegree = ((turnRatio * turnCircum) / wheelCircum) * maxDegrees;

    double motorUpper = fabs(motorDegree) + 5;
    double motorLower = fabs(motorDegree) - 5;

    resetChassisEncoders();

    frontRightDriveMotor.move_absolute(-motorDegree, speed);
    frontLeftDriveMotor.move_absolute(motorDegree, speed);
    backRightDriveMotor.move_absolute(-motorDegree, speed);
    backLeftDriveMotor.move_absolute(motorDegree, speed);

    while ((!((fabs(frontRightDriveMotor.get_position()) < fabs(motorUpper)) && (fabs(frontRightDriveMotor.get_position()) > fabs(motorLower)))) &&
            (!((fabs(frontLeftDriveMotor.get_position()) < fabs(motorUpper)) && (fabs(frontLeftDriveMotor.get_position()) > fabs(motorLower)))))  {
            pros::delay(2);
    }

    std::cout << inertialSensor.get_rotation() << std::endl;

    chassisStopDrive(pros::E_MOTOR_BRAKE_BRAKE);
}

void pollGyro() {
    if (inertialSensor.is_calibrating()) {
        pros::screen::print(TEXT_MEDIUM, 2, "calibrating");
    }
    else {
        pros::c::imu_accel_s_t accel1 = inertialSensor.get_accel();
        pros::screen::print(TEXT_MEDIUM, 2, "gyro: %3f", inertialSensor.get_rotation());
        pros::screen::print(TEXT_MEDIUM, 3, "x: %3f, y: %3f, z: %3f", accel1.x, accel1.y, accel1.z);
    }
}

void calibrateGyro() {
    inertialSensor.reset();
}

void resetGyro() {
    inertialSensor.set_rotation(0);
}

void gyroTurn(int turnAngle, int time) {
    
    while (inertialSensor.is_calibrating()) {
        pros::delay(5);
    }

    double zero_point_offset = inertialSensor.get_rotation();
    
    // p / i ~ 1 / 30
    double error = turnAngle;
    double pidSpeed, derivitive, totalError, previousError = 0.0;
    float p = 0.13;
    float i = 0.00005;
    float d = 0.00;

    std::cout << "pre turn rotation: " << inertialSensor.get_rotation() << " turnAngle " << turnAngle << std::endl;

    int direction;
    if (turnAngle < 0) direction = 1;
    else direction = -1;

    for (int x = 0; x < time; x += 20)  {
        std::cout << error << std::endl;

        error = fabs(turnAngle) - fabs(inertialSensor.get_rotation() - zero_point_offset);
        totalError += error * 0.02;
        derivitive = (error - previousError) / 0.02;
        pidSpeed = p * error + i * totalError + d * derivitive;

        frontRightDriveMotor.move_velocity(-direction * (pidSpeed * 10));
        frontLeftDriveMotor.move_velocity(direction * (pidSpeed * 10));
        backRightDriveMotor.move_velocity(-direction * (pidSpeed * 10));
        backLeftDriveMotor.move_velocity(direction * (pidSpeed * 10));

        previousError = error;
        pros::delay(20);
    }

    std::cout << "turn done " << inertialSensor.get_rotation() << std::endl;
 
    chassisStopDrive(pros::E_MOTOR_BRAKE_BRAKE);
}

void initializeGps(double xInit, double yInit, double headingInit, double xOffset, double yOffset) {
    gpsSensor.set_data_rate(20);
    // if (xInit || yInit || headingInit) {
        gpsSensor.set_position(xInit, yInit, headingInit);
    // }
    // if (xOffset || yOffset) {
        gpsSensor.set_offset(xOffset, yOffset);
    // }

    std::cout << "gps initialized" << std::endl;
} 

void pollGps() {

    pros::c::gps_status_s_t status = gpsSensor.get_status();

    pros::screen::print(TEXT_MEDIUM, 2, "error: %3f", gpsSensor.get_error());
    pros::screen::print(TEXT_MEDIUM, 3, "x: %3f, y: %3f", status.x, status.y);
    pros::screen::print(TEXT_MEDIUM, 4, "pitch: %3f, yaw: %3f, roll: %3f", status.pitch, status.yaw, status.roll);

}

void seek(int xCord, int yCord, int time) {

    int turn_Error;
    double turn_PidSpeed, turn_Derivitive, turn_TotalError, turn_PreviousError = 0.0;
    float turn_P = 0.7;
    float turn_I = 0.18;
    float turn_D = 0.05;

    int dist_Error;
    double dist_PidSpeed, dist_Derivitive, dist_TotalError, dist_PreviousError = 0.0;
    float dist_P = 1.2;
    float dist_I = 0.15;
    float dist_D = 0.01;

    for (int x = 0; x < time; x += 20) {

        pros::c::gps_status_s_t status = gpsSensor.get_status();
        int deltaX = xCord - status.x * 1000;
        int deltaY = yCord - status.y * 1000;

        float angleToTarget = atan(deltaY / deltaX);

        turn_Error = angleToTarget;
        turn_TotalError += turn_Error * 0.02;
        turn_Derivitive = (turn_Error - turn_PreviousError) / 0.02;
        turn_PidSpeed = turn_P * turn_Error + turn_I * turn_TotalError + turn_D * turn_Derivitive;
        turn_PreviousError = turn_Error;

        float distanceToTarget = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

        dist_Error = distanceToTarget;
        dist_TotalError += dist_Error * 0.02;
        dist_Derivitive = (dist_Error - dist_PreviousError) / 0.02;
        dist_PidSpeed = dist_P * dist_Error + dist_I * dist_TotalError/* + turn_D * turn_Derivitive*/;
        dist_PreviousError = dist_Error;

        std::cout << turn_PidSpeed << " " << dist_PidSpeed << std::endl;

        frontRightDriveMotor.move(-turn_PidSpeed + dist_PidSpeed);
        frontLeftDriveMotor.move(turn_PidSpeed + dist_PidSpeed);
        backRightDriveMotor.move(-turn_PidSpeed + dist_PidSpeed);
        backLeftDriveMotor.move(turn_PidSpeed + dist_PidSpeed);

        pros::delay(20);
    }
}


// functions below this line suffer from sensor error too much to be viable at this time

int turn_Error;
double turn_PidSpeed, turn_Derivitive, turn_TotalError, turn_PreviousError = 0.0;
float turn_P = 0.7;
float turn_I = 0.2;
float turn_D = 0.05;
std::vector<int> pastN;
double visAimAssist(int sig) {

    // Sig 1 is red
    // Sig 2 is blue
    // Sig 3 is yellow

    pros::vision_object_s_t object_array[5];
    pros::vision_object_s_t preprocessed;
    bool validSigFound = false;

    visionSensor.read_by_sig(0, sig, 5, object_array);
    for (int x = 0; x < 5; x++) {
        if (
                object_array[x].signature != 255 && 
                object_array[x].width > 10 &&
                object_array[x].width > object_array[x].height * 2
            ) {
            preprocessed = object_array[x];
            validSigFound = true;
            break;
        }
    }

    std::cout << visionSensor.get_object_count() << std::endl;

    if (validSigFound) {
        
        pastN.insert(pastN.begin(), preprocessed.x_middle_coord);
        pastN.resize(25, 158);
        int average = std::reduce(pastN.begin(), pastN.end()) / 25;

        turn_Error = 220 - average;
        turn_TotalError += turn_Error * 0.02;
        turn_Derivitive = (turn_Error - turn_PreviousError) / 0.02;
        turn_PidSpeed = turn_P * turn_Error + turn_I * turn_TotalError + turn_D * turn_Derivitive;

        turn_PreviousError = turn_Error;

        return turn_PidSpeed;
    }
    else {
        return 0.0;
    }    
}

void visPathfind(int sig, int time) {

    if (sig == 1) visionSensor.set_led(COLOR_RED);
    else if (sig == 2) visionSensor.set_led(COLOR_TEAL);
    else if (sig == 3) visionSensor.set_led(COLOR_GREEN);

    std::cout << "vis pathfind starting, sig: " << sig << std::endl;

    int turn_Error;
    double turn_PidSpeed, turn_Derivitive, turn_TotalError, turn_PreviousError = 0.0;
    float turn_P = 0.7;
    float turn_I = 0.18;
    float turn_D = 0.05;

    int dist_Error;
    double dist_PidSpeed, dist_Derivitive, dist_TotalError, dist_PreviousError = 0.0;
    float dist_P = 1.2;
    float dist_I = 0.15;
    float dist_D = 0.01;

    for (int x = 0; x < time; x += 20) {

        pros::vision_object_s_t object = visionSensor.get_by_sig(0, sig);

        std::cout << visionSensor.get_object_count() << std::endl;

        if (object.signature != 255 && object.width > 10) {
            
            std::cout << "object signiture detected " << object.signature << " ";

            turn_Error = 160 - object.x_middle_coord;
            turn_TotalError += turn_Error * 0.02;
            turn_Derivitive = (turn_Error - turn_PreviousError) / 0.02;
            turn_PidSpeed = turn_P * turn_Error + turn_I * turn_TotalError + turn_D * turn_Derivitive;

            dist_Error = 270 - object.width;
            dist_TotalError += dist_Error * 0.02;
            dist_Derivitive = (dist_Error - dist_PreviousError) / 0.02;
            dist_PidSpeed = dist_P * dist_Error + dist_I * dist_TotalError/* + turn_D * turn_Derivitive*/;

            std::cout << turn_PidSpeed << " " << dist_PidSpeed << std::endl;

            turn_PreviousError = turn_Error;
            dist_PreviousError = dist_Error;

            frontRightDriveMotor.move_velocity(turn_PidSpeed + dist_PidSpeed);
            frontLeftDriveMotor.move_velocity(-turn_PidSpeed + dist_PidSpeed);
            backRightDriveMotor.move_velocity(turn_PidSpeed + dist_PidSpeed);
            backLeftDriveMotor.move_velocity(-turn_PidSpeed + dist_PidSpeed);
        }
        else {
            frontRightDriveMotor.move(0);
            frontLeftDriveMotor.move(0);
            backRightDriveMotor.move(0);
            backLeftDriveMotor.move(0);
        }
        pros::delay(20);
    }
    visionSensor.set_led(COLOR_WHITE);
}

float offset[2] = {0.0f, 0.0f};
int count = 0;
void accumulateGyroOffset() {
    if (inertialSensor.is_calibrating()) return;

    pros::c::imu_accel_s_t accel = inertialSensor.get_accel();
    offset[0] += accel.x;
    offset[1] += accel.y;
    count += 1;

    if (count == 1000) {
        std::cout << "Averages after 10000: x = " << offset[0] / 1000 << " y = " << offset[1] / 1000 << std::endl;
    }
}
// these functions are not reliable, 20ms polling rate is just too slow to be useful especially after double integral
uint64_t previousTime = 0;
float displacement[2] = {0.0f, 0.0f};
float velocity[2] = {0.0f, 0.0f};
void gyroDisplace() {
    if (inertialSensor.is_calibrating()) return;

    uint64_t deltaTime = pros::micros() - previousTime;

    pros::c::imu_accel_s_t accel = inertialSensor.get_accel();
    float heading = inertialSensor.get_heading();

    // offsets hardcoded here
    velocity[0] += (accel.x - 0.0356652) * 9.80665 * deltaTime / 1000000.0;
    velocity[1] += (accel.y - 0.0623785) * 9.80665 * deltaTime / 1000000.0;

    displacement[0] += velocity[0] * deltaTime / 1000000.0;
    displacement[1] += velocity[1] * deltaTime / 1000000.0;

    std::cout << displacement[0] << std::endl;

    pros::screen::print(TEXT_MEDIUM, 2, "displacementx: %3f, displacementy: %3f", displacement[0], displacement[1]);
    pros::screen::print(TEXT_MEDIUM, 3, "velocityx: %3f, velocityy: %3f", velocity[0], velocity[1]);

    previousTime = pros::micros();
}