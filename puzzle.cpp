#include "puzzle.h"
#include "mbed.h"

Puzzle::Puzzle() {
  activated = false;
  solved = false;
  inCooldown = false;
  cooldown = 0.0;
  title = "";
}

void Puzzle::deactivate() {
  activated = false;
}

bool Puzzle::isActive() {
  return activated;
}

void Puzzle::isSolved() {
  printf("%s puzzle solved\r\n", this->title.c_str());
  this->solved = true;
}

bool Puzzle::coolingDown() {
  return inCooldown;
}

bool Puzzle::hasCooldown() {
  return (cooldown != 0.0);
}

void Puzzle::startCooldown() {
  if(hasCooldown()) {
    t.attach(callback(this, &Puzzle::endCooldown), cooldown);
    inCooldown = true;
    printf("%s %.0f cooldown started\r\n", this->title.c_str(), cooldown);
  }
}

void Puzzle::endCooldown() {
  inCooldown = false;
  printf("%s cooldown ended\r\n", this->title.c_str());
}
