#ifndef PUZZLE_H
#define PUZZLE_H

#include "mbed.h"
#include <string>

struct Puzzle {
  Puzzle();

  void deactivate();
  bool isActive();
  void isSolved();
  bool coolingDown();
  bool hasCooldown();
  void startCooldown();
  void endCooldown();
  
  virtual void activate() {};
  virtual void solve() {};
  std::string title;
  
  float cooldown;
  bool activated;
  
private:
  bool solved;
  bool inCooldown;
  Timeout t;
};

#endif
