#include "relay.h"

void Relay::turnOn() {
  turnedOn = true;
  rOut = 0;
}

void Relay::turnOff() {
  turnedOn = false;
  rOut = 1;
}

bool Relay::isOn() {
  return turnedOn;
}
