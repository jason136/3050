#include "main.h"
#include "module.hpp"
#include "portdef.hpp"

// Miscellaneous motor construction
pros::Motor clawMotor(CLAW_MOTOR);
pros::Motor grabberMotor(GRABBER_MOTOR);

// Digital out for pneumatics 
pros::ADIDigitalOut pneumatic1(PNEUMATIC_PORT_1);
pros::ADIDigitalOut pneumatic2(PNEUMATIC_PORT_2);

void moveGrabber(int mode) {
    if (mode == 1) grabberMotor.move(127);
    else if (mode == -1) grabberMotor.move(-127);
    else {
        grabberMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        grabberMotor.move_velocity(0);
    }
}

void moveClaw(int mode) {
    if (mode == 1) clawMotor.move(127);
    else if (mode == -1) clawMotor.move(-127);
    else {
        clawMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        clawMotor.move_velocity(0);
    }
}

void togglePneumaticState(int mode) {
    pneumatic1.set_value(-mode);
    pneumatic2.set_value(-mode);
}
