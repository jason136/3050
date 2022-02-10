#include "main.h"
#include "module.hpp"
#include "portdef.hpp"

// Miscellaneous motor construction
pros::Motor clawMotor(CLAW_MOTOR);
pros::Motor grabberMotor(GRABBER_MOTOR);

// Digital out for pneumatics 
pros::ADIDigitalOut pneumaticsMoGoal(PNEUMATIC_PORT_MOBILE_GOAL);
pros::ADIDigitalOut pneumaticsAutonomous1(PNEUMATIC_PORT_AUTONOMOUS_1);
pros::ADIDigitalOut pneumaticsAutonomous2(PNEUMATIC_PORT_AUTONOMOUS_2);

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

void toggleMoGoalPneumatics(int mode) {
    pneumaticsMoGoal.set_value(-mode);
}

void toggleAutonPneumatics(int mode) {

    pneumaticsAutonomous1.set_value(!mode);
    pneumaticsAutonomous2.set_value(!mode);

}