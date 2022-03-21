#pragma once
#include <stdint.h>

#include "../dbg/debuglog.h"
#include "display.h"

class Adafruit_ST7789;

class SPI2InchLandscape : public Display, public DebugLog {
  Adafruit_ST7789* tft;
  uint8_t backlight;
  // Display state:
  uint8_t lightOn;
  uint32_t lastUpdate;
  // Former DebugLog thing to nest out to
  DebugLog* dbgFormer;

 public:
  SPI2InchLandscape()
    : tft(nullptr),
      backlight(0xff),
      lightOn(0),
      lastUpdate(0),
      dbgFormer(nullptr) {}
  void setup(MPU*, Matrix*, Scanner*) override;
  void tick(uint32_t) override;

  // DebugLog interface
  void init() override;
  void logln(const char* str = 0) override;
  void log(const char*) override;
  void log(uint32_t) override;
};
