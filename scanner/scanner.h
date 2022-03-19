#pragma once
#include <stdint.h>
#include <vector>

class MPU;
class Matrix;

class Scanner {
 protected:
  std::vector<uint8_t> codes;

 public:
  virtual void setup(MPU* mpu, Matrix* m) = 0;
  virtual bool pendingScanCodes(uint32_t now) = 0;
  virtual void clearScanCodes() {
    codes.clear();
  }
};
