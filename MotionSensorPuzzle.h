#ifndef MOTION_SENSOR_PUZZLE_H
#define MOTION_SENSOR_PUZZLE_H

#include "puzzle.h"

struct MotionSensorPuzzle : public Puzzle {
  MotionSensorPuzzle() : Puzzle() {
    cooldown = 120.0;
  }

  void motion_triggered();

  virtual void activate();
  virtual void solve();
};

#endif
