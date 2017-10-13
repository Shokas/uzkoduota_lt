#include "MagnetService.h"

const uint8_t num_of_magnets = 4;

Relay m1(PH_1);
Relay m2(PH_0);
Relay m3(PC_15);
Relay m4(PC_14);
Relay *mArray[] = {&m1, &m2, &m3, &m4};

MagnetController magnets(mArray, num_of_magnets);
