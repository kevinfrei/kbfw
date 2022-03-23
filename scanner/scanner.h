#pragma once
#include <deque>
#include <stdint.h>

class MPU;
class Matrix;

class Scanner {
 protected:
  std::deque<uint8_t> codes;

 public:
  virtual void setup(MPU* mpu, Matrix* m) = 0;
  virtual bool pendingScanCodes(uint32_t now) = 0;
  uint8_t getNext() {
    if (codes.empty()) {
      return 0xff;
    }
    uint8_t code = codes.front();
    codes.pop_front();
    return code;
  };

  void clearScanCodes() {
    codes.clear();
  }
};
