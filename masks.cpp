#include "mbed.h"
#include "rtos.h"

#define NUM_MASKS 10
BusOut mask_leds(PA_10, PB_3, PB_5, PB_4, PB_10, PA_8, PA_9, PC_7, PB_6, PA_7);

namespace masks {
  void setup() {
    mask_leds = 0x000;
  }

  void activate() {
    printf("Masks activated\r\n");
    uint8_t i;
    for(i=0; i<=NUM_MASKS; i++) {
      masks = 0x001 << i;
      Thread::wait(2);
    }
  }
}
