#include "main.h"
#include "module.hpp"
#include "portdef.hpp"

// Miscellaneous motor construction
pros::Motor clawMotor(CLAW_MOTOR);
pros::Motor grabberMotor(GRABBER_MOTOR);

// Digital out for pneumatics 
pros::ADIDigitalOut pneumaticsLiftClaw1(PNEUMATIC_LIFT_CLAW_1);
pros::ADIDigitalOut pneumaticsLiftClaw2(PNEUMATIC_LIFT_CLAW_2);
pros::ADIDigitalOut pneumaticsBackClaw1(PNEUMATIC_BACK_CLAW_1);
pros::ADIDigitalOut pneumaticsBackClaw2(PNEUMATIC_BACK_CLAW_2);

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

void toggleLiftClawPneumatics(int mode) {
    pneumaticsLiftClaw1.set_value(!mode);
    pneumaticsLiftClaw2.set_value(!mode);
}

void toggleBackClawPneumatics(int mode) {
    pneumaticsBackClaw1.set_value(!mode);
    pneumaticsBackClaw2.set_value(!mode);
}

void closeLiftClaw(void* param) {
    pros::delay((int)param);
    pneumaticsLiftClaw1.set_value(0);
    pneumaticsLiftClaw2.set_value(0);
}

void closeBackClaw(void* param) {
    pros::delay((int)param);
    pneumaticsBackClaw1.set_value(0);
    pneumaticsBackClaw2.set_value(0);
}