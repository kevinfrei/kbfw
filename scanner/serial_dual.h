#pragma once

#include <stdint.h>

#include "scanner.h"

// This is for "have a pair of halves, each on different serial ports"
// Means, no "scan the keyboard matrix" but rather "Read data from the serial
// ports"

class RemoteMatrix;
class MPU;

class DualSerialScanner : public Scanner {
  MPU* mpu;
  RemoteMatrix* matrix;

 public:
  void setup(MPU* mp, Matrix* mat) override;
  bool pendingScanCodes(uint32_t now) override;
};
