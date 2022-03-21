#include "Arduino.h"
#include <stdint.h>

#include "dbg/debuglog.h"
#include "dbg/seriallog.h"

void SerialLog::init() {
  Serial.begin(115200);
};
void SerialLog::log(const char* str) {
  Serial.print(str);
};
void SerialLog::logln(const char* str) {
  if (str != nullptr) {
    Serial.println(str);
  } else {
    Serial.println();
  }
};
void SerialLog::log(uint32_t val) {
  switch (this->mode) {
    case ValueMode::Hex:
      Serial.print(val, HEX);
      break;
    case ValueMode::Dec:
      Serial.print(val, DEC);
      break;
    case ValueMode::Bin:
      Serial.print(val, BIN);
      break;
    default:
      break;
  }
};
