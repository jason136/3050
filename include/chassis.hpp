#ifndef _CHASSIS_H_
#define _CHASSIS_H_
// Place all chassis related globals, function stub declartions in this header file.

#define WHEEL_DIAMETER 4      // diameter of drive wheels
#define WHEEL_BASE 18         // wheel base in inches left to right wheel diagonal

#define DRIVE_MODE 3          // 1 for x-drive TANK
                              // 2 for x-drive ARDCADE
                              // 3 for standard TANK
                              // 4 for standard ARCADE
                              // 5 for Ryan Mode (arcade but with the arrow keys for movement)

#define JOY_SCALE .5          // scale the joysticks to 50% valid values are 0 - 1
                              // note: 0 will disable joysticks 0 * x = 0 always....

#define DEAD_STICK 10         // Dead stick zone - joystick movement between
                              // -DEAD_STICK and DEAD_STICK will result in a joystick
                              // value of 0 - dealing with slow creepign of robot when joysticks
                              // do not land perfectly in the center position

// Motor max speeds for reference
// 36 gearset (RED) -- 100
// 18 gearset (GREEN) -- 200
// 06 gearset (BLUE) -- 600

// Function declaration - sets voltage of motors without programmed stop
void chassisMove(int voltage);

// Sets the speeds of each motor individually.
// This method controls the chassis during opcontrol
void setIndividualMotor(int FRight, int FLeft, int BRight, int BLeft);

// Function to stop all Motors
void chassisStopDrive();

// Reset chassis encoders
void resetChassisEncoders();

// Drive with PID control for a given distnace in inches
void driveForDistancePID(int distance, int speed);

// Make a pivot turn to the right or left for a given angle
// angle should be greater than 10 and less equal to 360
// Speed must take motor internal gearing into account
void pivotTurn(int speed, long angle);

// Return motor diagnostics data for screen
void getChassisDiag(double * buffer);

// Helper for calculating averages
int average(int x, int y);

#endif // _CHASSIS_H_
