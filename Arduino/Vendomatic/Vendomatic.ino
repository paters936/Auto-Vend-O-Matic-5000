#include "pinDefinitions.h"
#include "Dispenser.h"
#include "CoinReader.h"
#include "Buttons.h"

//Core Libraries
#include <Keypad.h>

Dispenser dispenser;
CoinReader coinReader;
Buttons buttons;

long credit; 


void setup() {

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
  // might be worth adding it to a timer. Although it does need millis(). 
  
  int creditadded = coinReader.checkCoins(); 

  if(creditadded>0) { 
    // money has been entered!
    credit+=creditadded; 
    
    // update display 
    updateCashString(credit); 
    
    // update internal eeprom money received value

  }



}

