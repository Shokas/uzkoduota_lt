#include "mbed.h"
#include "rtos.h"
#include "HCSR04.h"
#include "MFRC522.h"

#define ON 0
#define OFF 1
#define BUFF_SIZE 128
#define DIST_UPDATE_INTERVAL 0.2
#define RELAYS 4
#define TESTMODE true
#define MF_RESET    D8

Serial pc(SERIAL_TX, SERIAL_RX);
DigitalOut led(D13);

InterruptIn bigButton(PB_13);//(USER_BUTTON); //USER_BUTTON == PC_13
Ticker distTick;
Ticker blinky;

//SRF05 sr(PC_1, PC_0);   // Trigger, Echo
HCSR04 sr(PC_1, PC_0);
//SRF05 sr2(PA_4, PB_0);  // Trigger, Echo
HCSR04 sr2(PC_8, PC_6);
//SRF05 sr3(PA_1, PA_0);  // Trigger, Echo
//HCSR04 sr3(PB_15, PB_14);       //PB_14, PB_13
MFRC522    RfChip   (PC_12, PC_11, PC_10, PD_2, PC_9);

BusOut v5Relays(PB_7, PA_15, PA_14, PA_13);
BusOut v12Relays(PH_1, PH_0, PC_15, PC_14);
BusOut masks(PA_10, PB_3, PB_5, PB_4, PB_10, PA_8, PA_9, PC_7, PB_6, PA_7);
DigitalOut eyes(PA_6);
//Reed sensor PA_5, PB_9
DigitalOut reed_power(PA_5);
//InterruptIn reed_sense(PB_9);
DigitalIn reed_sense(PB_9);
InterruptIn motion_sensor(PB_8);

Timer painting_cooldown_t;
Timer motion_sensor_cooldown_t;
Timer distance_sensors_cooldown_t;

volatile int bigButtonFlag = 0;
volatile int distFlag = 0;
volatile int sensorNum = 1;
char buffer[BUFF_SIZE];

double distance = 100.0;
double distance2 = 100.0;
double distance3 = 100.0;

volatile int currState = 3;
volatile int nextState = 0;
volatile int prevState = 0;

void blinky_handler();
void updateDistFlag();

void init_room(void);
void activate_trapdoor(void);
void activate_painting(void);
void activate_motion_sensor(void);
void activate_masks(void);
void activate_nfc_reader(void);
void activate_distance_sensors(void);
void activate_safe_puzzle(void);

void painting_solved(void);
void motion_triggered(void);
void open_drawer(uint8_t);
void close_drawer(uint8_t);

void startup();
void idle();
void intro();
void game();
void restart();

void initRelays();
void startGame();
void resetGame();

float updateDistance();
float updateDistance2();
float updateDistance3();

bool painting_activated = false;
bool masks_activated = false;
bool distance_sensors_activated = false;
bool motion_sensor_activated = false;
bool nfc_reader_activated = false;

volatile bool painting_cooldown = false;
volatile bool masks_cooldown = false;
volatile bool distance_sensors_cooldown = false;
volatile bool motion_sensor_cooldown = false;
volatile bool nfc_reader_cooldown = false;

