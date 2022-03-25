#pragma once
#include <stdint.h>

#include "../scancode.h"
#include "remote_matrix.h"

class Split34 : public RemoteMatrix {
 public:
  void setup(MPU*) override;
  uint8_t rows() override;
  uint8_t cols() override;
  scancode_t translateWireToScancode(uint8_t val, uint8_t which = 0) override;
  uint8_t getPin(PinInfo request) override;
};
