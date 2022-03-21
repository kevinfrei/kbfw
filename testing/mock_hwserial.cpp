#include "HardwareSerial.h"

bool HardwareSerial::available() {
  return !this->stream.empty();
}

uint8_t HardwareSerial::read() {
  uint8_t res = this->stream.front();
  this->stream.pop_front();
  return res;
}

void HardwareSerial::write(uint8_t val) {
  this->stream.push_back(val);
}
