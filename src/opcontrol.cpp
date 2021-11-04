#include "main.h"
#include "portdef.hpp"
#include "chassis.hpp"
#include "conveyor.hpp"
#include "lift.hpp"
#include "screen.hpp"
#include "file.hpp"
#include "opcontrol.hpp"

// Datastructures for recordable autonomous
double instJoysticks[4];
int instButtons[3];

// Datastructures used for console and screen diagnostics
double buffer[12];
char chassisData[400];

extern int selection;

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

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

	pros::Task opcontrolThread(opcontrolLoop);

}

void opcontrolLoop(void * param) {
    while (true) {
		pros::Mutex mutex;
		mutex.take(25);

		instJoysticks[0] = master.get_analog(ANALOG_RIGHT_X);
		instJoysticks[1] = master.get_analog(ANALOG_RIGHT_Y);
		instJoysticks[2] = master.get_analog(ANALOG_LEFT_X);
		instJoysticks[3] = master.get_analog(ANALOG_LEFT_Y);

		if (partner.get_digital(DIGITAL_R1)) {
			instButtons[0] = 1;
		}
		else if (partner.get_digital(DIGITAL_R2)) {
			instButtons[0] = -1;
		}
		else {
			instButtons[0] = -0;
		}
		if (master.get_digital(DIGITAL_L1)) {
			instButtons[1] = 1;
		}
		else if (master.get_digital(DIGITAL_L2)) {
			instButtons[1] = -1;
		}
		else {
			instButtons[1] = -0;
		}
		if (partner.get_digital(DIGITAL_UP)) {
			instButtons[2] = 1;
		}
		else if (partner.get_digital(DIGITAL_DOWN)) {
			instButtons[2] = -1;
		}
		else {
			instButtons[2] = -0;
		}

		mutex.give();

		processInput(&instJoysticks[0], &instButtons[0]);
		
		// Get data from module functions
		getChassisDiag(buffer);
		sprintf(chassisData,
		"Fn R Mtr V: %f -- T: %f -- E: %f\n"
		"Fn L Mtr V: %f -- T: %f -- E: %f\n"
		"Bk R Mtr V: %f -- T: %f -- E: %f\n"
		"Bk L Mtr V: %f -- T: %f -- E: %f\n",
		buffer[0], buffer[4], buffer[8],
		buffer[1], buffer[5], buffer[9],
		buffer[2], buffer[6], buffer[10],
		buffer[3], buffer[7], buffer[11]);

		updateDiag(&chassisData[0]);

		if (false) {
			std::cout << chassisData;
		}

		pros::delay(20);
	}
}

void startRecordThread() {
    clearVectors();

	pros::Task recordThread(recordLoop);

	std::cout << "record loop started" << std::endl;
}

void recordLoop(void * param) {
	int startTime = pros::millis();
    char countdown[20];
    sprintf(countdown, "press A");
    master.set_text(1, 1, countdown);
    while (pros::millis() < startTime + 15000) {
        if (master.get_digital(DIGITAL_A)) {
            break;
        }
    }

    //master.clear_line(1);
    sprintf(countdown, "recording");
    master.set_text(1, 1, countdown);
    startTime = pros::millis();
	while (pros::millis() < startTime + 15000) {
		pros::Mutex mutex;
		mutex.take(25);
		recordInput(&instJoysticks[0], &instButtons[0]);
		mutex.give();

		pros::delay(20);
	}

    master.clear_line(1);
    char filename[20];
    sprintf(filename, "/usd/RecAuton%i.txt", selection);
	std::cout << "record loop finished -- " << getVectorSize() << filename << std::endl;

	writeToFile(filename);
    finishRecording();
}

