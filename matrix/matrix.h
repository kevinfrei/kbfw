#pragma once

#include <stdint.h>

class MPU;

enum class PinInfo {
  TFT_CS,
  TFT_DC,
  TFT_RESET,
  TFT_BACKLIGHT,
  SPEAKER_GND,
  SPEAKER_SIGNAL
};

class Matrix {
 public:
  virtual void setup(MPU*) = 0;
  virtual uint8_t rows() = 0;
  virtual uint8_t cols() = 0;
  virtual uint8_t getPin(PinInfo request) = 0;
};
