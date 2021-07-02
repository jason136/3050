#ifndef AUTO_H_
#define AUTO_H_

#include "main.h"

// Declare drawScreen here because it's auton related
void drawScreen();

// Functiosn facilitating the various Autonomous routien options
void skillRun();              // Skill Autonomous - 60Sec
void autoRedLeft();           // Competition autonomous - 15Sec
void autoBlueRight();
void autoRedRight();
void autoBlueLeft();

#endif
