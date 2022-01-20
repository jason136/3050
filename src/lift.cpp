#include "main.h"
#include "portdef.hpp"
#include "lift.hpp"

// Setup the motor definition for the lift motor
pros::Motor rightTopLiftMotor(RIGHT_TOP_LIFT_MOTOR);
pros::Motor rightBottomLiftMotor(RIGHT_BOTTOM_LIFT_MOTOR);
pros::Motor leftTopLiftMotor(LEFT_TOP_LIFT_MOTOR);
pros::Motor leftBottomLiftMotor(LEFT_BOTTOM_LIFT_MOTOR);
pros::Motor clawMotor(CLAW_MOTOR);
pros::Motor grabberMotor(GRABBER_MOTOR);

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
    pneumatic1.set_value(-mode);
    pneumatic2.set_value(-mode);
}

void moveClaw(int mode) {
    if (mode == 1) clawMotor.move(127);
    else if (mode == -1) clawMotor.move(-127);
    else {
        clawMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        clawMotor.move_velocity(0);
    }
}

void moveGrabber(int mode) {
    if (mode == 1) grabberMotor.move(127);
    else if (mode == -1) grabberMotor.move(-127);
    else {
        grabberMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        grabberMotor.move_velocity(0);
    }
}

int speed;
int tempRight;
int tempLeft;

void differential(int right, int left) {
    if (right != 0 || left != 0) {
        tempRight = right;
        tempLeft = left;
        if (speed < 127) speed += 10;
    }
    else {
        if (speed > 0) speed -= 10;
        else if (speed < 0) speed = 0;
    }
    if (speed > 0) {
        if (tempRight) {
            moveLift(right * 1 * speed, right * 1 * speed, right * -1 * speed, right * -1 * speed);
        }
        else if (tempLeft) {
            moveLift(left * -1 * speed, left * 1 * speed, left * -1 * speed, left * 1 * speed);
        }
    }
    else {
        liftLock(); 
    }
}