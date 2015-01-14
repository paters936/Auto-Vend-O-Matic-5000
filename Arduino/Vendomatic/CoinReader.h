#include "Arduino.h"
#include "pinDefinitions.h"

class CoinReader {
  public:

    void setupPins() {
        pinMode(COIN_PIN3, INPUT_PULLUP);
        pinMode(COIN_PIN4, INPUT_PULLUP);
        pinMode(COIN_PIN5, INPUT_PULLUP);
        pinMode(COIN_PIN6, OUTPUT);
        pinMode(COIN_PIN7, INPUT_PULLUP);
        pinMode(COIN_PIN8, INPUT_PULLUP);
        pinMode(COIN_PIN9, INPUT_PULLUP);
        pinMode(COIN_PIN10, INPUT_PULLUP);
    }

    void disable(int trueFalse) {
        digitalWrite(COIN_PIN6, trueFalse);
    };

  private:

};
