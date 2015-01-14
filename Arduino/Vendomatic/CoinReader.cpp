#include "CoinReader.h"
#include "pinDefinitions.h"

void CoinReader::setupPins() {
  pinMode(COIN_PIN3, INPUT_PULLUP);
  pinMode(COIN_PIN4, INPUT_PULLUP);
  pinMode(COIN_PIN5, INPUT_PULLUP);
  pinMode(COIN_PIN6, OUTPUT);
  pinMode(COIN_PIN7, INPUT_PULLUP);
  pinMode(COIN_PIN8, INPUT_PULLUP);
  pinMode(COIN_PIN9, INPUT_PULLUP);
  pinMode(COIN_PIN10, INPUT_PULLUP);
}

//Stop the coin reader from accepting any coins
void CoinReader::disable(int trueFalse) {
  digitalWrite(COIN_PIN6, trueFalse);
}
