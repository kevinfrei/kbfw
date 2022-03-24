#pragma once
#include <stdint.h>

#include "matrix.h"
#include "../scancode.h"

class RemoteMatrix : public Matrix {
 public:
  virtual scancode_t translateWireToScancode(uint8_t val,
                                             uint8_t which = 0) = 0;
};