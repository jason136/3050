#ifndef _MISC_H_
#define _MISC_H_

void initializeVision();

void initializeGps(
    double xInit = 0.0, 
    double yInit = 0.0, 
    double headingInit = 0.0, 
    double xOffset = 0.0, 
    double yOffset = 0.0
);

void pollGps();

// Set pneumatics to extend (1) or retract (0)
void toggleIndexer(int toggle);

void setIndexer(int input);

void setEndgame(int input);

void spinIntake(int speed);

void stopIntakeDelayed(void* param);

#endif