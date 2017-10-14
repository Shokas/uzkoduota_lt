#ifndef MASK_PUZZLE_H
#define MASK_PUZZLE_H

#include "puzzle.h"

struct MaskPuzzle : public Puzzle {
  MaskPuzzle() : Puzzle() {
    cooldown = 300.0; //  in seconds
  }

  virtual void solve();
};

#endif
