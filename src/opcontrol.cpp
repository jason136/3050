#include "main.h"
#include "portdef.hpp"
#include "chassis.hpp"
#include "flywheel.hpp"
#include "misc.hpp"
#include "screen.hpp"
#include "file.hpp"
#include "opcontrol.hpp"

// Datastructures for recordable autonomous
int instInputs[28];

// This mutex carries protects all motor control values
pros::Mutex mutex;

extern pros::Vision visionSensor;

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
		
		pros::delay(20);
	}
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

		chassisMoveIndividuals((rightY - average(rightX, leftX)),
							(leftY + average(rightX, leftX)),
							(rightY + average(rightX, leftX)),
							(leftY - average(rightX, leftX)));
	}
	else if (DRIVE_MODE == 2) {
		// We want to do X-Drive ARCADE control

		int aimAmount = 0;

		if (instInputs[6]) {
    		visionSensor.set_led(COLOR_GREEN);

			if (selection == 0 || selection == 2 || selection == 4) {
				aimAmount = int(visAimAssist(1));
			}
			else if (selection == 1 || selection == 3 || selection == 5) {
				aimAmount = int(visAimAssist(2));
			}
			std::cout << "selection:" << selection << "    aimAmount" << aimAmount << std::endl; 
		}
		else {
			visionSensor.set_led(COLOR_WHITE);
		}
		
		chassisMoveIndividuals((rightY - leftX - rightX) + aimAmount,
							(rightY + leftX + rightX) - aimAmount,
							(rightY - leftX + rightX) + aimAmount,
							(rightY + leftX - rightX) - aimAmount);
	}
	else if (DRIVE_MODE == 3) {
		// we are wanting to do standard TANK Control

        chassisMoveIndividuals(-rightY, -leftY, -rightY, -leftY);

	}
	else if (DRIVE_MODE == 4) {
		// We are wanting to do standard ARCADE control

		chassisMoveIndividuals(leftY - leftX, leftY + leftX, leftY - leftX, leftY + leftX);
	}

	// toggleIndexer(/*instInputs[18] && */instInputs[4]);

	// if (arrInputs[27]) setFlywheelSpeed(500);
	// if (arrInputs[26]) setFlywheelSpeed(450);
	// if (arrInputs[25]) setFlywheelSpeed(400);
	// if (arrInputs[24]) setFlywheelSpeed(350);
	
	if (arrInputs[13]) setFlywheelSpeed(500);
	if (arrInputs[12]) setFlywheelSpeed(450);
	if (arrInputs[11]) setFlywheelSpeed(400);
	if (arrInputs[10]) setFlywheelSpeed(350);

	// spinFlywheel(arrInputs[27] || arrInputs[26] || arrInputs[25] || arrInputs[24]);

	spinFlywheel(arrInputs[13] || arrInputs[12] || arrInputs[11] || arrInputs[10]);

	spinIntake(arrInputs[5] * 127);

	// pollGps();

	if (instInputs[20]) {
		calibrateGyro();
	}

	// pollGyro();

	if (instInputs[6]/* && instInputs[20]*/) setEndgame(0);
	setIndexer(!abs(instInputs[4]));
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
		duration = 60000;
	}
	else {
		duration = 15000;
	}
	
    // right y cord, left y cord, lateral x
    double cords[] = {0.0, 0.0, 0.0};
    int index = 0;
	while (pros::millis() < startTime + duration) {
        index++; 
		mutex.take(5);
        trackSpeed(&cords[0]);
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