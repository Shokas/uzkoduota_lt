#include "NfcPuzzle.h"
#include "MFRC522.h"

// #define MF_RESET    D8
MFRC522 nfcItem(PC_12, PC_11, PC_10, PD_2, PC_9);

void NfcPuzzle::activate() {
  activated = true;
}

void NfcPuzzle::solve() {
  if(isActive() && !coolingDown()) {
    // do stuff
    
  }
}
