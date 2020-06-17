#include "main.h"
using namespace okapi;

#define BACK_LEFT_MOTOR 1
#define FRONT_LEFT_MOTOR 2
#define BACK_RIGHT_MOTOR 3
#define FRONT_RIGHT_MOTOR 4
#define PUSHY_THINGY_MOTOR 5
#define ALBA_MOTOR 6
#define LEFT_ROLLY_MOTOR 7
#define RIGHT_ROLLY_MOTOR 8

auto drive = ChassisControllerFactory::create(
    1, 2, 3, 4, AbstractMotor::gearset::green, {4_in, 11.5_in});

/**
 * Runs the operator control code. This function will be started in its own
 * task with the default priority and stack size whenever the robot is
 * enabled via the Field Management System or the VEX Competition Switch in
 * the operator control mode.
 *
 * If no competition control is connected, this function will run
 * immediately following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart
 * the task, not resume it from where it left off.
 */

void opcontrol() {

  pros::lcd::set_text(3, "user control done started");

  Controller masterController;

  Motor pusher_motor = 5_rmtr;
  Motor alba_motor = 6_rmtr;
  Motor left_rolly_motor = 7_rmtr;
  Motor right_rolly_motor = 8_rmtr;

  ControllerButton push_forwards(ControllerDigital::R1);
  ControllerButton push_backwards(ControllerDigital::R2);
  ControllerButton roll_forwards(ControllerDigital::L1);
  ControllerButton roll_backwards(ControllerDigital::L2);
  ControllerButton alba_up(ControllerDigital::A);
  ControllerButton alba_down(ControllerDigital::B);

  while (true) {
    pros::lcd::print(0, "%d %d %d",
                     (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
                     (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
                     (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

    drive.arcade(masterController.getAnalog(ControllerAnalog::leftY),
                 masterController.getAnalog(ControllerAnalog::rightY));

    if (push_forwards.isPressed()) {
      pusher_motor.moveVoltage(12000);
    } else if (push_backwards.isPressed()) {
      pusher_motor.moveVoltage(-12000);
    } else {
      pusher_motor.moveVoltage(0);
    }

    if (alba_up.isPressed()) {
      alba_motor.moveVoltage(12000);
    } else if (alba_down.isPressed()) {
      alba_motor.moveVoltage(-12000);
    } else
      alba_motor.moveVoltage(0);

    if (roll_forwards.isPressed()) {
      left_rolly_motor.moveVoltage(12000);
      right_rolly_motor.moveVoltage(-12000);
    } else if (roll_backwards.isPressed()) {
      left_rolly_motor.moveVoltage(-12000);
      right_rolly_motor.moveVoltage(12000);
    } else {
      left_rolly_motor.moveVoltage(0);
      right_rolly_motor.moveVoltage(0);
    }
    pros::delay(20);
  }
}
