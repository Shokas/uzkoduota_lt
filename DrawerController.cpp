#include "DrawerController.h"

const uint8_t num_of_magnets = 4;

Relay m1(PH_1);
Relay m2(PH_0);
Relay m3(PC_15);
Relay m4(PC_14);
Relay *mArray[] = {&m1, &m2, &m3, &m4};

MagnetController magnets(mArray, num_of_magnets);

namespace MagnetDoors {
  void openDrawer(uint8_t location) {
    magnets.turnOff(location);
  }

  void closeDrawer(uint8_t location) {
    magnets.turnOn(location);
  }

  void openTrapdoor() {
    magnets.turnOff(0);
  }

  void closeTrapdoor() {
    magnets.turnOn(0);
  }

  void test() {
    magnets.turnOff(DRAWER1);
    wait(10);
    magnets.turnOn(DRAWER1);
    wait(10);
    magnets.turnOff(DRAWER2);
    wait(10);
    magnets.turnOn(DRAWER2);
    wait(10);
    magnets.turnOff(DRAWER3);
    wait(10);
    magnets.turnOn(DRAWER3);
    wait(10);
    magnets.turnOff(DRAWER4);
    wait(10);
    magnets.turnOn(DRAWER4);
  }
}
