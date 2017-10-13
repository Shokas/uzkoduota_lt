#include "puzzle.h"

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
