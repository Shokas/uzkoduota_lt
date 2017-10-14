#include "MotionSensorPuzzle.h"

InterruptIn motion_sensor(PB_8);  //  active low

void MotionSensorPuzzle::activate() {
  motion_sensor.fall(callback(this, &MotionSensorPuzzle::motion_triggered));
  activated = true;
}

void MotionSensorPuzzle::motion_triggered() {
  startCooldown();
}

// activates masks 5mins coolown, open drawer for 10-15s, 2 mins cooldown
void MotionSensorPuzzle::solve() {
  if(isActive() && !coolingDown()) {
    
  }
}
