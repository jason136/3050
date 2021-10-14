#ifndef _TRAY_H_
#define _TRAY_H_

// ----------- SETTINGS FOR AUTO TRAY CONTROL -------

void trayForward(int speed);

void trayBackward(int speed);

void trayStop();

void traySpinForEncoder(int speed, int encDegrees); // move tray forward or backward in given increment at speed in RPM

void trayLock();

#endif
