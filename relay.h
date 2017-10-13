#ifndef RELAY_H
#define RELAY_H

#include "mbed.h"

struct Relay {
  Relay(PinName pin) : rOut(pin), turnedOn(false){
    rOut = 1;
  };

  void turnOn();
  void turnOff();
  bool isOn();

private:
  DigitalOut rOut;
  bool turnedOn;
};

#endif
