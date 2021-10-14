#include "main.h"
#include "api.h"
#include "portdef.h"
#include "auto.h"
#include "chassis.h"
#include "lift.h"
#include "roller.h"
#include "screen.h"

  extern const lv_img_dsc_t field_image;

  int selection;

  lv_obj_t * autonSelect;
  lv_obj_t * autonButton;
  lv_obj_t * autonButtunLabel;
  lv_obj_t * label;
  lv_obj_t * fieldImage;

	lv_style_t * defaultStyle = &lv_style_plain;

  lv_style_t * redStyle = createBtnStyle(defaultStyle, LV_COLOR_MAKE(255, 0, 0), LV_COLOR_MAKE(0, 0, 0),
  LV_COLOR_MAKE(102, 51, 51), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0));

  lv_style_t * blueStyle = createBtnStyle(defaultStyle, LV_COLOR_MAKE(0, 0, 255), LV_COLOR_MAKE(0, 0, 0),
	LV_COLOR_MAKE(46, 46, 107), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0));

	lv_style_t * autonLocStyle = createBtnStyle(defaultStyle, LV_COLOR_MAKE(255, 255, 0), LV_COLOR_MAKE(0, 0, 0),
	LV_COLOR_MAKE(89, 89, 42), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0), LV_COLOR_MAKE(0, 0, 0));

	lv_obj_t * autonButtons = (lv_obj_t *)malloc(sizeof(lv_obj_t) * 8);

static lv_res_t btn_click_action(lv_obj_t * btn) {
		uint8_t id = lv_obj_get_free_num(btn); //id usefull when there are multiple buttons

		switch (id) {
      case 1:
        char buffer[100];
        sprintf(buffer, "button was clicked %i milliseconds from start", pros::millis());
        lv_label_set_text(label, buffer);
        lv_btn_toggle(btn);
        break;
      case 2:
        lv_obj_set_hidden(autonSelect, true);
        break;
		}
		return LV_RES_OK;
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

	pros::Motor front_right_motor(FRONT_RIGHT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor front_left_motor(FRONT_LEFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor back_right_motor(BACK_RIGHT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor back_left_motor(BACK_LEFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Motor tray_motor(TRAY_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Motor lift_motor(LIFT_MOTOR, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Motor right_roller_motor(RIGHT_ROLLER_MOTOR, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor left_roller_motor(LEFT_ROLLER_MOTOR, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);

  autonSelect = createPage();
  lv_obj_set_hidden(autonSelect, false);

  autonButton = createBtn(autonSelect, 50, 60, 80, 50, 1, "1");
  setBtnStyle(autonLocStyle, autonButton);
  memcpy(&autonButtons[2], autonButton, sizeof(lv_obj_t));

  autonButton = createBtn(autonSelect, 320, 60, 80, 50, 1, "1");
  setBtnStyle(autonLocStyle, autonButton);
  memcpy(&autonButtons[3], autonButton, sizeof(lv_obj_t));

  autonButton = createBtn(autonSelect, 50, 120, 80, 50, 1, "2");
  setBtnStyle(autonLocStyle, autonButton);
  memcpy(&autonButtons[4], autonButton, sizeof(lv_obj_t));

  autonButton = createBtn(autonSelect, 320, 120, 80, 50, 1, "2");
  setBtnStyle(autonLocStyle, autonButton);
  memcpy(&autonButtons[5], autonButton, sizeof(lv_obj_t));

  autonButton = createBtn(autonSelect, 70, 0, 150, 50, 1, "Red");
  setBtnStyle(redStyle, autonButton);
  memcpy(&autonButtons[0], autonButton, sizeof(lv_obj_t));
  autonButton = createBtn(autonSelect, 230, 0, 150, 50, 2, "Blue");
  setBtnStyle(blueStyle, autonButton);
  memcpy(&autonButtons[1], autonButton, sizeof(lv_obj_t));

  autonButton = createBtn(autonSelect, 400, 120, 140, 50, 2, "select");
  setBtnStyle(autonLocStyle, autonButton);
  memcpy(&autonButtons[6], autonButton, sizeof(lv_obj_t));

	for (int x = 0; x < 7; x++) {
	  lv_btn_set_action(&autonButtons[x], LV_BTN_ACTION_CLICK, btn_click_action);
	}

  LV_IMG_DECLARE(field_image);
  lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(img1, &field_image);
  lv_obj_set_size(img1, 170, 170);
  lv_obj_set_pos(img1, 160, 68);



  // autonButton = createBtn(lv_scr_act(), 25, 25, 100, 50, 0, "btn0");
	// lv_obj_set_free_num(autonButton, 0);
	// lv_btn_set_action(autonButton, LV_BTN_ACTION_CLICK, btn_click_action);
	// setBtnStyle(autonButtonStyle, autonButton);

	label = lv_label_create(autonSelect, NULL);
	lv_label_set_text(label, "Button has not been clicked yet");
	lv_obj_align(label, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0);

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
