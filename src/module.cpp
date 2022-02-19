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

pros::Vision visionSensor(VISION_PORT);

pros::vision_signature_s_t RED_SIG = pros::Vision::signature_from_utility(1, 7839, 9557, 8698, -1203, -615, -909, 3.000, 0);
pros::vision_signature_s_t BLUE_SIG = pros::Vision::signature_from_utility(2, -2639, -1809, -2224, 6611, 9223, 7917, 3.000, 0);
pros::vision_signature_s_t YELLOW_SIG = pros::Vision::signature_from_utility(3, 2053, 2849, 2451, -4491, -3983, -4237, 3.000, 0);

void initializeVision() {
    visionSensor.set_led(COLOR_WHITE);
    visionSensor.set_signature(1, &RED_SIG);
    visionSensor.set_signature(2, &BLUE_SIG);
    visionSensor.set_signature(3, &YELLOW_SIG);
}

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