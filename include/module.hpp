#ifndef _MODULE_H_
#define _MODULE_H_

void initializeVision();

void moveGrabber(int mode);

void moveClaw(int mode);

// Set pneumatics to extend (1) or retract (0)
void toggleLiftClawPneumatics(int toggle);

void toggleBackClawPneumatics(int toggle);

void setLiftClawPneumatics(int mode);

void setBackClawPneumatics(int mode);

void closeLiftClaw(void* param);

void closeBackClaw(void* param);

#endif