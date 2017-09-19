#include "mbed.h"
#include "rtos.h"

#define RELAY_ON 0
#define RELAY_OFF 1
#define ALL_OFF 0xFFF
#define ALL_ON 0x000

// relays are active low
BusOut magnet_relays(PH_1, PH_0, PC_15, PC_14);

void turnOn(uint8_t relay) {
  magnet_relays &= ~(0x1 << (relay - 1));
}

void turnOff(uint8_t relay) {
  magnet_relays |= 0x1 << (relay - 1);
}

namespace magnets {
  void setup() {
    // turn off all relays
    magnet_relays = ALL_OFF;
  }
}