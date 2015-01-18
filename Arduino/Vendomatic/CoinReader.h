#include "Arduino.h"
#include "pinDefinitions.h"

#define COIN_TIMEOUT 2000
#define COIN_TYPE_COUNT 6

class CoinReader {
public:

  CoinReader();

  void setupPins();
  void disableCoinSlot();
  void enableCoinSlot();

  boolean update(); 
  long getCredit(); 
  long subtractCredit(long amount); 
  long addCredit(long amount); 


private:

  unsigned long lastCoinTime; 
  unsigned long now; 

  int coinPins[COIN_TYPE_COUNT];
  int coinValues[COIN_TYPE_COUNT];
  long credit; 




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

  credit = 0; 
  
  


}

boolean CoinReader::update() { 

  // if the last coin was more than 2 seconds ago, then check the other coin pins
  boolean changed = false; 
  
  now = millis(); 


  if((unsigned long) (now-lastCoinTime) > COIN_TIMEOUT) { 

    enableCoinSlot();  // could poss be cleverer about this - store an enabled flag? 

    // check all the coins! 
    for(int i = 0; i< COIN_TYPE_COUNT; i++) { 
      if(digitalRead(coinPins[i])) { 
        // debounce? 
        // add credit
        addCredit(coinValues[i]); 
        lastCoinTime = now; 
        disableCoinSlot(); 
        break; 

      } 

    }

  } else { 
    disableCoinSlot(); 
  }
  
  return changed; 
  
};

long CoinReader :: getCredit() {
  return credit;  
}
long CoinReader :: addCredit(long value) { 
  credit+=value; 
  return credit;  


}
long CoinReader :: subtractCredit(long value) {
  credit-=value; 
  return credit;  
}


void CoinReader::setupPins() {

  pinMode(COIN_PIN_RETURN, INPUT_PULLUP);
  pinMode(COIN_PIN_BLOCK, OUTPUT);

  for(int i = 0; i< COIN_TYPE_COUNT; i++) { 
    pinMode(coinPins[i], OUTPUT);  

  }

};

void CoinReader::disableCoinSlot() {
  digitalWrite(COIN_PIN_BLOCK, true);
};

void CoinReader::enableCoinSlot() {
  digitalWrite(COIN_PIN_BLOCK, false);
};







