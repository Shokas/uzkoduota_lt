#include "PaintingPuzzle.h"
#include "MaskPuzzle.h"

Puzzle *mask_puzzle = new MaskPuzzle();
DigitalOut creepy_eyes(PA_6);
DigitalOut reed_power(PA_5);
DigitalIn reed_sense(PB_9);
//InterruptIn reed_sense(PB_9);

void PaintingPuzzle::solve() {
  reed_power = 1;
  if(isActive() && !coolingDown()) {
    printf("Painting puzzle started");
    if(reed_sense == 0) {
      creepy_eyes = 0;
      startCooldown();
      mask_puzzle->activate();
    } else {
      creepy_eyes = 1;
    }
  } else if(coolingDown()) {
    creepy_eyes = 0;
  } else {
    creepy_eyes = 1;
  }
}
