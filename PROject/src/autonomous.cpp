#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

using namespace okapi;

const int BACK_LEFT_MOTOR = 1;
const int FRONT_LEFT_MOTOR = 2;
const int BACK_RIGHT_MOTOR = 3;
const int FRONT_RIGHT_MOTOR = 4;
const auto WHEEL_DIAMETER = 4_in;
const auto CHASSIS_WIDTH = 13.5_in;

auto chassis = ChassisControllerFactory::create(
    BACK_LEFT_MOTOR, FRONT_LEFT_MOTOR, BACK_RIGHT_MOTOR, FRONT_RIGHT_MOTOR,
    AbstractMotor::gearset::green, {WHEEL_DIAMETER, CHASSIS_WIDTH});

void autonomous() {

  chassis.moveDistance(1_m);
  chassis.turnAngle(90_deg);
  chassis.moveDistance(1.5_ft);
}
