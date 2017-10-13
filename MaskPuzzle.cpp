#include "MaskPuzzle.h"
#include "mbed.h"

Timer t;
BusOut masks(PA_10, PB_3, PB_5, PB_4, PB_10, PA_8, PA_9, PC_7, PB_6, PA_7);

void blinkPattern() {
  // blink pattern in here
  int i;
  for(i=0; i <= 10; i++) {
    masks = 0x001 << i;
    wait(1);
  }
}

void MaskPuzzle::solve() {
  t.start();
  if(this->isActive()) {
    blinkPattern();
    printf("Mask Puzzle started");
  }
}
