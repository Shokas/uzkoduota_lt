#include "mbed.h"
#include "MaskPuzzle.h"
#include "puzzle.h"
#include "MagnetService.h"
// #include "rtos.h"
// #include "HCSR04.h"
// #include "MFRC522.h"

// #define ON 0
// #define OFF 1
// #define BUFF_SIZE 128
// #define DIST_UPDATE_INTERVAL 0.2
// #define RELAYS 4
// #define TESTMODE true
// #define MF_RESET    D8

// Serial pc(SERIAL_TX, SERIAL_RX);
// DigitalOut led(D13);

// InterruptIn bigButton(PB_13);//(USER_BUTTON); //USER_BUTTON == PC_13
// InterruptIn motion_sensor(PB_8);
// //Reed sensor PA_5, PB_9
// //InterruptIn reed_sense(PB_9);
// DigitalIn reed_sense(PB_9);
// DigitalOut reed_power(PA_5);

// DigitalOut eyes(PA_6);

// //SRF05 sr(PC_1, PC_0);   // Trigger, Echo
// HCSR04 sr(PC_1, PC_0);
// //SRF05 sr2(PA_4, PB_0);  // Trigger, Echo
// HCSR04 sr2(PC_8, PC_6);
// //SRF05 sr3(PA_1, PA_0);  // Trigger, Echo
// //HCSR04 sr3(PB_15, PB_14);       //PB_14, PB_13
// MFRC522    RfChip   (PC_12, PC_11, PC_10, PD_2, PC_9);

// BusOut v5Relays(PB_7, PA_15, PA_14, PA_13);
// BusOut v12Relays(PH_1, PH_0, PC_15, PC_14);


// Ticker distTick;
// Ticker blinky;

//magnets PH_1, PH_0, PC_15, PC_14
//leds PB_7, PA_15, PA_14, PA_13

Puzzle *new_puzzle = new MaskPuzzle();

int main() {
  printf("Hello Game");
  magnets.allOff();
  new_puzzle->activate();
  while(1) {
    new_puzzle->solve();
    wait(2.0);
  }
}