#pragma once
#include <stdint.h>

#include "display.h"

class Adafruit_ST7789;

class SPI2InchLandscape : public Display {
  Adafruit_ST7789* tft;

 public:
  void setup(MPU*, Matrix*, Scanner*) override;
  void tick(uint32_t) override;
};
