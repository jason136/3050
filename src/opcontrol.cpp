#include "main.h"
#include "portdef.hpp"
#include "chassis.hpp"
#include "conveyor.hpp"
#include "lift.hpp"
#include "screen.hpp"
#include "file.hpp"
#include "opcontrol.hpp"

// Datastructures for recordable autonomous
int instInputs[7];

// Datastructures used for console and screen diagnostics
double buffer[12];
char chassisData[400];

extern int selection;
extern bool recSkills;

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

		instInputs[0] = master.get_analog(ANALOG_RIGHT_X);
		instInputs[1] = master.get_analog(ANALOG_RIGHT_Y);
		instInputs[2] = master.get_analog(ANALOG_LEFT_X);
		instInputs[3] = master.get_analog(ANALOG_LEFT_Y);

		if (partner.get_digital(DIGITAL_R1)) {
			instInputs[4] = 1;
		}
		else if (partner.get_digital(DIGITAL_R2)) {
			instInputs[4] = -1;
		}
		else {
			instInputs[4] = -0;
		}
		if (master.get_digital(DIGITAL_L1)) {
			instInputs[5] = 1;
		}
		else if (master.get_digital(DIGITAL_L2)) {
			instInputs[5] = -1;
		}
		else {
			instInputs[5] = -0;
		}
		if (partner.get_digital(DIGITAL_UP)) {
			instInputs[6] = 1;
		}
		else if (partner.get_digital(DIGITAL_DOWN)) {
			instInputs[6] = -1;
		}
		else {
			instInputs[6] = -0;
		}

		mutex.give();

		processInput(&instInputs[0]);
		
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
		pros::delay(20);
    }

    sprintf(countdown, "recording");
    master.set_text(1, 1, countdown);
    startTime = pros::millis();
	int duration;
	if (recSkills) {
		duration = 60000;
	}
	else {
		duration = 15000;
	}
	while (pros::millis() < startTime + duration) {
		pros::Mutex mutex;
		mutex.take(5);
		recordInput(&instInputs[0]);
		mutex.give();
		
		pros::delay(20);
	}

    master.clear_line(1);
    char filename[20];
    sprintf(filename, "/usd/RecAuton%i.txt", selection);
	std::cout << "record loop finished -- " << getVectorSize() << filename << " elapsed time: " << pros::millis() - startTime << std::endl;

	writeToFile(filename);
    finishRecording();
}

void processInput(int * arrInputs) {
	// Create easily mutable versions of struct members
	int rightX = arrInputs[0];
	int rightY = arrInputs[1];
	int leftX = arrInputs[2];
	int leftY = arrInputs[3];

	if (abs(rightX) < DEAD_STICK) rightX = 0; 
	if (abs(rightY) < DEAD_STICK) rightY = 0; 
	if (abs(leftX) < DEAD_STICK) leftX = 0; 
	if (abs(leftY) < DEAD_STICK) leftY = 0; 
	rightX = (rightX * SCALING);
	rightY = (rightY * SCALING);
	leftX = (leftX * SCALING);
	leftY = (leftY * SCALING);

	if (DRIVE_MODE == 1) {
		// We want to do X-Drive TANK control

		setIndividualMotor((rightY - average(rightX, leftX)),
							(leftY + average(rightX, leftX)),
							(rightY + average(rightX, leftX)),
							(leftY - average(rightX, leftX)));
	}
	else if (DRIVE_MODE == 2) {
		// We want to do X-Drive ARCADE control

		setIndividualMotor((rightY - leftX - rightX),
							(rightY + leftX + rightX),
							(rightY - leftX + rightX),
							(rightY + leftX - rightX));
	}
	else if (DRIVE_MODE == 3) {
		// we are wanting to do standard TANK Control

		setIndividualMotor(rightY, leftY, rightY, leftY);

        chassisLockDrive(rightY, leftY, rightY, leftY);
	}
	else if (DRIVE_MODE == 4) {
		// We are wanting to do standard ARCADE control

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
	if (arrInputs[4] == 1) {
		conveyorMove(100);
	}
	else if (arrInputs[4] == -1) {
		conveyorMove(-100);
	}
	else {
		conveyorStop();
	}

	if (arrInputs[5] == 1) {
		frontLiftMove(127);
	}
	else if (arrInputs[5] == -1) {
		frontLiftMove(-110);
	}
	else {
		frontLiftLock();
	}

	if (arrInputs[6] == 1) {
		backLiftMove(127);
	}
	else if (arrInputs[6] == -1) {
		backLiftMove(-110);
	}
	else {
        //backLiftMove(0);
		backLiftLock();
	}
}

int average(int x, int y) {
  return((x + y) / 2);
}
