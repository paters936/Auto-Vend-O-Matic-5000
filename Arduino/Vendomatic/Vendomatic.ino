#include "constants.h"
#include "Dispenser.h"
#include "CoinReader.h"
#include "Buttons.h"

//Core Libraries
#include <Keypad.h>

//Local Database
#include <EDB.h>
#include <EEPROM.h>

Dispenser dispenser;
CoinReader coinReader;
//Buttons buttons;




//Setup the structure of the stored dispenser item data
struct ItemData {
  char id[13];
  char name[21];
  int price;
  int stockLevel;
  int vendsSinceCashout;
} 
itemData;



//Setup the database for the items
// The read and write handlers for using the EEPROM Library
void writer(unsigned long address, byte data) {
    EEPROM.write(address, data);     //external
}
byte reader(unsigned long address) {
    return EEPROM.read(address);     //external
}
// Create an EDB object with the appropriate write and read handlers
EDB itemDb(&writer, &reader);





// CHANGE THIS TO CLEAR THE EEPROM
byte eepromValidateData = 2; 

long credit; 
long totalCredit; 
long creditSinceCashout;

boolean initialising = true; 

byte colPins[COLS] = {KEYPAD_COL0, KEYPAD_COL1};
 
byte rowPins[ROWS] = {KEYPAD_ROW0, 
              KEYPAD_ROW1,
              KEYPAD_ROW2,
              KEYPAD_ROW3,
              KEYPAD_ROW4,
              KEYPAD_ROW5,
              KEYPAD_ROW6,
              KEYPAD_ROW7,
              KEYPAD_ROW8,
              KEYPAD_ROW9};
char keys[ROWS][COLS] = {
                {1,11},
                {2,12},
                {3,13},
                {4,14},
                {5,15},
                {6,16},
                {7,17},
                {8,18},
                {9,19},
                {10,20}
              };
              
int dispenserKeyAssignments[] = {40,39,38,37,36,35,34,33,31,32,30,-1,-1,-1,-1};

Keypad buttons = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
boolean displayDirty = true; // flag that determines whether the display has updated and needs to be redrawn. 


void setup() {

  initEeprom(); 
  dispenser.setupPins();
  coinReader.setupPins();
  initDisplay();
  
  
  
  //Database - wipe existing db
  itemDb.create(ITEM_DB_START, ITEM_DB_TABLE_SIZE, sizeof(itemData));
  
  //Database - open without wiping
  itemDb.open(ITEM_DB_START);
  
  
  
  createDefaultRecords();
  
  Serial.begin(9600);

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
        addCredit(-50); 
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
  }

}



boolean lookupItem(int keyPress) {
  
  //fetch the item from the db
  EDB_Status result = itemDb.readRec(keyPress, EDB_REC itemData);
  if (result == EDB_OK) {
    return true;
  } else {
    return false;
  }
}


boolean updateItem(int keyPress) {
  EDB_Status result = itemDb.updateRec(keyPress, EDB_REC itemData);
  if (result == EDB_OK) {
    return true;
  } else {
    return false;
  }
}


void createDefaultRecords() {
  //create records - testing
  for (int recno = 1; recno <= 11; recno++)
  {
    copyString(itemData.id, "ID");
    copyString(itemData.name, "Name");
    itemData.price = recno * 2;
    itemData.vendsSinceCashout = 0;
    itemData.stockLevel = 10;
    itemDb.appendRec(EDB_REC itemData);
  }
}





//Helper method
void copyString(char *p1, char *p2)
{
    while(*p2 !='\0')
    {
       *p1 = *p2;
       p1++;
       p2++;
     }
    *p1= '\0';
}

