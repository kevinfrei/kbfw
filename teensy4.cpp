#include "Arduino.h"
#include <stdint.h>

#include "mpu/teensy4.h"

void Teensy4::setup() {
  // Do I need to do anything "generally" to setup the Teensy?
}

void Teensy4::configOutputPin(uint8_t pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
}
void Teensy4::configInputPin(uint8_t pin) {
  pinMode(pin, INPUT_PULLUP);
}
void Teensy4::prepPinForRead(uint8_t pin) {
  digitalWrite(pin, LOW);
  // TODO: Do I need a delayMicroseconds in here?
}
void Teensy4::completePin(uint8_t pin) {
  digitalWrite(pin, HIGH);
}

HardwareSerial* Teensy4::getSerialPort(uint8_t which) {
  switch (which) {
    case 1:
      return &Serial1;
    case 2:
      return &Serial2;
    case 3:
      return &Serial3;
    case 4:
      return &Serial4;
    default:
      return nullptr;
  }
}
