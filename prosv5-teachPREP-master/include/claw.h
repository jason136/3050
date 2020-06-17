#ifndef _CLAW_H_
#define _CLAW_H_

// ----------- SETTINGS FOR AUTO CLAW CONTROL -------
#define FLIP_TARGET 370           // How many tics to flip the claw 180degrees

void flipClaw(int speed);         // flip the claw 180 degrees
void flipClawBack(int speed);     // flips claw back to starting position  (-180)
void lockClaw();                  // hold the claw in rotated position (lock)
void setClawPosition();           // resets encoder to 0

#endif
