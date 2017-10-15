#ifndef DRAWER_CONTROLLER_H
#define DRAWER_CONTROLLER_H

#include "MagnetController.h"

extern MagnetController magnets;

enum MagnetLocation {
  TRAPDOOR,
  DRAWER1,
  DRAWER2,
  DRAWER3,
  DRAWER4
};

namespace MagnetDoors {
  void openDrawer(uint8_t);
  void closeDrawer(uint8_t);
  void openTrapdoor();
  void closeTrapdoor();
  void test();
}

#endif
