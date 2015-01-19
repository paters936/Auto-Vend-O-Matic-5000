//#include "Arduino.h"
//#include "constants.h"
//#include <Keypad.h>
//
////const byte ROWS = 10; //four rows
////const byte COLS = 2; //three columns
///*
//char keys[ROWS][2] = {
//  {'1','B'},
//  {'2','C'},
//  {'3','D'},
//  {'4','E'},
//  {'5','F'},
//  {'6','G'},
//  {'7','H'},
//  {'8','I'},
//  {'9','J'},
//  {'A','K'}
//};
//
//
//byte rowPins[ROWS] = {KEYPAD_ROW0, 
//                      KEYPAD_ROW1,
//                      KEYPAD_ROW2,
//                      KEYPAD_ROW3,
//                      KEYPAD_ROW4,
//                      KEYPAD_ROW5,
//                      KEYPAD_ROW6,
//                      KEYPAD_ROW7,
//                      KEYPAD_ROW8,
//                      KEYPAD_ROW9}; //connect to the row pinouts of the keypad
// //connect to the column pinouts of the keypad
//*/
//class Buttons {
//    public:
//        Buttons();
//        char getKey();
//        
//    private:
//        static const int ROWS = 10;
//        static const int COLS = 2;
//        
//        Keypad _keypad;
//        byte _colPins[COLS];
//        byte _rowPins[ROWS];
//        char _keys[ROWS][COLS];
//};
//
////Initialise the buttons class and create the keypad object
//Buttons::Buttons() : _keypad( makeKeymap(_keys), _rowPins, _colPins, ROWS, COLS) {
//    byte _colPins[COLS] = {KEYPAD_COL0, KEYPAD_COL1};
//    byte _rowPins[ROWS] = {KEYPAD_ROW0, 
//                      KEYPAD_ROW1,
//                      KEYPAD_ROW2,
//                      KEYPAD_ROW3,
//                      KEYPAD_ROW4,
//                      KEYPAD_ROW5,
//                      KEYPAD_ROW6,
//                      KEYPAD_ROW7,
//                      KEYPAD_ROW8,
//                      KEYPAD_ROW9};
//    char _keys[ROWS][COLS] = {
//                    {'1','B'},
//                    {'2','C'},
//                    {'3','D'},
//                    {'4','E'},
//                    {'5','F'},
//                    {'6','G'},
//                    {'7','H'},
//                    {'8','I'},
//                    {'9','J'},
//                    {'A','K'}
//                  };
//     //Keypad _keypad = Keypad( makeKeymap(_keys), _rowPins, _colPins, ROWS, COLS );
//}
//
//char Buttons::getKey() {
//  return _keypad.getKey();
//}
