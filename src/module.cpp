#include "main.h"
#include "module.hpp"
#include "portdef.hpp"

#include <errno.h>
extern int errno;

pros::Motor indexerMotor(INDEXER_MOTOR, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intakeMotor(INTAKE_MOTOR, pros::E_MOTOR_GEAR_RED, false, pros::E_MOTOR_ENCODER_DEGREES);

// Digital out for pneumatics 
pros::ADIDigitalOut pneumaticsLiftClaw(PNEUMATIC_LIFT_CLAW);
pros::ADIDigitalOut pneumaticsBackClaw(PNEUMATIC_BACK_CLAW);

pros::Vision visionSensor(VISION_PORT);

pros::Gps gpsSensor(GPS_PORT);

pros::vision_signature_s_t RED_SIG = pros::Vision::signature_from_utility(1, 7839, 9557, 8698, -1203, -615, -909, 3.000, 0);
pros::vision_signature_s_t BLUE_SIG = pros::Vision::signature_from_utility(2, -2639, -1809, -2224, 6611, 9223, 7917, 3.000, 0);
pros::vision_signature_s_t YELLOW_SIG = pros::Vision::signature_from_utility(3, 969, 1755, 1362, -5179, -4667, -4923, 3.000, 0);

void initializeVision() {
    visionSensor.set_led(COLOR_WHITE);
    visionSensor.set_signature(1, &RED_SIG);
    visionSensor.set_signature(2, &BLUE_SIG);
    visionSensor.set_signature(3, &YELLOW_SIG);
}

void initializeGps(double xInit, double yInit, double headingInit, double xOffset, double yOffset) {
    gpsSensor.set_data_rate(20);
    // if (xInit || yInit || headingInit) {
        gpsSensor.set_position(xInit, yInit, headingInit);
    // }
    // if (xOffset || yOffset) {
        gpsSensor.set_offset(xOffset, yOffset);
    // }

    std::cout << "gps initialized" << std::endl;
} 

void pollGps() {

    // pros::c::gps_status_s_t status = gpsSensor.get_status();

    // pros::screen::print(TEXT_MEDIUM, 2, "error: %3f", gpsSensor.get_error());
    // pros::screen::print(TEXT_MEDIUM, 3, "x: %3f, y: %3f", status.x, status.y);
    // pros::screen::print(TEXT_MEDIUM, 4, "pitch: %3f, yaw: %3f, roll: %3f", status.pitch, status.yaw, status.roll);

}

float distanceToTarget() {
    
}

bool liftPressed = false;
bool liftToggle = false;
void toggleLiftClawPneumatics(int input) {
    if (input) {
        liftPressed = true;
    }
    else if (liftPressed) {
        liftPressed = false;
        liftToggle = !liftToggle;
    }
    pneumaticsLiftClaw.set_value(liftToggle);
}

void spinIndexer(bool triggered) {
    if (triggered) {
        indexerMotor.move_velocity(-75);
    }
    else {
        indexerMotor.move_velocity(0);
    }
}

bool intakeSpinning = false;
void spinIntake(int speed) {
    if (speed && !intakeSpinning) {
        intakeSpinning = true;

        intakeMotor.move_velocity(speed);

    }
    else if (!speed && intakeSpinning) {
        intakeSpinning = false;
        intakeMotor.move_velocity(0);
    }
}

// void closeLiftClaw(void* param) {
//     pros::delay((int)param);
//     pneumaticsLiftClaw.set_value(0);
// }