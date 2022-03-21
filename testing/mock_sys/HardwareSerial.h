#pragma once
#include <deque>
#include <stdint.h>

class HardwareSerial {
  std::deque<uint8_t> stream;

 public:
  bool available();
  uint8_t read();
  void write(uint8_t);
};