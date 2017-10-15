#include "DistanceSensorPuzzle.h"
#include "HCSR04.h"

#define MAX_NUM_SENSORS 2

HCSR04 sr(PC_1, PC_0);
HCSR04 sr2(PC_8, PC_6);
//HCSR04 sr3(PB_15, PB_14);       //PB_14, PB_13

uint8_t sensorNum;
float dist, dist2;

void DistanceSensorPuzzle::activate() {
  printf("Distance Sensor Puzzle activated\r\n");
  activated = true;
  sensorNum = 1;
  dist = 200;
  dist2 = 200;
}

void DistanceSensorPuzzle::solve() {
  if(isActive() && !coolingDown()) {
    if(sensorNum == 1) {
      dist = sr.getCm();
      // if < 100, turn on LED lights
    }
    if(sensorNum == 2) {
      dist2 = sr2.getCm();
      // if < 100, turn on LED lights
    }
    printf("Sensor %d distance %.2f\r\n", sensorNum, dist);

    if((dist < 100) && (dist2 < 100)) {
      printf("Distance sensors solved\r\n");
      // open drawer
      this->startCooldown();
    }
    
    if(sensorNum == MAX_NUM_SENSORS) {
      sensorNum = 1;
    } else {
      sensorNum++;
    }
  }
}
