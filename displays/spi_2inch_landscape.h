#pragma once
#include <stdint.h>

#include "display.h"

class Adafruit_ST7789;

class SPI2InchLandscape : public Display {
  Adafruit_ST7789* tft;
  uint8_t backlight;
  // Display state:
  uint32_t lastUpdate;
  bool lightOn;

 public:
  SPI2InchLandscape()
    : tft(nullptr), backlight(0xff), lastUpdate(0), lightOn(true) {}
  void setup(MPU*, Matrix*, Scanner*) override;
  void tick(uint32_t) override;
};
