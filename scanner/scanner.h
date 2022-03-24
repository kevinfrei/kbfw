#pragma once
#include <deque>
#include <stdint.h>

#include "../scancode.h"

class MPU;
class Matrix;

class Scanner {
 protected:
  std::deque<scancode_t> codes;

 public:
  virtual void setup(MPU* mpu, Matrix* m) = 0;
  virtual bool pendingScanCodes(uint32_t now) = 0;
  scancode_t getNext() {
    if (codes.empty()) {
      return scancode_t::error;
    }
    scancode_t code = codes.front();
    codes.pop_front();
    return code;
  };

  void clearScanCodes() {
    codes.clear();
  }
};
