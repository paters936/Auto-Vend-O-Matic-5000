

int pin3 = 38; //£1
int pin4 = 42; //£2
int pin5 = 36; //input - coin return
int pin6 = 44; //high - stops money
int pin7 = 34; //5p
int pin8 = 46; //10p
int pin9 = 32; //20p
int pin10 = 48;//50p

void setup() {
  pinMode(pin3, INPUT_PULLUP);
  pinMode(pin4, INPUT_PULLUP);
  pinMode(pin5, INPUT_PULLUP);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, INPUT_PULLUP);
  pinMode(pin8, INPUT_PULLUP);
  pinMode(pin9, INPUT_PULLUP);
  pinMode(pin10, INPUT_PULLUP);
  
  Serial.begin(9600);
}


void loop() {
  
  //digitalWrite(pin6, true);

  if (!digitalRead(pin3)) {
    Serial.println("£1");
  }
  if (!digitalRead(pin4)) {
    Serial.println("£2");
  }
  if (!digitalRead(pin5)) {
    Serial.println("Reset");
  }
  if (digitalRead(pin6)) {
    //Serial.println("PIN6");
  }
  if (!digitalRead(pin7)) {
    Serial.println("5p");
  }
  if (!digitalRead(pin8)) {
    Serial.println("10p");
  }
  if (!digitalRead(pin9)) {
    Serial.println("20p");
  }
  if (!digitalRead(pin10)) {
    Serial.println("50p");
  }
}
