#include <Adafruit_NeoPixel.h>
#include <HSBColor.h>
//Core Libraries
#include <Keypad.h>

//Local Database
#include <EDB.h>
#include <EEPROM.h>

#include "constants.h"

#include "neopixel.h"
#include "Dispenser.h"
#include "CoinReader.h"
#include "Buttons.h"
#include "EDB.h"

Dispenser dispenser;
CoinReader coinReader;
//Buttons buttons;

// CHANGE THIS TO CLEAR THE EEPROM
byte eepromValidateData = 3;

long credit;
long totalCredit;
long creditSinceCashout;
unsigned long showPriceTime; // time that we started showing the price.




long priceShownIndex;
long showPriceDuration;
int key;


boolean initialising = true;

Keypad buttons = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
boolean displayDirty = true; // flag that determines whether the display has updated and needs to be redrawn.

int mode = MODE_NORMAL;

int prices[] = {50, 50, 50, 50, 50, 50, 100, 100, 150, 150, 1500};

void setup() {

  initNeopixels();

  Serial.begin(9600);

  initPins();
  initEeprom();
  dispenser.setupPins();
  coinReader.setupPins();
  initDisplay();
  initDatabase();
  showPriceTime = 0;
  priceShownIndex = -1; // doesn't show if it's less than 1
  showPriceDuration = 2000;
  timeoutStartTime = 0;

  buttons.setDebounceTime(100);

  //tone(BUZZER_PIN, 880, 2000);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(50);
  digitalWrite(BUZZER_PIN, LOW);

}

void loop() {

  if (millis() > 5000) initialising = false;

  if (dispenser.canDispense()) {
    updateLeds(priceShownIndex);
  } else {
    updateLeds(dispenser.lastDispenseRow, true);
  }
  if (initialising) {
    updateDisplay();
    return;
  }

  if ((priceShownIndex > -1) && ((unsigned long) (millis() - showPriceTime) > 5000)) {
    updateCashString(credit);
    priceShownIndex = -1;
    displayDirty = true;

  }
  checkCoinReader();
  updateDisplay();
  checkButtons();


}

void checkCoinReader() {

  // this function needs to be called frequently or it may miss coins!
  // might be worth adding it to a timer (although it does need millis()
  // which may be unreliable from within a timer).

  int creditadded = coinReader.checkCoins();

  if (creditadded > 0) {


    // money has been entered!
    addCredit(creditadded);

    resetTimeout();
    coinDropCountdown = 132;


  }



}

void addCredit(int creditvalue) {
  credit += creditvalue;
  totalCredit += creditvalue;
  creditSinceCashout += creditvalue;
  writeCreditToEeprom();

  // update display
  updateCashString(credit);
  priceShownIndex = -1;


}

void resetCredit(int creditvalue) {
  credit = creditvalue;
  totalCredit = creditvalue;
  creditSinceCashout = creditvalue;
  writeCreditToEeprom();

  // update display
  updateCashString(credit);
  priceShownIndex = -1;


}
void payForItem(int debitvalue) {
  credit -= debitvalue;
  writeCreditToEeprom();

  // update display
  updateCashString(credit);
}

void checkButtons() {


  int dispenserCode = -1;
  int price = -1;
  key = buttons.getKey();
  if (key) {

    resetTimeout();

    Serial.println(key);
    int keyIndex = key - 1;
    if ((keyIndex >= 0) && (keyIndex <= 11)) {

      dispenserCode = dispenserKeyAssignments[keyIndex];
      price = prices[keyIndex];
    }
    /*
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

    */

    if (dispenserCode >= 0) {
      if (dispenser.canDispense() && (credit >= price)) {
        digitalWrite(BUZZER_PIN, HIGH);
        payForItem(price);
        updateDisplay();

        coinReader.disableCoinSlot();

        digitalWrite(BUZZER_PIN, LOW);

        if (dispenser.dispenseItem(dispenserCode, keyIndex)) {

          //Item dispensed
          //itemData.stockLevel --;
          //itemData.vendsSinceCashout ++;

          //Save back to the db
          //updateItem(key);

        } else {
          // if it didn't dispense (it should have)
          // then refund!
          addCredit(price);


        };
        coinReader.enableCoinSlot();
      } else if (credit < price) {

        digitalWrite(BUZZER_PIN, HIGH);

        priceShownIndex = keyIndex;
        showPriceTime = millis();
        updateCashString(price);

        delay(50);
        digitalWrite(BUZZER_PIN, LOW);

      }
    }
  } else {
    //noTone(BUZZER_PIN);
  }

  if (!digitalRead(ADMIN_BUTTON)) {
    resetTimeout();

    //debounce;
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);

    if (mode == MODE_NORMAL) {
      mode = MODE_ADMIN;
      Serial.println("ADMIN MODE");
    } else {
      mode = MODE_NORMAL;
      Serial.println("NORMAL MODE");
    }
    while (!digitalRead(ADMIN_BUTTON)) {
      if ((unsigned long) (millis() - timeoutStartTime) > 2000) {
        resetCredit(0);
        updateDisplay();
        digitalWrite(BUZZER_PIN, HIGH);
        delay(50);
        digitalWrite(BUZZER_PIN, LOW);
        while (!digitalRead(ADMIN_BUTTON));
      }


    };
    //debounce
    delay(100);
    displayDirty = true;
  }


}

void initPins() {

  for (int i = 0; i < sizeof(groundPins); i++) {
    pinMode(groundPins[i], OUTPUT);
    digitalWrite(groundPins[i], LOW);

  }

  pinMode(ADMIN_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

}

void resetTimeout() {
  timeoutStartTime = millis();
}
