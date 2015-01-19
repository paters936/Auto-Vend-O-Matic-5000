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



 byte _colPins[COLS] = {KEYPAD_COL0, KEYPAD_COL1};
 
    byte _rowPins[ROWS] = {KEYPAD_ROW0, 
                      KEYPAD_ROW1,
                      KEYPAD_ROW2,
                      KEYPAD_ROW3,
                      KEYPAD_ROW4,
                      KEYPAD_ROW5,
                      KEYPAD_ROW6,
                      KEYPAD_ROW7,
                      KEYPAD_ROW8,
                      KEYPAD_ROW9};
    char _keys[ROWS][COLS] = {
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

Keypad buttons = Keypad( makeKeymap(_keys), _rowPins, _colPins, ROWS, COLS);



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


  int key = buttons.getKey();
  if (key) {
    Serial.println(key);
    dispenser.dispenseItem(dispenserKeyAssignments[key]);
  }
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


