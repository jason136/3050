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
pros::ADIDigitalOut pneumatic1(PNEUMATIC_PORT_1);
pros::ADIDigitalOut pneumatic2(PNEUMATIC_PORT_2);

void moveLift(int LTop, int LBottom, int RTop, int RBottom) {
    if (LTop) leftTopLiftMotor.move(LTop);
    if (LBottom) leftBottomLiftMotor.move(LBottom);
    if (RTop) rightTopLiftMotor.move(RTop);
    if (RBottom) rightBottomLiftMotor.move(RBottom);
}

void liftLock(bool left=false, bool right=false) {
    if (!left) {
        leftTopLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        leftBottomLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        leftTopLiftMotor.move_velocity(0);
        leftBottomLiftMotor.move_velocity(0);
    }
    if (!right) {
        rightTopLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        rightBottomLiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        rightTopLiftMotor.move_velocity(0);
        rightBottomLiftMotor.move_velocity(0);
    }
}

void liftResetEncoder() {
    rightTopLiftMotor.tare_position();
    rightBottomLiftMotor.tare_position();
    leftTopLiftMotor.tare_position();
    leftBottomLiftMotor.tare_position();
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

void liftComplex(int left, int right) {
    if (right != 0 || left != 0) {
        if (right < 0) tempRight = -1;
        if (right > 0) tempRight = 1;
        if (right == 0) tempRight = 0;
        if (left < 0) tempLeft = -1;
        if (left > 0) tempLeft = 1;
        if (left == 0) tempLeft = 0;
        if (speed < 127) speed += 10;
    }
    else {
        if (speed > 0) speed -= 20;
        else if (speed < 0) speed = 0;
    }
    if (speed > 0) {
        std::cout << "lift with speed called" << std::endl;
        if (tempLeft < 0) speed *= 1;
        if (tempRight) {
            // moveLift(right * -1 * speed, right * -1 * speed, right * 1 * speed, right * 1 * speed);
            moveLift(0, 0, right * 1 * speed, right * -1 * speed);
            liftLock(false, true);
        }
        else if (tempLeft) {
            moveLift(left * -1 * speed, left * -1 * speed, left * 1 * speed, left * 1 * speed);
        }
    }
    else {
        liftLock(); 
    }
}