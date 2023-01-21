#include "main.h"
#include "portdef.hpp"
#include "flywheel.hpp"
#include <atomic>
#include <vector>
#include <numeric>

pros::Motor flywheel1(FLYWHEEL_1, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor flywheel2(FLYWHEEL_2, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);

std::atomic<int> taskFlywheelSpeed (0);
std::atomic<bool> taskSpinFlywheel (false);
void spinFlywheel(bool pressed) {
    if (pressed && !taskSpinFlywheel) {
        taskSpinFlywheel = true;
    }
    else if (!pressed && taskSpinFlywheel) {
        taskSpinFlywheel = false;
    }
}

void setFlywheelSpeed(int speed) {
    taskFlywheelSpeed = speed;
}

void flywheelPIDTask(void * param) {
    // p / i ~ 1 / 30
    double error, pidSpeed, derivitive, totalError, previousError = 0.0;
    float p = 0.969;
    float i = 0.0000069;
    float d = 0.0;

    std::vector<float> dampener;
    
    std::cout << "taskstart" << std::endl;

    int count = 0;

    while (true) {
        if (!taskSpinFlywheel.load()) {
            error, pidSpeed, derivitive, totalError, previousError = 0.0;
            // std::cout << "off" << std::endl;
            flywheel1.move(0);
            flywheel2.move(0);
            pros::delay(10);
            continue;
        }

        int flywheelSpeed = taskFlywheelSpeed.load();
        float averageSpeed = (flywheel1.get_actual_velocity() - flywheel2.get_actual_velocity()) / 2.0;
        
        dampener.push_back(averageSpeed);
        if (dampener.size() >= 6) dampener.erase(dampener.begin());
        float dampedSpeed = std::accumulate(dampener.begin(), dampener.end(), 0.0) / dampener.size();
        
        error = dampedSpeed - flywheelSpeed;

        totalError += error * 0.02;
        derivitive = (error - previousError) / 0.02;
        pidSpeed = p * error + i * totalError + d * derivitive;

        float voltOffset = (flywheelSpeed / 600.0) * 127.0;

        std::cout << "pidSpeed: " << (pidSpeed - voltOffset)  << " error: " << error << std::endl;

        flywheel1.move(-(pidSpeed - voltOffset));
        flywheel2.move((pidSpeed - voltOffset));

        previousError = error;
        pros::delay(10);
    }
}

void stopFlywheel() {
    flywheel1.move_velocity(0);
    flywheel2.move_velocity(0);
}


    // flywheel1.set_brake_mode(brakeType);
    // flywheel2.set_brake_mode(brakeType);
        // stopFlywheel(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_COAST);

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
