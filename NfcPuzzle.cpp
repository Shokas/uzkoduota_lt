#include "NfcPuzzle.h"
#include "MFRC522.h"

// #define MF_RESET    D8
MFRC522 nfcReader(PC_12, PC_11, PC_10, PD_2, PC_9);

void NfcPuzzle::activate() {
  printf("NFC Puzzle activated\r\n");
  activated = true;
}

void NfcPuzzle::solve() {
  if(isActive() && !coolingDown()) {
    if(nfcReader.PICC_IsNewCardPresent()) {
      printf("NFC Puzzle solved\r\n");
      this->deactivate();
      // activate distance sensor puzzle
    }
  }
}
