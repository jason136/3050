#include "main.h"
#include "portdef.hpp"
#include "flywheel.hpp"

// Setup the motor definition for the lift motor
pros::Motor flywheel1(FLYWHEEL_1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor flywheel2(FLYWHEEL_2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

void spinFlywheel(int speed) {
    flywheel1.move(speed);
    flywheel2.move(-speed);
}

void stopFlywheel(pros::motor_brake_mode_e_t brakeType) {
    flywheel1.set_brake_mode(brakeType);
    flywheel2.set_brake_mode(brakeType);
    flywheel1.move_velocity(0);
    flywheel2.move_velocity(0);
}

void resetFlywheelEncoders() {
    flywheel1.tare_position();
    flywheel2.tare_position();
}

pros::motor_brake_mode_e_t getliftBrakeMode() {
    return flywheel1.get_brake_mode();
}

// int liftSpeed = 0;
// void liftComplex(int left, int right) {
//     if (left) {
//         if (liftSpeed < 127) liftSpeed += 20;        
//         moveLift(left * 1 * liftSpeed, left * 1 * liftSpeed, left * -1 * liftSpeed, left * -1 * liftSpeed);
//     }
//     else if (right) {
//         liftSpeed = 0;
//         moveLift(0, 0, right * 1 * 127, right * -1 * 127);
//         liftLock(pros::E_MOTOR_BRAKE_HOLD, true, false);
//     }
//     else {
//         if (liftSpeed > 0) {
//             liftSpeed -= 10;
//             liftLock(pros::E_MOTOR_BRAKE_BRAKE);
//         }
//         else if (liftSpeed <= 0) {
//             liftSpeed = 0;
//             liftLock(pros::E_MOTOR_BRAKE_HOLD);
//         }
//     }
// }