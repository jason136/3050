#ifndef _CHASSIS_H_
#define _CHASSIS_H_
// Place all chassis related globals, function stub declartions in this header file.

#define WHEEL_DIAMETER 4      // diameter of drive wheels
#define WHEEL_BASE 18         // wheel base in inches left to right wheel diagonal

// Motor max speeds for reference
// 36 gearset (RED) -- 100
// 18 gearset (GREEN) -- 200
// 06 gearset (BLUE) -- 600

// Sets the speeds of each motor individually.
// This method controls the chassis during opcontrol
void setIndividualMotor(int FRight, int FLeft, int BRight, int BLeft);

// Function to lock drive motors if the corresponding number is 0
void chassisLockDrive(int FRight, int FLeft, int BRight, int BLeft);

#endif // _CHASSIS_H_
