#include "main.h"
#include "tray.h"
#include "portdef.h"

pros::Motor trayMotor(TRAY_MOTOR_PORT);

void trayForward(int speed) {
  trayMotor.move_velocity(speed);
}

void trayBackward(int speed) {
  trayMotor.move_velocity(-speed);
}

void trayStop() {
  trayMotor.move_velocity(0);
}

void rollerSpinForEncoder(int speed, int encDegrees) {
  trayMotor.move_absolute(encDegrees, speed);

  if(DEBUG_ON){
    std::cout << "In Tray Raise Manual function -- Speed: " << speed ;
    std::cout << " Current Encoder: " << trayMotor.get_position() << "\n";
  }
  trayMotor.move_velocity(speed);
  pros::delay(2);
}

void trayLock() {
  trayMotor.move_velocity(0);
  if(trayMotor.get_brake_mode() != 2 ) {
    trayMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  pros::delay(2);
}
