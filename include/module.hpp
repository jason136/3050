#ifndef _MODULE_H_
#define _MODULE_H_

void initializeVision();

void moveGrabber(int mode);

void moveClaw(int mode);

// Set pneumatics to extend (1) or retract (0)
void toggleLiftClawPneumatics(int mode);

void toggleBackClawPneumatics(int mode);

void closeLiftClaw(void* param);

void closeBackClaw(void* param);

#endif