#include "main.h"
#include "portdef.hpp"
#include "chassis.hpp"
#include "lift.hpp"
#include "module.hpp"
#include "screen.hpp"
#include "file.hpp"
#include "opcontrol.hpp"

// Datastructures for recordable autonomous
int instInputs[28];

// Datastructures used for console and screen diagnostics
double buffer[12];
char chassisData[400];

// This mutex carries protects all motor control values
pros::Mutex mutex;

extern int selection;

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

// Record state of controllers in int array
void readController(int * instInputs) {
    instInputs[0] = master.get_analog(ANALOG_RIGHT_X);
    instInputs[1] = master.get_analog(ANALOG_RIGHT_Y);
    instInputs[2] = master.get_analog(ANALOG_LEFT_X);
    instInputs[3] = master.get_analog(ANALOG_LEFT_Y);

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

    instInputs[14] = partner.get_analog(ANALOG_RIGHT_X);
    instInputs[15] = partner.get_analog(ANALOG_RIGHT_Y);
    instInputs[16] = partner.get_analog(ANALOG_LEFT_X);
    instInputs[17] = partner.get_analog(ANALOG_LEFT_Y);
    
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
        std::fill_n(instInputs, 28, 0);
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

		if (false) {
			std::cout << chassisData;
		}
		pros::delay(20);
	}
}

// right y cord, left y cord, lateral x
double cords[] = {0.0, 0.0, 0.0};

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

		chassisMoveIndividuals((rightY - average(rightX, leftX)),
							(leftY + average(rightX, leftX)),
							(rightY + average(rightX, leftX)),
							(leftY - average(rightX, leftX)));
	}
	else if (DRIVE_MODE == 2) {
		// We want to do X-Drive ARCADE control

		chassisMoveIndividuals((rightY - leftX - rightX),
							(rightY + leftX + rightX),
							(rightY - leftX + rightX),
							(rightY + leftX - rightX));
	}
	else if (DRIVE_MODE == 3) {
		// we are wanting to do standard TANK Control


        if (arrInputs[10]) chassisGyroPark();
        else chassisMoveIndividuals(rightY, leftY, rightY, leftY);

        //chassisLockDrive(rightY, leftY, rightY, leftY);
	}
	else if (DRIVE_MODE == 4) {
		// We are wanting to do standard ARCADE control

		chassisMoveIndividuals(leftY - leftX, leftY + leftX, leftY - leftX, leftY + leftX);
	}

    if (arrInputs[6]) moveClaw(-1);
    else if (arrInputs[7]) moveClaw(1);
    else moveClaw(0);

    if (arrInputs[8]) moveGrabber(1);
    else if (arrInputs[9]) moveGrabber(-1);
    else moveGrabber(0);

    trackDistance(&cords[0]);

    // if (arrInputs[12]) {
    //     std::cout << cords[0] << " " << cords[1] << " " << cords[2] << std::endl;
    // }
    // std::cout << " inst: " << arrInputs[5] << std::endl;

    if (FLIP_FLOP) {
        
        liftComplex(-1 * arrInputs[5], -1 * arrInputs[5]);

    }
    else {

        // competition bot

		togglePneumaticState(arrInputs[5]);

        int differentialControl = 0;
        if (arrInputs[6]) differentialControl++;
        if (arrInputs[7]) differentialControl--;
        
        liftComplex(arrInputs[4], differentialControl);
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
	if (selection == 6) {
		duration = 15000;
	}
	else {
		duration = 60000;
	}
	/////////////////////////////////////////////////////////
    memset(cords, 0, sizeof(cords));
    int index = 0;
	while (pros::millis() < startTime + duration) {
        index++; 
		mutex.take(5);
        trackDistance(&cords[0]);
		recordInput(index, &instInputs[0], &cords[0]);
		mutex.give();

		pros::delay(20);
	}

    master.clear_line(1);
    char filename[20];
    sprintf(filename, "/usd/RecAuton%i.txt", selection);
	std::cout << "record loop finished -- " << getVectorSize() << filename << " elapsed time: " << pros::millis() - startTime << std::endl;

	writeToFile(filename);
    clearVectors();
    finishRecording();
}

int average(int x, int y) {
  return((x + y) / 2);
}