#include "puzzle.h"

Puzzle::Puzzle() {
  activated = false;
  solved = false;
  inCooldown = false;
  cooldown = 0.0;
}

void Puzzle::activate() {
  activated = true;
}

void Puzzle::deactivate() {
  activated = false;
}

bool Puzzle::isActive() {
  return activated;
}

bool Puzzle::isSolved() {
  return solved;
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
  }
}

void Puzzle::endCooldown() {
  inCooldown = false;
}
