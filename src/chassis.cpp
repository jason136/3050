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
}

void chassisStopDrive() {
    frontRightMotor.move(0);
    frontLeftMotor.move(0);
    backRightMotor.move(0);
    backLeftMotor.move(0);
}