#ifndef AUTO_H_
#define AUTO_H_

#include "main.h"

// Functiosn facilitating the various Autonomous routien options
void recordableAuton();

void recAutonLoop(void * param);

void skillRun();              // Skill Autonomous - 60Sec

void autoRed1();              // Competition autonomous - 15Sec

void autoBlue1();

void autoRed2();

void autoBlue2();

void autoRed3();

void autoBlue3();

void courseCorrect(int index, int * inputs, double * cords);

#endif
