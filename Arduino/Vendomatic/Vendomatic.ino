#include "constants.h"
#include "Dispenser.h"
#include "CoinReader.h"
#include "Buttons.h"


//Core Libraries
#include <Keypad.h>

Dispenser dispenser;
CoinReader coinReader;
Buttons buttons;

// CHANGE THIS TO CLEAR THE EEPROM
byte eepromValidateData = 0; 


long credit; 
long totalCredit; 
long creditSinceCashout;


void setup() {

  initEeprom(); 
  dispenser.setupPins();
  coinReader.setupPins();
  initDisplay();

}

void loop() {

  checkCoinReader(); 
  updateDisplay(); 

}

void checkCoinReader() { 

  // this function needs to be called frequently or it may miss coins! 
  // might be worth adding it to a timer (although it does need millis() 
  // which may be unreliable from within a timer). 

  int creditadded = coinReader.checkCoins(); 

  if(creditadded>0) { 
    // money has been entered!
    addCredit(creditadded); 


    // update display 
    updateCashString(credit); 


  }



}

void addCredit(int creditvalue) { 
  credit+=creditvalue; 
  totalCredit+=creditvalue; 
  creditSinceCashout+=creditvalue; 
  writeCreditToEeprom();

}


