#ifndef PUZZLE_H
#define PUZZLE_H

#include "mbed.h"

struct Puzzle {
  Puzzle();

  void activate();
  void deactivate();
  bool isActive();
  bool isSolved();
  bool coolingDown();
  bool hasCooldown();
  void startCooldown();
  void endCooldown();
  
  virtual void solve() {};
  
  float cooldown;

private:
  bool activated;
  bool solved;
  bool inCooldown;
  Timeout t;
};

#endif
