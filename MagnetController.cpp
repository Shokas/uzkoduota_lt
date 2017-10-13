#include "MagnetController.h"

MagnetController::MagnetController(Relay *rArray[], uint8_t num) {
  numberOfRelays = num;
  relays = *rArray;
  allOn();
}

void MagnetController::allOff() {
  for(int i=0; i<numberOfRelays; i++) {
    relays[i].turnOff();
  }
}

void MagnetController::allOn() {
  for(int i=0; i<numberOfRelays; i++) {
    relays[i].turnOn();
  }
}

void MagnetController::turnOff(uint8_t item) {
  relays[item].turnOff();
}

void MagnetController::turnOn(uint8_t item) {
  relays[item].turnOn();
}

void MagnetController::toggle(uint8_t item) {
  if(relays[item].isOn()) {
    relays[item].turnOff();
  } else {
    relays[item].turnOn();
  }
}
