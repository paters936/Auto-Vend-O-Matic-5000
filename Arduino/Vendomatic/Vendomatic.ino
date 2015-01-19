#include "constants.h"
#include "Dispenser.h"
#include "CoinReader.h"
#include "Buttons.h"

//Core Libraries
#include <Keypad.h>

Dispenser dispenser;
CoinReader coinReader;
//Buttons buttons;

// CHANGE THIS TO CLEAR THE EEPROM
byte eepromValidateData = 0; 

long credit; 
long totalCredit; 
long creditSinceCashout;

byte colPins[COLS] = {KEYPAD_COL0, KEYPAD_COL1};
 
byte rowPins[ROWS] = {KEYPAD_ROW0, 
              KEYPAD_ROW1,
              KEYPAD_ROW2,
              KEYPAD_ROW3,
              KEYPAD_ROW4,
              KEYPAD_ROW5,
              KEYPAD_ROW6,
              KEYPAD_ROW7,
              KEYPAD_ROW8,
              KEYPAD_ROW9};
char keys[ROWS][COLS] = {
                {1,11},
                {2,12},
                {3,13},
                {4,14},
                {5,15},
                {6,16},
                {7,17},
                {8,18},
                {9,19},
                {10,20}
              };
              
int dispenserKeyAssignments[] = {40,39,38,37,36,35,34,33,31,32,30,-1,-1,-1,-1};

Keypad buttons = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
boolean displayDirty = true; // flag that determines whether the display has updated and needs to be redrawn. 


void setup() {

  initEeprom(); 
  dispenser.setupPins();
  coinReader.setupPins();
  initDisplay();
  
  Serial.begin(9600);

}

void loop() {

  checkCoinReader(); 
  updateDisplay(); 

  checkButtons(); 


}

void checkCoinReader() { 

  // this function needs to be called frequently or it may miss coins! 
  // might be worth adding it to a timer (although it does need millis() 
  // which may be unreliable from within a timer). 

  int creditadded = coinReader.checkCoins(); 

  if(creditadded>0) { 
    // money has been entered!
    addCredit(creditadded); 


    

  }



}

void addCredit(int creditvalue) { 
  credit+=creditvalue; 
  totalCredit+=creditvalue; 
  creditSinceCashout+=creditvalue; 
  writeCreditToEeprom();
  
  // update display 
    updateCashString(credit); 

  

}

void checkButtons() { 
  int key = buttons.getKey();
  if (key) {
    Serial.println(key);
    int dispensercode = dispenserKeyAssignments[key-1]; 
    if(dispensercode>=0) {
      if(dispenser.canDispense()) { 
        addCredit(-50); 
        updateDisplay();
        
        coinReader.disableCoinSlot(); 
        if(!dispenser.dispenseItem(dispensercode)) { 
          // if it didn't dispense (it should have) 
          // then refund!
          addCredit(50); 
          
          
        };
        coinReader.enableCoinSlot(); 
      }
    }
  }

}