int main() {
    pc.baud(9600);
    pc.printf("Game started\r\nController loading\r\n");
    blinky.attach(&blinky_handler, 0.5);
    bigButton.mode(PullDown);
    bigButton.rise(&startGame);
    reed_power = 1;    
    distTick.attach(&updateDistFlag, DIST_UPDATE_INTERVAL);
    RfChip.PCD_Init();
    
    
    pc.printf("Controller loaded.. \r\n");

    //pc.printf("\n\n\r***\n\rafter each button press serial port should print out:\n\r\"testing eyes\"\n\r\"testing masks\"\n\r\"testing 5v relays\"\n\r\"testing 12v relays\"\n\r\"testing distance sensors\"\n\n\r");
    
    float dst;
    int count = 0;
    
    bigButtonFlag = 0;
    led = 0;
    int i;
    
    init_room();
    
    //wait until button pressed
    pc.printf("Press button to start\r\n");
    
    while(!bigButtonFlag) {
        __WFI();
    }
    
    while(1) {
        for(i=0; i <= 5; i++) {
            v12Relays = ~(0x01 << i);
            wait(1);
        }
    }
    
    //when button pressed:
    pc.printf("start\n");
    
    //while(!pc.available()) {}
    //if(pc.scanf() == "start");
    
    activate_trapdoor();        
    while(1) {
        activate_painting();
        //activate_motion_sensor();
        //activate_nfc_reader();
        activate_distance_sensors();
        //activate_safe_puzzle();
        
        sensorNum++;
        if(sensorNum > 2) {
            sensorNum = 1;
        }
    }
/*
    while(1) {
          switch(currState) {
              case 0:           //test eyes
                pc.printf("testing eyes\n\r");
                while(!bigButtonFlag) {
//                    pc.printf("eyes");
                    eyes = !eyes;
                    wait(0.5);
                }
                break;
                
              case 1:           //test masks
                pc.printf("testing masks\n\r");
                masks = 0xFFF;
                i = 0;
                while(!bigButtonFlag) {
                    masks = ~(0x001 << i);
                    i += 1;
                    if(i == 10) i = 0;
                    wait(1);
                }
                break;
                
              case 2:           //test 5v relays
                pc.printf("testing 5v relays\n\r");
                v5Relays = 0xF;
                i = 0;
                while(!bigButtonFlag) {
                    v5Relays = ~(0x1 << i);
                    i += 1;
                    if(i == RELAYS) i = 0;
                    wait(1);
                }
                break;
                
              case 3:           //test 12v relays
                pc.printf("testing 12v relays\n\r");
                v12Relays = 0xF;
                i = 0;
                while(!bigButtonFlag) {
                    //v12Relays = 0x4;
                    //wait(1);
                    //v12Relays = 0x2;
                    //wait(1);
                    v12Relays = 0xB;
                    wait(1);
                }
                break;

              case 4:           //test distance sensors. stand under each one, corresponding LEDs should light up
                pc.printf("testing distance sensors\n\r");
                v5Relays = 0x0;
                wait(5);
                v5Relays = 0xF;
                while(!bigButtonFlag) {
                    if(distFlag == 1) {
                        distFlag = 0;
                        if(reed_sense == 1) {
                            v5Relays = v5Relays & ~(0x3 << 1);
                            pc.printf("REED\n\r");
                        } else {
                            v5Relays = v5Relays | (0x3 << 1);   
                        }
                        if(sensorNum == 1) {
                            distance = sr.getCm();
                            //sensorNum = 2;
                        }
                        if(sensorNum == 2) {
                            //distance = sr2.getCm();
                            //sensorNum = 3;
                            //pc.printf("2\n\r");
                            //pc.printf("S1 %7.3f S2 %7.3f S3 %7.3f %d\n\r", distance, distance2, distance3, sensorNum);
                        }
                        if(sensorNum == 3) {
                            distance = sr3.getCm();
                            //sensorNum = 1;
                            //pc.printf("3\n\r");
                            //pc.printf("S1 %7.3f S2 %7.3f S3 %7.3f %d\n\r", distance, distance2, distance3, sensorNum);
                        }
                        
                        pc.printf("%7.3f ", distance);
                        if(sensorNum != 2){
                        if(distance < 100.0) {
                            //v5Relays = v5Relays & ~(0x3 << (sensorNum - 1));
                        } else {
                            //Relays = v5Relays | (0x3 << (sensorNum - 1));
                        }
                    }
                        sensorNum++;
                        if(sensorNum > 3) {
                            sensorNum = 1;
                            pc.printf("\n\r");
                        }
                    }
                }
                break;
        }
        if(bigButtonFlag) {
            bigButtonFlag = 0;
            currState += 1;
        }
        if(currState > 4) currState = 0;
    }
*/
    pc.printf("Controller stopped\n\r");

    __WFI();
}

void init_room(void) {
    masks = 0x000;
    //v5Relays = 0x0;
    //v12Relays = 0x0;
    eyes = 0;
    nfc_reader_activated = true;
}

void activate_trapdoor(void) {
    v12Relays = 0x0;
    pc.printf("Trap door activated\r\n");
    //start playing soundtrack from speaker on top of drawer
    //play scary sound from TV speaker
}

void activate_painting(void) {
    if(!painting_activated) {
        painting_activated = true;
        //reed_sense.fall(&painting_solved);
        pc.printf("Painting activated\r\n");
    } else {
        eyes = reed_sense;
        //if(!painting_cooldown) {
//            eyes = 0;
//        } else {
//            eyes = 1;
//            pc.printf("Painting cooldown\r\n");
//            if(painting_cooldown_t.read() > 15) {
//                close_drawer(1);
//            } else {
//                open_drawer(1);
//                //play scary sound
//            }
//            if(painting_cooldown_t.read() > 120) {
//                painting_cooldown_t.stop();
//                painting_cooldown_t.reset();
//                painting_cooldown = false;
//                pc.printf("Painting cooldown reset\r\n");
//            }
//        }
    }
}

