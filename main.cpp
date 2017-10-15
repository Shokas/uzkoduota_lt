#include "mbed.h"
#include "puzzle.h"
#include "DrawerController.h"
#include "PaintingPuzzle.h"
#include "MotionSensorPuzzle.h"
#include "NfcPuzzle.h"
#include "DistanceSensorPuzzle.h"
#include "SafePuzzle.h"

InterruptIn bigButton(USER_BUTTON); //USER_BUTTON == PC_13; BIG_BUTTON(PB_13);//

//magnets PH_1, PH_0, PC_15, PC_14
//leds PB_7, PA_15, PA_14, PA_13

Serial pc(USBTX, USBRX);

Puzzle *painting_puzzle = new PaintingPuzzle();
Puzzle *motion_puzzle = new MotionSensorPuzzle();
Puzzle *nfc_puzzle = new NfcPuzzle();
Puzzle *distance_puzzle = new DistanceSensorPuzzle();
Puzzle *safe_puzzle = new SafePuzzle();

int main() {
  printf("Hello Game\r\n");
  painting_puzzle->activate();
  safe_puzzle->activate();
  // motion_puzzle->activate();
  // nfc_puzzle->activate();
  // distance_puzzle->activate();

  while(1) {
    painting_puzzle->solve();
    safe_puzzle->solve();

  // motion_puzzle->solve();
  // motion_sensor_puzzle->solve();
    __WFI();
  }
}