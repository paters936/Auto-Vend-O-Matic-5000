#include "Arduino.h"
#include "pinDefinitions.h"

#define COIN_TIMEOUT 2000
#define COIN_TYPE_COUNT 6

class CoinReader {
public:

  CoinReader();

  void setupPins();
  void disable();
  void activate();

  void update(); 


private:

  unsigned long lastCoinTime; 
  unsigned long now; 

  int coinPins[COIN_TYPE_COUNT];
  int coinValues[COIN_TYPE_COUNT];
  



};


CoinReader::CoinReader () { 
  
  coinPins[0] = COIN_PIN_5;
  coinPins[1] = COIN_PIN_10;
  coinPins[2] = COIN_PIN_20; 
  coinPins[3] = COIN_PIN_50; 
  coinPins[4] = COIN_PIN_100; 
  coinPins[5] = COIN_PIN_200 ;

  coinValues[0] = 5; 
  coinValues[1] = 10; 
  coinValues[2] = 20; 
  coinValues[3] = 50; 
  coinValues[4] = 100; 
  coinValues[5] = 200; 
  
  lastCoinTime = 0; 
 

}

void CoinReader::update() { 

  // if the last coin was more than 2 seconds ago, then check the other coin pins

  now = millis(); 


  if((unsigned long) (now-lastCoinTime) > COIN_TIMEOUT) { 
    // check all the coins! 
    for(int i = 0; i< COIN_TYPE_COUNT; i++) { 
      if(digitalRead(coinPins[i])) { 
         // debounce? 
         // add credit
         lastCoinTime = now; 
         break; 
       
      } 

    }

  }

};


void CoinReader::setupPins() {

  pinMode(COIN_PIN_RETURN, INPUT_PULLUP);
  pinMode(COIN_PIN_BLOCK, OUTPUT);

  for(int i = 0; i< COIN_TYPE_COUNT; i++) { 
    pinMode(coinPins[i], OUTPUT);  

  }

};

void CoinReader::disable() {
  digitalWrite(COIN_PIN_BLOCK, true);
};

void CoinReader::activate() {
  digitalWrite(COIN_PIN_BLOCK, false);
};


