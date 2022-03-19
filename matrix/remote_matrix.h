#pragma once
#include <stdint.h>

#include "matrix.h"

class RemoteMatrix : public Matrix {
 public:
  virtual uint8_t translateWireToScancode(uint8_t val, uint8_t which = 0) = 0;
};