void processInput(double * arrJoysticks, int * arrButtons) {
	// Create easily mutable versions of struct members
	double rightX = arrJoysticks[0];
	double rightY = arrJoysticks[1];
	double leftX = arrJoysticks[2];
	double leftY = arrJoysticks[3];

	if (DRIVE_MODE == 1) {
			// We want to do X-Drive TANK control

			if (abs(rightX) < DEAD_STICK) rightX = 0;
			if (abs(rightY) < DEAD_STICK) rightY = 0;
			if (abs(leftX) < DEAD_STICK) leftX = 0; 
			if (abs(leftY) < DEAD_STICK) leftY = 0;
			rightX = (rightX * SCALING);
			rightY = (rightY * SCALING);
			leftX = (leftX * SCALING);
			leftY = (leftY * SCALING);

			setIndividualMotor((rightY - average(rightX, leftX)),
				 				(leftY + average(rightX, leftX)),
								(rightY + average(rightX, leftX)),
								(leftY - average(rightX, leftX)));
	}
	else if (DRIVE_MODE == 2) {
		// We want to do X-Drive ARCADE control

		if (abs(rightX) < DEAD_STICK) rightX = 0; 
		if (abs(rightY) < DEAD_STICK) rightY = 0; 
		if (abs(leftX) < DEAD_STICK) leftX = 0; 
		if (abs(leftY) < DEAD_STICK) leftY = 0; 
		rightX = (rightX * SCALING);
		rightY = (rightY * SCALING);
		leftX = (leftX * SCALING);
		leftY = (leftY * SCALING);

		setIndividualMotor((rightY - leftX - rightX),
							(rightY + leftX + rightX),
							(rightY - leftX + rightX),
							(rightY + leftX - rightX));
	}
	else if (DRIVE_MODE == 3) {
		// we are wanting to do standard TANK Control

		// implemenet dead stick control
		if (abs(leftY) < DEAD_STICK) leftY = 0; 
		if (abs(rightY) < DEAD_STICK) rightY = 0; 
		// implement scaling
		rightY = (rightY * SCALING);
		leftY = (leftY * SCALING);

		setIndividualMotor(rightY, leftY, rightY, leftY);
	}
	else if (DRIVE_MODE == 4) {
		// We are wanting to do standard ARCADE control

		// implemenet dead stick control
		if (abs(leftY) < DEAD_STICK) leftY = 0; 
		if (abs(leftX) < DEAD_STICK) leftX = 0; 
		// implement scaling
		leftX = (leftX * SCALING);
		leftY = (leftY * SCALING);

		setIndividualMotor(leftY - leftX, leftY + leftX, leftY - leftX, leftY + leftX);
	}
	// else if (DRIVE_MODE == 5) {    // decomissioned until further testing and/or demand for it to actually be made
	// 	int leftX;
	//   	int leftY;

	// 	if (master.get_digital(DIGITAL_UP)) {
	// 		leftY = 200;
	// 	}
	// 	else if (master.get_digital(DIGITAL_DOWN)) {
	// 		leftY = -200;
	// 	}
	// 	else {
	// 		leftY = 0;
	// 	}

	// 	if (master.get_digital(DIGITAL_LEFT)) {
	// 		leftX = 200;
	// 	}
	// 	else if (master.get_digital(DIGITAL_RIGHT)) {
	// 		leftX = -200;
	// 	}
	// 	else {
	// 		leftX = 0;
	// 	}

	//   	int rightX = master.get_analog(ANALOG_RIGHT_X);

	// 	if(abs(rightX) < DEAD_STICK) { rightX = 0; }
	// 	if(abs(leftX) < DEAD_STICK) { leftX = 0; }
	// 	if(abs(leftY) < DEAD_STICK) { leftY = 0; }

	// 	setIndividualMotor((rightX - leftX - rightX),
	// 	 					(rightX + leftX + rightX),
	// 						(rightX - leftX + rightX),
	// 						(rightX + leftX - rightX));

	// }

	// end chassis control, below is other modules only
	if (arrButtons[0] == 1) {
		conveyorMove(100);
	}
	else if (arrButtons[0] == -1) {
		conveyorMove(-100);
	}
	else {
		conveyorStop();
	}

	if (arrButtons[1] == 1) {
		frontLiftMove(127);
	}
	else if (arrButtons[1] == -1) {
		frontLiftMove(-110);
	}
	else {
		frontLiftLock();
	}

	if (arrButtons[2] == 1) {
		backLiftMove(127);
	}
	else if (arrButtons[2] == -1) {
		backLiftMove(-110);
	}
	else {
        backLiftMove(0);
		//backLiftLock();
	}
}

int average(int x, int y) {
  return((x + y) / 2);
}
