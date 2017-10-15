#ifndef PAINTING_PUZZLE_H
#define PAINTING_PUZZLE_H

#include "puzzle.h"

struct PaintingPuzzle : public Puzzle {
  PaintingPuzzle() : Puzzle() {
    cooldown = 120.0;
    title = "Painting puzzle";
  }

  void reedSenseIsr();
  virtual void activate();
  virtual void solve();
};

#endif
