#include "main.h"
#include "api.h"
#include "portdef.h"
#include "auto.h"
#include "chassis.h"
#include "lift.h"
#include "roller.h"
#include "screen.h"

extern int autonomousPreSet;
  
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// Motor Setup
	// GEARSET_36 -- RED
	// GEARSET_18 -- GREEN (default)
	// GEARSET_6 -- BLUE

	pros::Motor front_right_motor(FRONT_RIGHT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor front_left_motor(FRONT_LEFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor back_right_motor(BACK_RIGHT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor back_left_motor(BACK_LEFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Motor tray_motor(TRAY_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Motor lift_motor(LIFT_MOTOR, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Motor right_roller_motor(RIGHT_ROLLER_MOTOR, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor left_roller_motor(LEFT_ROLLER_MOTOR, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
  
  loadScreen();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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

void autonomous() {
	// We are calling a autonomous function based on the selection
  // we made on the LCD

	/*
	switch(selection) {
		case 0 :
			pros::lcd::print(4, "Script#: %d\n", selection);
      pros::lcd::print(5, titles[selection]);
      skillRun();
      break;

		case 1 :
			pros::lcd::print(4, "Script#: %d\n", selection);
      pros::lcd::print(5, titles[selection]);
      autoRedLeft();
      break;

    case 2 :
      pros::lcd::print(4, "Script#: %d\n", selection);
      pros::lcd::print(5, titles[selection]);
    	autoBlueLeft();
      break;

    case 3 :
    	pros::lcd::print(4, "Script#: %d\n", selection);
      pros::lcd::print(5, titles[selection]);
      autoRedRight();
      break;

    case 4 :
      pros::lcd::print(4, "Script#: %d\n", selection);
      pros::lcd::print(5, titles[selection]);
      autoBlueRight();
      break;

    default :
      // this should never happen as selection is alwasy inialized as 0
      // does the case of '0' is in essence the defualt.
      break;
  }
*/
}
