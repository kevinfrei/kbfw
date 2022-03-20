#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_ST77XX.h>
#include <stdint.h>

#include "dbg/debuglog.h"
#include "displays/spi_2inch_landscape.h"
#include "matrix/matrix.h"
#include "mpu/mpu.h"
#include "scanner/scanner.h"

void SPI2InchLandscape::setup(MPU* mpu, Matrix* mat, Scanner* scn) {
  this->tft = new Adafruit_ST7789(mat->getPin(PinInfo::TFT_CS),
                                  mat->getPin(PinInfo::TFT_DC),
                                  mat->getPin(PinInfo::TFT_RESET));
  this->backlight = mat->getPin(PinInfo::TFT_BACKLIGHT);
  pinMode(this->backlight, OUTPUT);
}

void SPI2InchLandscape::tick(uint32_t now) {
  if (now - this->lastUpdate > 500) {
    this->lightOn = !this->lightOn;
    dbg->log("Flipping backlight (");
    dbg->log(this->backlight);
    dbg->logln(this->lightOn ? ") to high" : ") to low");
    digitalWrite(this->backlight, this->lightOn ? HIGH : LOW);
    this->lastUpdate = now;
  }
}