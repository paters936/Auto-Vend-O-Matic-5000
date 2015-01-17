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
}

void loop() {
  
  coinReader.update() ;
  

}
