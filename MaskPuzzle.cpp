#include "MaskPuzzle.h"

uint8_t repeat = 2;
BusOut masks(PA_10, PB_3, PB_5, PB_4, PB_10, PA_8, PA_9, PC_7, PB_6, PA_7);

void blinkPattern() {
  // blink pattern in here
  for(int r=0; r<repeat; r++) {
    for(int i=0; i<=10; i++) {
      masks = 0x001 << i;
      // add one second delay
    }
    // add 10 second delay
  }
}

void MaskPuzzle::solve() {
  if(isActive() && !coolingDown()) {
    printf("Mask Puzzle started");
    blinkPattern();
    startCooldown();
  }
}
