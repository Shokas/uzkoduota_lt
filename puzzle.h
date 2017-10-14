#ifndef PUZZLE_H
#define PUZZLE_H

#include "mbed.h"

struct Puzzle {
  Puzzle();

  void deactivate();
  bool isActive();
  bool isSolved();
  bool coolingDown();
  bool hasCooldown();
  void startCooldown();
  void endCooldown();
  
  virtual void activate() {};
  virtual void solve() {};
  
  float cooldown;
  bool activated;
  
private:
  bool solved;
  bool inCooldown;
  Timeout t;
};

#endif
