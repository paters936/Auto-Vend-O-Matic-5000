int clock = A8; //clock - black
int data = A11; //data - blue
int latch = A9; //latch - yellow
int enable = A10; //enable - green
int purple = A12; //enable - purple



void setup() {
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(purple, OUTPUT);
 
  
  Serial.begin(9600);
  
  //Reset the data lines
  digitalWrite(purple, true);
  digitalWrite(latch, true);
  digitalWrite(clock, true);
  digitalWrite(data, true);
  digitalWrite(enable, true);
  
  delay(3000);
}



void loop() {
  
  for (uint16_t i = 30; i <= 34; i++) {
    dispenseItem(i);
    delay(3000);
  }
}

void dispenseItem(int row) {
    //activate the enable line ready for the data
    digitalWrite(enable, false);
    
    //Send the data we are interested in
    sendDataPacket(row);
    
    //Delay enough for the motor to start activating
    delay(1500);
    
    //Shut off the motor - it will carry on automatically
    sendDataPacket(-1);
    
    
    // ---  The rest might not be needed --- //
    
    //digitalWrite(data, false);
    
    //delay(2500);
    
    //digitalWrite(data, true);
    //digitalWrite(enable, true);
    //sendDataPacket(-1);

    //delay(1000);
}

void sendDataPacket(int row) {
  
  //start position for data lines - prob not needed
  digitalWrite(latch, true);
  digitalWrite(clock, true);
  digitalWrite(data, true);

  //Each data packet is 40 bits long
  for (uint16_t i = 0; i <= 40; i++) {
       
    //When we reach the bit we are interested in set it low (active) for the clock pulse
    if (row == i) {
      digitalWrite(data, false);
    } else {
      digitalWrite(data, true);
    }

    //might not be needed
    delay(1);
         
    //clock - this is the inportant one - data is latched on the falling edge
    digitalWrite(clock, false);

    //1.5ms gap needed - might not be needed
    delay(1);
          
    //clock
    digitalWrite(clock, true);
          
    //data back to normal
    digitalWrite(data, true);
              
  }
  
  //Once everything has been written latch the data into place
  digitalWrite(latch, false);
  delay(1);
  digitalWrite(latch, true);
     
}
