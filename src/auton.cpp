#include "main.h"
#include "portdef.hpp"
#include "auton.hpp"
#include "chassis.hpp"
#include "lift.hpp"
#include "conveyor.hpp"
#include "file.hpp"
#include "screen.hpp"
#include "opcontrol.hpp"

// Pull values from screen
extern int selection;
extern bool recSkills;
/**
 * This is where all the various autonomous routines are located
 * and subsequently called by the autonomous() selector based on GUI input
 **/
void recordableAuton() {
    int interations = getVectorSize();
    int recOutputs[7];
    int starttime = pros::millis();
    // char filename[20];
    // sprintf(filename, "/usd/RecAuton%i.txt", selection);
    // readFromFile(filename);
    if (interations > 0) {
        for (int x = 0; x < interations; x++) {
        updateIndex(&recOutputs[0], x);
        processInput(&recOutputs[0]);
        std::cout << "selection: " << selection << " execute line " << x << "of" << interations << std::endl;
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
