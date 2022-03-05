#include "main.h"
#include "portdef.hpp"
#include "lift.hpp"

// Setup the motor definition for the lift motor
pros::Motor rightTopLiftMotor(RIGHT_TOP_LIFT_MOTOR, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBottomLiftMotor(RIGHT_BOTTOM_LIFT_MOTOR, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftTopLiftMotor(LEFT_TOP_LIFT_MOTOR, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBottomLiftMotor(LEFT_BOTTOM_LIFT_MOTOR, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

void moveLift(int LTop, int LBottom, int RTop, int RBottom) {
    if (LTop) leftTopLiftMotor.move(LTop);
    if (LBottom) leftBottomLiftMotor.move(LBottom);
    if (RTop) rightTopLiftMotor.move(RTop);
    if (RBottom) rightBottomLiftMotor.move(RBottom);
}

void liftLock(pros::motor_brake_mode_e_t brakeType, bool left=true, bool right=true) {
    if (left) {
        leftTopLiftMotor.set_brake_mode(brakeType);
        leftBottomLiftMotor.set_brake_mode(brakeType);
        leftTopLiftMotor.move_velocity(0);
        leftBottomLiftMotor.move_velocity(0);
    }
    if (right) {
        rightTopLiftMotor.set_brake_mode(brakeType);
        rightBottomLiftMotor.set_brake_mode(brakeType);
        rightTopLiftMotor.move_velocity(0);
        rightBottomLiftMotor.move_velocity(0);
    }
}

void resetLiftEncoders() {
    rightTopLiftMotor.tare_position();
    rightBottomLiftMotor.tare_position();
    leftTopLiftMotor.tare_position();
    leftBottomLiftMotor.tare_position();
}

pros::motor_brake_mode_e_t getliftBrakeMode() {
    return rightTopLiftMotor.get_brake_mode();
}

int liftSpeed = 0;

void liftComplex(int left, int right) {

    std::cout << liftSpeed << std::endl;

    if (left) {
        if (liftSpeed < 127) liftSpeed += 20;
        std::cout << "lift with liftSpeed called" << std::endl;
        
        moveLift(left * 1 * liftSpeed, left * 1 * liftSpeed, left * -1 * liftSpeed, left * -1 * liftSpeed);
    }
    else if (right) {
        liftSpeed = 0;
        moveLift(0, 0, right * 1 * 127, right * -1 * 127);
        liftLock(pros::E_MOTOR_BRAKE_HOLD, true, false);
    }
    else {
        if (liftSpeed > 0) {
            liftSpeed -= 10;
            liftLock(pros::E_MOTOR_BRAKE_BRAKE);
        }
        else if (liftSpeed <= 0) {
            liftSpeed = 0;
            std::cout << "holding" << std::endl;
            liftLock(pros::E_MOTOR_BRAKE_HOLD);
        }
    }
}