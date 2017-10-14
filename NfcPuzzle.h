#ifndef NFC_PUZZLE_H
#define NFC_PUZZLE_H

#include "puzzle.h"

struct NfcPuzzle : public Puzzle {
  NfcPuzzle() : Puzzle() {
  }

  virtual void activate();
  virtual void solve();
};

#endif
