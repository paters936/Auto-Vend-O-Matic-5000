/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/

#include <Keypad.h>

const byte ROWS = 2; //2 rows
const byte COLS = 10; //10 columns
//define the cymbols on the buttons of the keypads
char keyMap[ROWS][COLS] = {
  {'1','2','3', '4', '5', '6', '7', '8', '9', '10'},
  {'11', '12', '13', '14', '15', '16', '17','18','19','20'},
};
byte rowPins[COLS] = {31, 33, 35, 37, 39, 41, 43, 45, 47, 49 }; //connect to the row pinouts of the keypad
byte colPins[ROWS] = {51, 53}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(115200);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}
