#include "mbed.h"
#include "puzzle.h"
#include "DrawerController.h"
#include "PaintingPuzzle.h"
#include "MotionSensorPuzzle.h"
#include "NfcPuzzle.h"
#include "DistanceSensorPuzzle.h"
// #include "rtos.h"

DigitalOut led(D13);

// InterruptIn bigButton(PB_13);//(USER_BUTTON); //USER_BUTTON == PC_13

// Ticker distTick;
Ticker blinky;

//magnets PH_1, PH_0, PC_15, PC_14
//leds PB_7, PA_15, PA_14, PA_13

Serial pc(USBTX, USBRX);

Puzzle *painting_puzzle = new PaintingPuzzle();
Puzzle *motion_puzzle = new MotionSensorPuzzle();
Puzzle *nfc_puzzle = new NfcPuzzle();
Puzzle *distance_puzzle = new DistanceSensorPuzzle();
//SafePuzzle

void blinky_ISR() {
  led = !led;
}

int main() {
  printf("Hello Game\r\n");
  led = 0;
  blinky.attach(&blinky_ISR, 1.0);
  magnets.turnOff(MAG1);  //activate trap door
  painting_puzzle->activate();
  motion_puzzle->activate();
  nfc_puzzle->activate();
  distance_puzzle->activate();

  painting_puzzle->solve();
  motion_puzzle->solve();
  // while(1) {
  //   painting_puzzle->solve();
  //   motion_sensor_puzzle->solve();
  //   __WFI();
  // }
}