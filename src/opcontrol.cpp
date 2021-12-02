#include "main.h"
#include "portdef.hpp"
#include "chassis.hpp"
#include "conveyor.hpp"
#include "lift.hpp"
#include "screen.hpp"
#include "file.hpp"
#include "opcontrol.hpp"

// Datastructures for recordable autonomous
int8_t instInputs[28];

// Datastructures used for console and screen diagnostics
double buffer[12];
char chassisData[400];

// This mutex carries protects all motor control values
pros::Mutex mutex;

extern int8_t selection;
extern bool recSkills;

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

// Live state of controller is recorded in int array
void readController(int8_t * instInputs) {
    instInputs[0] = master.get_analog(ANALOG_RIGHT_X);
    instInputs[1] = master.get_analog(ANALOG_RIGHT_Y);
    instInputs[2] = master.get_analog(ANALOG_LEFT_X);
    instInputs[3] = master.get_analog(ANALOG_LEFT_Y);

    instInputs[14] = partner.get_analog(ANALOG_RIGHT_X);
    instInputs[15] = partner.get_analog(ANALOG_RIGHT_Y);
    instInputs[16] = partner.get_analog(ANALOG_LEFT_X);
    instInputs[17] = partner.get_analog(ANALOG_LEFT_Y);

    if (master.get_digital(DIGITAL_R1)) instInputs[4]++;
    if (master.get_digital(DIGITAL_R2)) instInputs[4]--;
    if (master.get_digital(DIGITAL_L1)) instInputs[5]++;
    if (master.get_digital(DIGITAL_L2)) instInputs[5]--;

    instInputs[6] = master.get_digital(DIGITAL_UP); 
    instInputs[7] = master.get_digital(DIGITAL_DOWN);
    instInputs[8] = master.get_digital(DIGITAL_LEFT);
    instInputs[9] = master.get_digital(DIGITAL_RIGHT);

    instInputs[10] = master.get_digital(DIGITAL_X);
    instInputs[11] = master.get_digital(DIGITAL_B);
    instInputs[12] = master.get_digital(DIGITAL_Y);
    instInputs[13] = master.get_digital(DIGITAL_A);
    
    if (partner.get_digital(DIGITAL_R1)) instInputs[18]++;
    if (partner.get_digital(DIGITAL_R2)) instInputs[18]--;
    if (partner.get_digital(DIGITAL_L1)) instInputs[19]++;
    if (partner.get_digital(DIGITAL_L2)) instInputs[19]--;

    instInputs[20] = partner.get_digital(DIGITAL_UP); 
    instInputs[21] = partner.get_digital(DIGITAL_DOWN);
    instInputs[22] = partner.get_digital(DIGITAL_LEFT);
    instInputs[23] = partner.get_digital(DIGITAL_RIGHT);

    instInputs[24] = partner.get_digital(DIGITAL_X);
    instInputs[25] = partner.get_digital(DIGITAL_B);
    instInputs[26] = partner.get_digital(DIGITAL_Y);
    instInputs[27] = partner.get_digital(DIGITAL_A);
}

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
	while (true) {

		mutex.take(25);
        std::fill_n(instInputs, 20, 0);
        readController(instInputs);
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

		if (DEBUG_ON) {
			std::cout << chassisData;
		}
		pros::delay(20);
	}
}

void processInput(int8_t * arrInputs) {
	// Create easily mutable versions of struct members
	int8_t rightX = arrInputs[0];
	int8_t rightY = arrInputs[1];
	int8_t leftX = arrInputs[2];
	int8_t leftY = arrInputs[3];

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
	// 	int8_t leftX;
	//   	int8_t leftY;

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

	//   	int8_t rightX = master.get_analog(ANALOG_RIGHT_X);

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

    if (instInputs[11]) {
        togglePneumaticState();
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

int average(int x, int y) {
  return((x + y) / 2);
}