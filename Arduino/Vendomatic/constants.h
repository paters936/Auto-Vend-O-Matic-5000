
#pragma once 

//Despenser
#define DISPENSER_CLOCK  A8
#define DISPENSER_DATA   A11
#define DISPENSER_LATCH  A9
#define DISPENSER_ENABLE A10
#define DISPENSER_PURPLE A12  //not sure what purple is!

// ** ** ** **    ** ** ** **
// 32 34 36 38 40 42 44 46 48

//Coin Acceptor
#define COIN_PIN_100  38 //£1      // pin 3
#define COIN_PIN_200  42 //£2      // pin 4
#define COIN_PIN_5    34 //5p      // pin 7
#define COIN_PIN_10   46 //10p     // pin 8
#define COIN_PIN_20   32 //20p     // pin 9
#define COIN_PIN_50   48 //50p     // pin 10

#define COIN_PIN_RETURN  36 //input - coin return // pin 5

#define COIN_PIN_BLOCK   44 //high - stops money  // pin 6
#define COIN_PIN_BLOCK_LED 13 // to preview when coin block is active

////Keypad
#define KEYPAD_COL0 53
#define KEYPAD_COL1 51
#define KEYPAD_ROW0 49
#define KEYPAD_ROW1 47
#define KEYPAD_ROW2 45
#define KEYPAD_ROW3 43
#define KEYPAD_ROW4 41
#define KEYPAD_ROW5 39
#define KEYPAD_ROW6 37
#define KEYPAD_ROW7 35
#define KEYPAD_ROW8 33
#define KEYPAD_ROW9 31

//#define KEYPAD_COL0 31
//#define KEYPAD_COL1 33
//#define KEYPAD_ROW0 35
//#define KEYPAD_ROW1 37
//#define KEYPAD_ROW2 39
//#define KEYPAD_ROW3 41
//#define KEYPAD_ROW4 43
//#define KEYPAD_ROW5 45
//#define KEYPAD_ROW6 47
//#define KEYPAD_ROW7 49
//#define KEYPAD_ROW8 51
//#define KEYPAD_ROW9 53

#define ROWS 10
#define COLS 2

//neo pixel
#define NEOPIXEL 4
#define PIXELS_PER_ROW 12
#define NUM_ROWS 11

// led time out and screen saver 300000 == five minutes
#define TIMEOUTMILLIS 300000 

// EEPROM
// EEPROM data validate address is 0 
#define EEPROM_CREDIT_START_ADDRESS 0 // 1 byte

//Database
#define ITEM_DB_START 20
#define ITEM_DB_TABLE_SIZE 512

#define BUZZER_PIN A0
#define ADMIN_BUTTON A1

int groundPins[] = {17, 19}; 

#define MODE_NORMAL 0
#define MODE_ADMIN 1

