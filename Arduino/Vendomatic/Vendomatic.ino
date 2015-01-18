#include "pinDefinitions.h"
#include "Dispenser.h"
#include "CoinReader.h"
#include "Buttons.h"

//Core Libraries
#include <Keypad.h>

Dispenser dispenser;
CoinReader coinReader;
Buttons buttons;



void setup() {
  
  dispenser.setupPins();
  coinReader.setupPins();
  //buttons.setup();
  
  coinReader.disable();
}

void loop() {
  
  //keypad testing
  char key = buttons.read();
  if (key){
    Serial.println(key);
  }

  if(coinReader.update()) { 
     // money has been entered! 
     // update display 
    
  }
  


}
