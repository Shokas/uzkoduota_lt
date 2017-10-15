#include "SafePuzzle.h"
#include "RPG.h"

void SafePuzzle::activate() {
  printf("Safe Puzzle activated\r\n");
  activated = true;
}

void SafePuzzle::solve() {
  if(isActive() && !coolingDown()) {

  }
}
