#include "pinDefinitions.h"
#include "Dispenser.h"
#include "CoinReader.h"

Dispenser dispenser;
CoinReader coinReader;

void setup() {
  
  dispenser.setupPins();
  coinReader.setupPins();
}

void loop() {
  

}
