/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>

const byte ROWS = 10; //four rows
const byte COLS = 2; //three columns
char keys[ROWS][COLS] = {
  {'1','B'},
  {'2','C'},
  {'3','D'},
  {'4','E'},
  {'5','F'},
  {'6','G'},
  {'7','H'},
  {'8','I'},
  {'9','J'},
  {'A','K'}
};
byte rowPins[ROWS] = {49, 47, 45, 43, 41, 39, 37, 35, 33, 31}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {53, 51}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
  }
}
