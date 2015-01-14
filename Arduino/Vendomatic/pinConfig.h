#include "Arduino.h"

void setDispenserPins() {
  pinMode(DISPENSER_CLOCK, OUTPUT);
  pinMode(DISPENSER_DATA, OUTPUT);
  pinMode(DISPENSER_LATCH, OUTPUT);
  pinMode(DISPENSER_ENABLE, OUTPUT);
  pinMode(DISPENSER_PURPLE, OUTPUT);
}
