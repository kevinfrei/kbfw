#pragma once

#include "HardwareSerial.h"
#include <stdint.h>

class MPU {
 public:
  virtual void setup() = 0;
  virtual void configOutputPin(uint8_t pin) = 0;
  virtual void configInputPin(uint8_t pin) = 0;
  virtual void prepPinForRead(uint8_t pin) = 0;
  virtual void completePin(uint8_t pin) = 0;
  virtual HardwareSerial* getSerialPort(uint8_t) = 0;
};
