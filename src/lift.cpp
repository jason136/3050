#include "main.h"
#include "portdef.hpp"
#include "lift.hpp"

// Setup the motor definition for the lift motor
pros::Motor rightTopLiftMotor(RIGHT_TOP_LIFT_MOTOR);
pros::Motor rightBottomLiftMotor(RIGHT_BOTTOM_LIFT_MOTOR);
pros::Motor leftTopLiftMotor(LEFT_TOP_LIFT_MOTOR);
pros::Motor leftBottomLiftMotor(LEFT_BOTTOM_LIFT_MOTOR);

// Digital out for pneumatics 
pros::ADIDigitalOut pneumatic (PNEUMATIC_PORT);

void moveLift(int RTop, int RBottom, int LTop, int LBottom) {
    rightTopLiftMotor.move(RTop);
    rightBottomLiftMotor.move(RBottom);
    leftTopLiftMotor.move(LTop);
    leftBottomLiftMotor.move(LBottom);
}

void liftLock() {
  rightTopLiftMotor.move(0);
  rightBottomLiftMotor.move(0);
  leftTopLiftMotor.move(0);
  leftBottomLiftMotor.move(0);
  if (rightTopLiftMotor.get_brake_mode() != 2 ) {
    rightTopLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightBottomLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftTopLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftBottomLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
}

void liftResetEncoder() {
  rightTopLiftMotor.tare_position();
  rightBottomLiftMotor.tare_position();
  leftTopLiftMotor.tare_position();
  leftBottomLiftMotor.tare_position();

  if(DEBUG_ON){
    std::cout << "lift encoder reset" << std::endl; 
  }
}

pros::motor_brake_mode_e_t getliftBrakeMode() {
  return rightTopLiftMotor.get_brake_mode();
}

void togglePneumaticState(int mode) {
    pneumatic.set_value(mode);
}

void differential (char side, int mode) {
    if (side == 'r') {
        if (mode) moveLift(mode * 127, mode * 127, mode * 127, mode * 127);
        else liftLock();
    }
    else if (side = 'l') {
        if (mode) moveLift(mode * -127, mode * 127, mode * -127, mode * 127);
        else liftLock();
    }
}