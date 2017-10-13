#ifndef MAGNET_CONTROLLER_H
#define MAGNET_CONTROLLER_H

#include "relay.h"

struct MagnetController {
  MagnetController(Relay *[], uint8_t);

  void allOn();
  void allOff();
  void turnOn(uint8_t);
  void turnOff(uint8_t);
  void toggle(uint8_t);

private:
  Relay *relays;
  uint8_t numberOfRelays;
};

#endif