#include "Arduino.h"
#include "pinDefinitions.h"

// minimum time between coins
#define COIN_TIMEOUT 300 
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
  unsigned long lastReleaseTime; 
  unsigned long now; 

  int coinPins[COIN_TYPE_COUNT];
  int coinValues[COIN_TYPE_COUNT];
  int currentCoin; 




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

  // used to "remember" the last coin found so we can 
  // make sure it doesn't get read twice. 
  currentCoin = -1; 



}

int CoinReader::checkCoins() { 


  now = millis(); 

  // if the last coin was more than COIN_TIMEOUT milliseconds ago, then recheck all other coin pins
  if((unsigned long) (now-lastCoinTime) > COIN_TIMEOUT)  { 

    // check all the coins! 
    for(int i = 0; i< COIN_TYPE_COUNT; i++) { 
      if(digitalRead(coinPins[i]) == LOW) { 
        
        // this ensures that the clock only starts once the coin is
        // no longer being read. 
        
        lastCoinTime = now; 
        
        // if we've already seen this coin... 
        if(i==currentCoin) {
          return 0; 
        }
        
        // otherwise - we found a coin - yay!
        disableCoinSlot(); 
        currentCoin = i; 
        return (coinValues[i]); 
      } 

    }

    // at this point we can be sure that no coin is currently being read
    // and that the required time has passed since the last coin. 
    
    // no coin pin is currently low so reset the currentCoin check. 
    currentCoin = -1;
    // re enable coin slot 
    enableCoinSlot();  

  } 

  return 0; 

};
/*

 if((unsigned long) (now-lastReleaseTime) > 100){
 // debounces the "off" state
 if(currentCoin>-1) { 
 lastReleaseTime = now;  
 }
 
 */
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










