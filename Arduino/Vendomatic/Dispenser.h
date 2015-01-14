#include "Arduino.h"
#include "pinDefinitions.h"

class Dispenser {
    public:
        void dispenseItem(int row);
        void setupPins();
    private:
        void sendDataPacket(int row);
};



void Dispenser::setupPins() {
  pinMode(DISPENSER_CLOCK, OUTPUT);
  pinMode(DISPENSER_DATA, OUTPUT);
  pinMode(DISPENSER_LATCH, OUTPUT);
  pinMode(DISPENSER_ENABLE, OUTPUT);
  pinMode(DISPENSER_PURPLE, OUTPUT);
}

void Dispenser::dispenseItem(int row) {
    //activate the enable line ready for the data
    digitalWrite(DISPENSER_ENABLE, false);
    
    //Send the data we are interested in
    sendDataPacket(row);
    
    //Delay enough for the motor to start activating
    delay(1500);
    
    //Shut off the motor - it will carry on automatically
    sendDataPacket(-1);
    
    
    // ---  The rest might not be needed --- //
    
    //digitalWrite(DISPENSER_DATA, false);
    
    //delay(2500);
    
    //digitalWrite(DISPENSER_DATA, true);
    //digitalWrite(DISPENSER_ENABLE, true);
    //sendDataPacket(-1);

    //delay(1000);
}


void Dispenser::sendDataPacket(int row) {
  
  //start position for data lines - prob not needed
  digitalWrite(DISPENSER_LATCH, true);
  digitalWrite(DISPENSER_CLOCK, true);
  digitalWrite(DISPENSER_DATA, true);

  //Each data packet is 40 bits long
  for (uint16_t i = 0; i <= 40; i++) {
       
    //When we reach the bit we are interested in set it low (active) for the clock pulse
    if (row == i) {
      digitalWrite(DISPENSER_DATA, false);
    } else {
      digitalWrite(DISPENSER_DATA, true);
    }

    //might not be needed
    delay(1);
         
    //clock - this is the inportant one - data is latched on the falling edge
    digitalWrite(DISPENSER_CLOCK, false);

    //1.5ms gap needed - might not be needed
    delay(1);
          
    //clock
    digitalWrite(DISPENSER_CLOCK, true);
          
    //data back to normal
    digitalWrite(DISPENSER_DATA, true);
              
  }
  
  //Once everything has been written latch the data into place
  digitalWrite(DISPENSER_LATCH, false);
  delay(1);
  digitalWrite(DISPENSER_LATCH, true);
     
}
