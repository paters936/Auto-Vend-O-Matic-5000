
#include <EEPROM.h>
//#include <Arduino.h>  // for type definitions
#include "constants.h"
#include "EEPROMAnything.h"


void initEeprom() { 
  int eepromAddress = EEPROM_CREDIT_START_ADDRESS;
  if( EEPROM.read(eepromAddress++)==eepromValidateData ) {

    eepromAddress+=EEPROM_readAnything(eepromAddress, credit);
    eepromAddress+=EEPROM_readAnything(eepromAddress, totalCredit);
    eepromAddress+=EEPROM_readAnything(eepromAddress, creditSinceCashout);

  } 
  else { 
    credit = 0; 
    totalCredit = 0; 
    creditSinceCashout = 0; 
    writeCreditToEeprom(); 
  }

}


void writeCreditToEeprom() { 
  
  int eepromAddress = EEPROM_CREDIT_START_ADDRESS;
  EEPROM.write(eepromAddress++, eepromValidateData);
  eepromAddress+=EEPROM_writeAnything(eepromAddress, credit);
  eepromAddress+=EEPROM_writeAnything(eepromAddress, totalCredit);
  eepromAddress+=EEPROM_writeAnything(eepromAddress, creditSinceCashout);   
}



/*

 
 
 //This function will write a 4 byte (32bit) long to the eeprom at
 //the specified address to adress + 3.
 void EEPROMWritelong(int address, long value) {
 //Decomposition from a long to 4 bytes by using bitshift.
 //One = Most significant -> Four = Least significant byte
 byte four = (value & 0xFF);
 byte three = ((value >> 8) & 0xFF);
 byte two = ((value >> 16) & 0xFF);
 byte one = ((value >> 24) & 0xFF);
 
 //Write the 4 bytes into the eeprom memory.
 EEPROM.write(address, four);
 EEPROM.write(address + 1, three);
 EEPROM.write(address + 2, two);
 EEPROM.write(address + 3, one);
 }
 
 
 long EEPROMReadlong(long address) {
 //Read the 4 bytes from the eeprom memory.
 long four = EEPROM.read(address);
 long three = EEPROM.read(address + 1);
 long two = EEPROM.read(address + 2);
 long one = EEPROM.read(address + 3);
 
 //Return the recomposed long by using bitshift.
 return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
 }
 */

