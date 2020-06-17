#include "main.h"
#include "init.h"
#include "portdef.h"

// Character array holdign the vaious labels for the autonomousroutines - labels are
// the function names being called
const char* titles[] = {"LUNAR ECLIPSE", "New Moon", "Waxing Gibbous", "Waning Gibbous", "Full Moon"};

int selection;													// Select script to run
unsigned int scriptNumber = 0;					// scriptNumber which will be passed

static bool selectionMade = false;			// Sart fresh - no selection made yet

// LEFT lcd display button call back routine
// Button pressed decrements in the selection array
void on_left_button() {
	static bool pressed = false;
  if(!selectionMade){
		pros::lcd::clear_line(4);
		if (scriptNumber != 0) {
			scriptNumber--;
		  pros::lcd::print(2, "Script#: %d\n", scriptNumber);
      pros::lcd::print(3, titles[scriptNumber]);
 	  } else {
		  pros::lcd::print(2, "Script#: %d Can't decrement\n", scriptNumber);
		  pros::lcd::print(3, titles[scriptNumber]);
	  }
	}
}

// CENTER make a selection or deselect the choosen option
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		selection = scriptNumber;
		pros::lcd::set_text(4, "<< SELECTED ! >>");
		selectionMade = true;
	} else {
		pros::lcd::set_text(4, "<< DE-SELECTED >>");
		selection = 0;					// Reset selection
    selectionMade = false;
	}
}

// RIGHT button, increments the array index to next selection
void on_right_button() {
	static bool pressed = false;
  if(!selectionMade){
		pros::lcd::clear_line(4);
		if (scriptNumber < (NUM_SCRIPTS - 1)) {
			scriptNumber++;
		  pros::lcd::print(2, "Script#: %d\n", scriptNumber);
		  pros::lcd::print(3, titles[scriptNumber]);
		} else {
			pros::lcd::print(2, "Script#: %d idk, Google it\n", scriptNumber);
		  pros::lcd::print(3, titles[scriptNumber]);
		}
	}
}

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

	pros::Motor front_right_motor(RIGHT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor front_left_motor(LEFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Motor tray_motor1(TRAY_MOTOR1_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor tray_motor2(TRAY_MOTOR2_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Motor right_lift_motor(RIGHT_LIFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor left_lift_motor(LEFT_LIFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Motor right_roller_motor(RIGHT_ROLLER_MOTOR_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor left_roller_motor(LEFT_ROLLER_MOTOR_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::lcd::initialize();
	pros::lcd::clear_line(1);
	pros::lcd::clear_line(2);
	pros::lcd::set_text(1, "WHOMST HAS SUMMONED ");
	pros::lcd::set_text(2, "THE ALMIGHTLY MRS. BENJAMIN");

	pros::lcd::register_btn0_cb(on_left_button);
	pros::lcd::register_btn1_cb(on_center_button);
	pros::lcd::register_btn2_cb(on_right_button);
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