void activate_motion_sensor(void) {
    if(!motion_sensor_activated) {
        motion_sensor_activated = true;
        motion_sensor.fall(&motion_triggered);
    } else {
        if(motion_sensor_cooldown) {
            if(motion_sensor_cooldown_t.read() > 15) {
                close_drawer(2);
            } else {
                //play scary sound
                open_drawer(2);
                activate_masks();
                wait(5);
                activate_masks();
            }
            if(motion_sensor_cooldown_t.read() > 120) {
                motion_sensor_cooldown_t.stop();
                motion_sensor_cooldown_t.reset();
                motion_sensor_cooldown = false;
            }
        }
    }
    //motion sensor triggered (in the cupboard)
    //activate gas masks for 2 times. 5mins cooldown
    //open drawer for 10-15s. 2mins cooldown
}

void activate_nfc_reader(void) {
    if(nfc_reader_activated) {
        if(RfChip.PICC_IsNewCardPresent()) {
          wait_ms(200);
          distance_sensors_activated = true;
          nfc_reader_activated = false;
          pc.printf("RFID puzzle solved\r\n");
        }
    }
}

void activate_distance_sensors(void) {
    //two people under sensors at the same time
    //open drawer 10-15s, 2mins cooldown
    if(distance_sensors_activated) {
        if(distance_sensors_cooldown) {
            if(distance_sensors_cooldown_t.read() > 15){
                close_drawer(3);
            } else {
                open_drawer(3);
                pc.printf("Distance drawer open\r\n");
            }
            if(distance_sensors_cooldown_t.read() > 120) {
                distance_sensors_cooldown_t.stop();
                distance_sensors_cooldown_t.reset();
                distance_sensors_cooldown = false;
                pc.printf("Distance cooldown expired\r\n");
            }
        } else {
            if(sensorNum == 1) {
                distance = sr.getCm();
            }
            if(sensorNum == 2) {
                distance = sr2.getCm();
            }
            pc.printf("Sensor %d distance %.2f\r\n", sensorNum, distance);        
            if(distance < 100.0) {
                v5Relays = v5Relays & ~(0x1 << (sensorNum - 1));
            } else {
                v5Relays = v5Relays | (0x1 << (sensorNum - 1));
            }
            if(v5Relays == 0x3) {
                pc.printf("Distance sensors solved\r\n");
                distance_sensors_cooldown = true;
                distance_sensors_cooldown_t.start();
            }
            //if(distance < 100.0 && distance2 < 100.0) {
            //    
            //}
        }
    }
}

void activate_safe_puzzle(void) {
    //safe puzzle solved
    //open drawer for 20-25s, 2min cooldown
}

void activate_masks(void) {
    printf("Masks activated\r\n");
    int i;
    for(i=0; i <= 10; i++) {
        masks = 0x001 << i;
        wait(1);
    }
}

void open_drawer(uint8_t drawer) {
    switch(drawer) {
        case 1:
            //v12Relays = 0xE;
        break;
    }
}

void close_drawer(uint8_t drawer) {
    switch(drawer) {
        case 1:
            //v12Relays = 0xF;
        break;
    }
}

void painting_solved() {
    painting_cooldown = true;
    painting_cooldown_t.start();
}

void motion_triggered() {
    motion_sensor_cooldown = true;
    motion_sensor_cooldown_t.start();
}

void blinky_handler(){
  led = !led;
}

void updateDistFlag() {
    distFlag = 1;
    //if(sensorNum == 1) { sensorNum = 2; }
    //else if(sensorNum == 2) { sensorNum = 3; }
    //else sensorNum = 1;
    //sensorNum = 1;
}

void startGame() {
    v5Relays = 0xF;
    v12Relays = 0xF;
    bigButtonFlag = 1;
    #if TESTMODE
      //currState += 1;
    #endif
}

void resetGame() {
    bigButtonFlag = 0;
    currState = 0;
    nextState = 0;
    prevState = 0;
    led = 0;
    v5Relays = 0xF;
    v12Relays = 0xF;
}
