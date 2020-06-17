#ifndef _SHOOTER_H_
#define _SHOOTER_H_

// ----------- SETTINGS FOR AUTO SHOOTER CONTROL -------
#define SHOOTER_TARGET 2160    // How many tics to pull shooter in degrees
                               // geared 12:36 - two rotations of 720 results in
                               // 3 * 720 = 2160 degrees

void shootBall(int speed);    // pull shooter and release speed in RPM

#endif
