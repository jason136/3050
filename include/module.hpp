#ifndef _MODULE_H_
#define _MODULE_H_

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
void toggleLiftClawPneumatics(int toggle);

void spinIndexer(bool triggered);

void spinIntake(int speed);

#endif