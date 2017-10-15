#include "PaintingPuzzle.h"

#define EYES_ON   0
#define EYES_OFF  1

DigitalOut creepy_eyes(PA_6);
DigitalOut reed_power(PA_5);
InterruptIn reed_sense(PB_9);

// open drawer when solved

void PaintingPuzzle::reedSenseIsr() {
  if(isActive() && !coolingDown()) {
    printf("Reed sense %d\r\n", reed_sense.read());
    if(reed_sense.read() == 0) {
      creepy_eyes = EYES_ON;
      startCooldown();
    } else {
      creepy_eyes = EYES_OFF;
    }
  }
}

void PaintingPuzzle::activate() {
  printf("Painting puzzle activated\r\n");
  activated = true;
  reed_power = 1;
  creepy_eyes = EYES_OFF;
  reed_sense.fall(callback(this, &PaintingPuzzle::reedSenseIsr));
}

void test() {
  creepy_eyes = EYES_ON;
  wait(5);
  creepy_eyes = EYES_OFF;
  wait(10);
}

void PaintingPuzzle::solve() {
  if(coolingDown()) {
    creepy_eyes = EYES_ON;
  } else {
    creepy_eyes = EYES_OFF;
  }
}
