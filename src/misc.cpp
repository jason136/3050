#include "main.h"
#include "misc.hpp"
#include "portdef.hpp"

#include <errno.h>
extern int errno;

pros::Motor intakeMotor1(INTAKE_1, pros::E_MOTOR_GEAR_RED, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intakeMotor2(INTAKE_2, pros::E_MOTOR_GEAR_RED, false, pros::E_MOTOR_ENCODER_DEGREES);

// Digital out for pneumatics 
pros::ADIDigitalOut pneumaticsIndexer(PNEUMATIC_INDEXER);
pros::ADIDigitalOut pneumaticsEndgame(PNEUMATIC_END_GAME);

pros::Vision visionSensor(VISION_PORT);

pros::vision_signature_s_t RED_SIG = pros::Vision::signature_from_utility(1, 7839, 9557, 8698, -1203, -615, -909, 3.000, 0);
pros::vision_signature_s_t BLUE_SIG = pros::Vision::signature_from_utility(2, -2639, -1809, -2224, 6611, 9223, 7917, 3.000, 0);
pros::vision_signature_s_t YELLOW_SIG = pros::Vision::signature_from_utility(3, 969, 1755, 1362, -5179, -4667, -4923, 3.000, 0);

void initializeVision() {
    visionSensor.set_led(COLOR_WHITE);
    visionSensor.set_signature(1, &RED_SIG);
    visionSensor.set_signature(2, &BLUE_SIG);
    visionSensor.set_signature(3, &YELLOW_SIG);
}

bool liftPressed = false;
bool liftToggle = false;
void toggleIndexer(int input) {
    if (input) {
        liftPressed = true;
    }
    else if (liftPressed) {
        liftPressed = false;
        liftToggle = !liftToggle;
    }
    pneumaticsIndexer.set_value(liftToggle);
}

void setIndexer(int input) {
    pneumaticsIndexer.set_value(!input);
}

std::uint32_t timeSinceExtend = 0;
std::uint32_t timeSinceRetract = 0;
void setIndexerFancy(int input) {
    if (input) {
        std::uint32_t deltaTime = pros::millis() - timeSinceExtend;
        if (timeSinceExtend > 500) {
            pneumaticsIndexer.set_value(0);
        }
    }

    timeSinceLast = pros::millis();
}

void setEndgame(int input) {
    pneumaticsEndgame.set_value(!input);
}

bool intakeSpinning = false;
void spinIntake(int speed) {
    if (speed && !intakeSpinning) {
        intakeSpinning = true;
        intakeMotor1.move_velocity(speed);
        intakeMotor2.move_velocity(-speed);
    }
    else if (!speed && intakeSpinning) {
        intakeSpinning = false;
        intakeMotor1.move_velocity(0);
        intakeMotor2.move_velocity(0);
    }
}

void stopIntakeDelayed(void* param) {
    pros::delay((int)param);
    spinIntake(0);
}