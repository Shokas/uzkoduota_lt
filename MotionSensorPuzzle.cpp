#include "MotionSensorPuzzle.h"
#include "MaskPuzzle.h"

Puzzle *mask_puzzle = new MaskPuzzle();
InterruptIn motion_sensor(PB_8);  //  active low

void MotionSensorPuzzle::activate() {
  mask_puzzle->activate();
  motion_sensor.fall(callback(this, &MotionSensorPuzzle::motion_triggered));
  activated = true;
}

void MotionSensorPuzzle::motion_triggered() {
  mask_puzzle->solve();
  // open drawer
  startCooldown();
}

// activates masks 5mins coolown, open drawer for 10-15s, 2 mins cooldown
void MotionSensorPuzzle::solve() {
}
