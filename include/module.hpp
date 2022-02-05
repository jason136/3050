#ifndef _MODULE_H_
#define _MODULE_H_

void moveGrabber(int mode);

void moveClaw(int mode);

// Set pneumatics to extend or retract
void toggleMoGoalPneumatics(int mode);

void toggleAutonPneumatics(int mode);

#endif