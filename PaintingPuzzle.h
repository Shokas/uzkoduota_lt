#ifndef PAINTING_PUZZLE_H
#define PAINTING_PUZZLE_H

#include "puzzle.h"

struct PaintingPuzzle : public Puzzle {
  PaintingPuzzle() : Puzzle() {
    cooldown = 120.0;
  }

  virtual void solve();
};

#endif
