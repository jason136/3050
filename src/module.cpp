#include "main.h"
#include "module.hpp"
#include "portdef.hpp"

// Digital out for pneumatics 
pros::ADIDigitalOut pneumaticsLiftClaw(PNEUMATIC_LIFT_CLAW);
pros::ADIDigitalOut pneumaticsBackClaw(PNEUMATIC_BACK_CLAW);

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

bool liftPressed = false;
bool liftToggle = false;
void toggleLiftClawPneumatics(int toggle) {
    if (toggle) {
        liftPressed = true;
    }
    else if (liftPressed) {
        liftPressed = false;
        liftToggle = !liftToggle;
    }
    pneumaticsLiftClaw.set_value(liftToggle);
}

bool clawPressed = false;
bool clawToggle = false;
void toggleBackClawPneumatics(int toggle) {
    if (toggle) {
        clawPressed = true;
    }
    else if (clawPressed) {
        clawPressed = false;
        clawToggle = !clawToggle;
    }
    pneumaticsBackClaw.set_value(clawToggle);
}

void setLiftClawPneumatics(int mode) {
    pneumaticsLiftClaw.set_value(!mode);
}

void setBackClawPneumatics(int mode) {
    pneumaticsBackClaw.set_value(!mode);
}

void closeLiftClaw(void* param) {
    pros::delay((int)param);
    pneumaticsLiftClaw.set_value(0);
}

void closeBackClaw(void* param) {
    pros::delay((int)param);
    pneumaticsBackClaw.set_value(0);
}