#ifndef DISTANCE_SENSOR_PUZZLE_H
#define DISTANCE_SENSOR_PUZZLE_H

#include "puzzle.h"

struct DistanceSensorPuzzle : public Puzzle {
  DistanceSensorPuzzle() : Puzzle() {
    cooldown = 120;
  }

  virtual void activate();
  virtual void solve();
};

#endif
