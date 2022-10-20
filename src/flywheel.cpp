#include "main.h"
#include "portdef.hpp"
#include "flywheel.hpp"

pros::Motor flywheel1(FLYWHEEL_1, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor flywheel2(FLYWHEEL_2, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);

bool flywheelSpinning = false;
void spinFlywheel(bool pressed, int speed) {
    if (pressed && !flywheelSpinning) {
        flywheelSpinning = true;

        flywheel1.move_velocity(speed);
        flywheel2.move_velocity(-speed);

    }
    else if (!pressed) {
        flywheelSpinning = false;
        stopFlywheel(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_COAST);
    }
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

void displayFlywheelData() {
    pros::screen::print(TEXT_SMALL, 1, "velocity: %3f", flywheel1.get_actual_velocity());
    pros::screen::print(TEXT_SMALL, 2, "draw: %3f", flywheel1.get_current_draw());
    pros::screen::print(TEXT_SMALL, 3, "power: %3f", flywheel1.get_power());
    pros::screen::print(TEXT_SMALL, 4, "temperature: %3f", flywheel1.get_temperature());
    pros::screen::print(TEXT_SMALL, 5, "effeciency: %3f", flywheel1.get_efficiency());
    pros::screen::print(TEXT_SMALL, 6, "flags: %3f, faults: %3f", flywheel1.get_flags(), flywheel1.get_faults());

    pros::screen::print(TEXT_SMALL, 7, "velocity: %3f", flywheel2.get_actual_velocity());
    pros::screen::print(TEXT_SMALL, 8, "draw: %3f", flywheel2.get_current_draw());
    pros::screen::print(TEXT_SMALL, 9, "power: %3f", flywheel2.get_power());
    pros::screen::print(TEXT_SMALL, 10, "temperature: %3f", flywheel2.get_temperature());
    pros::screen::print(TEXT_SMALL, 11, "effeciency: %3f", flywheel2.get_efficiency());
    pros::screen::print(TEXT_SMALL, 12, "flags: %3f, faults: %3f", flywheel2.get_flags(), flywheel2.get_faults());
}

bool flywheelPressed = false;
bool flywheelToggle = false;
void toggleVariableFlywheel(bool input) {
    if (input) {
        flywheelPressed = true;
    }
    else if (flywheelPressed) {
        flywheelPressed = false;
        flywheelToggle = !flywheelToggle;
    }

    // if (flywheelToggle) {
        
    //     double error = turnAngle;
    //     double pidSpeed, derivitive, totalError, previousError = 0.0;
    //     float p = 3.0;
    //     float i = 0.1;
    //     // float i = 0.01791;
    //     float d = 0.012;

    //     for (int x = 0; x < time; x += 20)  {
    //         std::cout << error << std::endl;

    //         error = fabs(turnAngle) - fabs(intertialSensor.get_rotation());
    //         totalError += error * 0.02;
    //         derivitive = (error - previousError) / 0.02;
    //         pidSpeed = p * error + i * totalError + d * derivitive;

    //         frontRightDriveMotor.move_velocity(-direction * (pidSpeed * 200));
    //         frontLeftDriveMotor.move_velocity(direction * (pidSpeed * 200));
    //         backRightDriveMotor.move_velocity(-direction * (pidSpeed * 200));
    //         backLeftDriveMotor.move_velocity(direction * (pidSpeed * 200));

    //         previousError = error;
    //         pros::delay(20);
    //     }
    // }
    // else {
    //     stopFlywheel(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);
    // }
} 
