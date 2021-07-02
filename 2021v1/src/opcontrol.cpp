#include "main.h"
#include "portdef.h"
#include "chassis.h"
#include "roller.h"
#include "lift.h"
#include "tray.h"

// ALL OTHER MODULE INCLUDES HERE


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	int left = 0;					// left motor speed control
	int right = 0;				// right motor speed control

	double scaling = 1.0;

	extern int selection;

	bool autoRun = true;

	while (true) {

		if (DRIVE_MODE == 1) {
			// We want to do X-Drive TANK control
			int rightX = master.get_analog(ANALOG_RIGHT_X);
		  int rightY = master.get_analog(ANALOG_RIGHT_Y);
			int leftX = master.get_analog(ANALOG_LEFT_X);
		  int leftY = master.get_analog(ANALOG_LEFT_Y);

			if(abs(rightX) < DEAD_STICK) { rightX = 0; }
			if(abs(rightY) < DEAD_STICK) { rightY = 0; }
			if(abs(leftX) < DEAD_STICK) { leftX = 0; }
			if(abs(leftY) < DEAD_STICK) { leftY = 0; }


			setIndividualMotor((rightY - average(rightX, leftX)),
				 								 (leftY + average(rightX, leftX)),
												 (rightY + average(rightX, leftX)),
											   (leftY - average(rightX, leftX)));
		}
		else if (DRIVE_MODE == 2) {
			// We want to do X-Drive ARCADE control
			int rightX = master.get_analog(ANALOG_RIGHT_X);
		  int rightY = master.get_analog(ANALOG_RIGHT_Y);
			int leftX = master.get_analog(ANALOG_LEFT_X);
		  int leftY = master.get_analog(ANALOG_LEFT_Y);

			if(abs(rightX) < DEAD_STICK) { rightX = 0; }
			if(abs(rightY) < DEAD_STICK) { rightY = 0; }
			if(abs(leftX) < DEAD_STICK) { leftX = 0; }
			if(abs(leftY) < DEAD_STICK) { leftY = 0; }

			setIndividualMotor((rightY - leftX - rightX),
			 									 (rightY + leftX + rightX),
												 (rightY - leftX + rightX),
												 (rightY + leftX - rightX));
		}
		else if (DRIVE_MODE == 3) {
			// We are wanting to do standard ARCADE control
	    left = master.get_analog(ANALOG_LEFT_Y);
		  right = master.get_analog(ANALOG_LEFT_X);

			// implemenet dead stick control
			if(abs(left) < DEAD_STICK) { left = 0; }
			if(abs(right) < DEAD_STICK) { right = 0; }

			 chassisSetOpcontrol(left + right, left - right);
    }
		else if (DRIVE_MODE == 4) {
       // we are wanting to do standard TANK Control
			 left = master.get_analog(ANALOG_LEFT_Y);
			 right = master.get_analog(ANALOG_RIGHT_Y);

			 // implemenet dead stick control
			 if(abs(left) < DEAD_STICK) { left = 0; }
			 if(abs(right) < DEAD_STICK) { right = 0; }

       if(DEBUG_ON) {
				 std::cout << "Scaling: " << scaling ;
				 std::cout << " Left: " << left ;
			 }

       // lets do JOY stick scaling as well
			 left = (left * scaling);
			 right = (right * scaling);

			 if(DEBUG_ON) {
				std::cout << " Left Scaled: " << left << "\n" ;
			}
	  	 chassisSetOpcontrol(left, right);
    }
		else if (DRIVE_MODE == 5) {    // CURRENTLY DECOMMISSIONED UNTIL FURTHER DEVELOPMENT
			int leftX;
		  int leftY;

			if (master.get_digital(DIGITAL_UP)) {
				leftY = 200;
			}
			else if (master.get_digital(DIGITAL_DOWN)) {
				leftY = -200;
			}
			else {
				leftY = 0;
			}

			if (master.get_digital(DIGITAL_LEFT)) {
				leftX = 200;
			}
			else if (master.get_digital(DIGITAL_RIGHT)) {
				leftX = -200;
			}
			else {
				leftX = 0;
			}

		  int rightX = master.get_analog(ANALOG_RIGHT_X);

			if(abs(rightX) < DEAD_STICK) { rightX = 0; }
			if(abs(leftX) < DEAD_STICK) { leftX = 0; }
			if(abs(leftY) < DEAD_STICK) { leftY = 0; }

			setIndividualMotor((rightX - leftX - rightX),
			 									 (rightX + leftX + rightX),
												 (rightX - leftX + rightX),
												 (rightX + leftX - rightX));

		}

		if (master.get_digital(DIGITAL_R1)) {
			rollerForward(600);
		}
		else if (master.get_digital(DIGITAL_R2)) {
			rollerBackward(600);
		}
		else {
			rollerStop(0);
		}

		if (master.get_digital(DIGITAL_L1)) {
			liftRaiseManual(100);
		}
		else if (master.get_digital(DIGITAL_L2)) {
			liftRaiseManual(-90);
		}
		else {
			liftLock();
		}

		if (master.get_digital(DIGITAL_A)) {
			trayForward(50);
		}
		else if (master.get_digital(DIGITAL_B)) {
			trayBackward(50);
		}
		else {
			trayLock();
		}

		pros::delay(20);
	}
}
