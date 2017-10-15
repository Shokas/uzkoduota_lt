#include "SafePuzzle.h"
#include "RPG.h"

enum RotationDirection {
  ANTICLOCKWISE = -1,
  NONE = 0,
  CLOCKWISE = 1
};

enum UnlockState {
  STATE1,
  STATE2,
  STATE3,
  STATE4
};

RPG rpgLock(PB_12, PA_11, PA_12);
uint8_t newDirection;
uint8_t lastDirection;
uint8_t rotationCount;
uint8_t currentState;

void SafePuzzle::activate() {
  printf("Safe Puzzle activated\r\n");
  activated = true;
  rotationCount = 0;
  lastDirection = NONE;
  newDirection = lastDirection;
  currentState = STATE1;
}

void SafePuzzle::solve() {
  if(isActive() && !coolingDown()) {
    newDirection = rpgLock.dir();
    if(newDirection != NONE) {
      if(lastDirection == NONE) {
        rotationCount++;
        lastDirection = newDirection;
      } else {
        if(newDirection == lastDirection) {
          rotationCount++;
        } else {
          rotationCount = 0;
          lastDirection = newDirection;
        }
      }
      printf("[%s] dir: %d count: %d\r\n", this->title.c_str(), newDirection, rotationCount);
    }
    
    switch(currentState) {
      case STATE1:
        if(rotationCount == 3) {
          rotationCount = 0;
          currentState = STATE2;
        }
        break;

      case STATE2:
        // open drawer for 20-25s
        startCooldown();
        isSolved();
        break;

      default:
        break;
    }
  }
}
