#include "main.h"
#include "portdef.hpp"
#include "auton.hpp"
#include "chassis.hpp"
#include "lift.hpp"
#include "conveyor.hpp"
#include "file.hpp"
#include "screen.hpp"
#include "opcontrol.hpp"

pros::Vision visionSensor(VISION_PORT);
extern int selection;
extern pros::Mutex mutex;
bool recAutonActive;
/**
 * This is where all the various autonomous routines are located
 * and subsequently called by the autonomous() selector based on GUI input
 **/
void recordableAuton() {
    //printVectors();
    recAutonActive = true;
    visionSensor.set_led(COLOR_CRIMSON);
    visionSensor.clear_led();
    visionSensor.set_auto_white_balance(true);
    pros::Task recAutonThread(recAutonLoop);

    while (true) {}
}

void recAutonLoop(void * param) {
	std::cout << "recAutonLoop started" << std::endl;
    char filename[20];
    sprintf(filename, "/usd/RecAuton%i.txt", selection);
    readFromFile(filename);

    int interations = getVectorSize();
    int recOutputs[28];

    // double cords[3];
    int starttime = pros::millis();
    if (interations > 0) {
        for (int index = 0; index < interations; index++) {
            updateVecs(index, &recOutputs[0]);
            //updateLocation(index, &cords[0]);

            //mutex.take(25);
            //courseCorrect(&recOutputs[0], &cords[0]);
            std::cout << recOutputs[0] << recOutputs[1] << recOutputs[2] << recOutputs[3] << std::endl;
            std::cout << " rec: " << recOutputs[5] << std::endl;
            processInput(&recOutputs[0]);
            //mutex.give();


            // if (recAutonActive) {
            // }

            //std::cout << "selection: " << selection << " execute line " << x << "of" << interations << std::endl;
            pros::delay(20);
        }
    }

    std::cout << "auton run time ellapsed: " << pros::millis() - starttime << std::endl;
}

void skillRun() {

    // // Old code below use only for reference. ie delete
    // //liftMove(100);
    // pros::delay(100);
    // //liftMove(-100);
    // pros::delay(100);
    // //liftMove(100);
    // pros::delay(100);
    // //liftMove(-100);
    // pros::delay(100);
    // //liftLock();

    // setIndividualMotor(100, -100, -100, 100);
    // pros::delay(2000);
    // chassisStopDrive();

}

void autoRedLeft() {

    // Code Here
}

void autoBlueLeft() {

    // Code Here
}

void autoRedRight() {

    // Code Here
}

void autoBlueRight() {

    // Code Here penis
}

void courseCorrect(int * inputs, double * cords) {
    // TODO fix file.cpp cordVectors
}