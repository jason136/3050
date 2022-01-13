#include "main.h"
#include "portdef.hpp"
#include "lift.hpp"

// Setup the motor definition for the lift motor
pros::Motor rightTopLiftMotor(RIGHT_TOP_LIFT_MOTOR);
pros::Motor rightBottomLiftMotor(RIGHT_BOTTOM_LIFT_MOTOR);
pros::Motor leftTopLiftMotor(LEFT_TOP_LIFT_MOTOR);
pros::Motor leftBottomLiftMotor(LEFT_BOTTOM_LIFT_MOTOR);

// Digital out for pneumatics 
pros::ADIDigitalOut pneumatic1 (PNEUMATIC_PORT_1);
pros::ADIDigitalOut pneumatic2 (PNEUMATIC_PORT_2);

void moveLift(int RTop, int RBottom, int LTop, int LBottom) {
    rightTopLiftMotor.move(RTop);
    rightBottomLiftMotor.move(RBottom);
    leftTopLiftMotor.move(LTop);
    leftBottomLiftMotor.move(LBottom);
}

void liftLock() {
    rightTopLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightBottomLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftTopLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftBottomLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightTopLiftMotor.move_velocity(0);
    rightBottomLiftMotor.move_velocity(0);
    leftTopLiftMotor.move_velocity(0);
    leftBottomLiftMotor.move_velocity(0);
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
    pneumatic1.set_value(mode);
    pneumatic2.set_value(mode);
}

void differential(int right, int left) {
    if (right) {
        moveLift(right * 80, right * 80, right * -80, right * -80);
    }
    else if (left) {
        moveLift(left * -127, left * 127, left * -127, left * 127);
    }
    else {
        liftLock();
    }
}