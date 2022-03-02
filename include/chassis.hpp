#ifndef _CHASSIS_H_
#define _CHASSIS_H_

// Place all chassis related globals, function stub declartions in this header file
#define WHEEL_DIAMETER 4      // diameter of drive wheels
#define WHEEL_BASE 18         // wheel base diameter

// Motor max speeds for reference
// 36 gearset (RED) -- 100
// 18 gearset (GREEN) -- 200
// 06 gearset (BLUE) -- 600

// Function declaration - sets voltage of motors without programmed stop
void chassisMove(int voltage);

// Sets the speeds of each motor individually.
// This method controls the chassis during opcontrol
void chassisMoveIndividuals(int FRight, int FLeft, int BRight, int BLeft);

// Function to lock drive motors if the corresponding number is 0
void chassisLockDrive(int FRight, int FLeft, int BRight, int BLeft);

void trackSpeed(double * coords);

void chassisGyroPark();

// Helper method to stop all chassis motors
void chassisStopDrive(pros::motor_brake_mode_e_t brakeType, bool left, bool right);

// Reset chassis encoders
void resetChassisEncoders();

// Return motor diagnostics data for screen
void getChassisDiag(double * buffer);

// Drive with PID control for a given distnace in inches
void driveForDistancePID(int distance, int speed);

// Make a pivot turn to the right or left for a given angle
// angle should be greater than 10 and less equal to 360
// Speed must take motor internal gearing into account
void pivotTurn(int turnAngle, int speed);

// positive is ccw, negative is cw
void gyroTurn(int turnAngle, int time);

// Time parameter for both corresponds to number of milliseconds

void visPathfind(int sig, int time); 

#endif // _CHASSIS_H_