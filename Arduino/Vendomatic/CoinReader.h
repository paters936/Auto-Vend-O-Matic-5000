#include "Arduino.h"
#include "pinDefinitions.h"

// minimum time between coins
#define COIN_TIMEOUT 600 
#define COIN_TYPE_COUNT 6

class CoinReader {
public:

  CoinReader();

  void setupPins();
  void disableCoinSlot();
  void enableCoinSlot();

  int checkCoins(); 
  //  long getCredit(); 
  //  long subtractCredit(long amount); 
  //  long addCredit(long amount); 


private:

  unsigned long lastCoinTime; 
  unsigned long now; 

  int coinPins[COIN_TYPE_COUNT];
  int coinValues[COIN_TYPE_COUNT];
  //long credit; 




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

  // credit = 0; 




}

int CoinReader::checkCoins() { 

  // if the last coin was more than 2 seconds ago, then check the other coin pins

    now = millis(); 

  // if it's been a second (time out value) since the last coin
  if((unsigned long) (now-lastCoinTime) > COIN_TIMEOUT) { 

    // re enable coin slot
    enableCoinSlot();  

    // check all the coins! 
    for(int i = 0; i< COIN_TYPE_COUNT; i++) { 
      if(digitalRead(coinPins[i]) == LOW) { 
        lastCoinTime = now; 
        disableCoinSlot(); 
        return (coinValues[i]); 
      } 

    }

  } 

  return 0; 

};


void CoinReader::setupPins() {

  pinMode(COIN_PIN_RETURN, INPUT_PULLUP);
  pinMode(COIN_PIN_BLOCK, OUTPUT);
  pinMode(COIN_PIN_BLOCK_LED, OUTPUT);
  
  for(int i = 0; i< COIN_TYPE_COUNT; i++) { 
    pinMode(coinPins[i], INPUT_PULLUP);  

  }

};

void CoinReader::disableCoinSlot() {
  digitalWrite(COIN_PIN_BLOCK, true);
  digitalWrite(13, true); 
};

void CoinReader::enableCoinSlot() {
  digitalWrite(COIN_PIN_BLOCK, false);
  digitalWrite(13, false); 

};








