//Core Libraries
#include <Keypad.h>

//Local Database
#include <EDB.h>
#include <EEPROM.h>

#include "constants.h"
#include "Dispenser.h"
#include "CoinReader.h"
#include "Buttons.h"
#include "EDB.h"



Dispenser dispenser;
CoinReader coinReader;
//Buttons buttons;



// CHANGE THIS TO CLEAR THE EEPROM
byte eepromValidateData = 1; 

long credit; 
long totalCredit; 
long creditSinceCashout;

boolean initialising = true; 


Keypad buttons = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
boolean displayDirty = true; // flag that determines whether the display has updated and needs to be redrawn. 

int mode = MODE_NORMAL;


void setup() {
 
  Serial.begin(9600);
  
  initPins(); 
  initEeprom(); 
  dispenser.setupPins();
  coinReader.setupPins();
  initDisplay();
  initDatabase(); 
  
 tone(BUZZER_PIN, 880, 2000); 

}

void loop() {

  if(millis()>5000) initialising = false; 
  
  if(initialising) return; 
  
  checkCoinReader(); 
  updateDisplay(); 
  checkButtons(); 


}

void checkCoinReader() { 

  // this function needs to be called frequently or it may miss coins! 
  // might be worth adding it to a timer (although it does need millis() 
  // which may be unreliable from within a timer). 

  int creditadded = coinReader.checkCoins(); 

  if(creditadded>0) { 
    // money has been entered!
    addCredit(creditadded); 


    

  }



}

void addCredit(int creditvalue) { 
  credit+=creditvalue; 
  totalCredit+=creditvalue; 
  creditSinceCashout+=creditvalue; 
  writeCreditToEeprom();
  
  // update display 
    updateCashString(credit); 

  

}

void payForItem(int debitvalue) { 
   credit-=debitvalue; 
  writeCreditToEeprom();
  
  // update display 
    updateCashString(credit); 
}

void checkButtons() { 
  
  
  
  int key = buttons.getKey();
  if (key) {
    
    Serial.println(key);
    int dispensercode = dispenserKeyAssignments[key-1];
    
    //Look the item up in the database
    bool itemLookupSuccess = lookupItem(key);
    if (!itemLookupSuccess) {
      //error locating item
      Serial.println("Error looking up item");
    } else {
      //if (itemData.stockLevel <= 0) {
        //We have no stock
        //Serial.println("No Stock");
      //}
      //Serial.print("Price: ");
      //Serial.println(itemData.price);
      
      //Serial.print("Stock Level: ");
      //Serial.println(itemData.stockLevel);
      
      //Serial.print("Sales: ");
      //Serial.println(itemData.vendsSinceCashout);
    
    }
    
    
    if(dispensercode>=0) {
      if(dispenser.canDispense() && (credit >= 50)) { 
        tone(BUZZER_PIN, 800, 100); 
        payForItem(50); 
        updateDisplay();
        
        coinReader.disableCoinSlot();
        if(dispenser.dispenseItem(dispensercode)) { 
          
          //Item dispensed
          //itemData.stockLevel --;
          //itemData.vendsSinceCashout ++;
          
          //Save back to the db
          //updateItem(key);
          
        } else {
          // if it didn't dispense (it should have) 
          // then refund!
          addCredit(50); 
          
          
        };
        coinReader.enableCoinSlot(); 
      }
    } 
  }else { 
      //noTone(BUZZER_PIN); 
  }

  if(!digitalRead(ADMIN_BUTTON)) { 
    //debounce; 
    tone(BUZZER_PIN, 800,100); 
    delay(100); 
    if(mode == MODE_NORMAL) { 
      mode = MODE_ADMIN; 
      Serial.println("ADMIN MODE"); 
    } else { 
      mode = MODE_NORMAL; 
      Serial.println("NORMAL MODE"); 
    }
    while(!digitalRead(ADMIN_BUTTON)); 
    //debounce
    delay(100); 
    displayDirty = true;
  }

}

void initPins() { 
  
  for(int i = 0; i<sizeof(groundPins);i++){
    pinMode(groundPins[i], OUTPUT); 
    digitalWrite(groundPins[i], LOW); 
    
  }
  
  pinMode(ADMIN_BUTTON, INPUT_PULLUP); 
  pinMode(BUZZER_PIN, OUTPUT); 

}
