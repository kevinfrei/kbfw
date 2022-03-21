#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_ST77XX.h>
#include <SPI.h>
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
  this->tft->init(240, 320);
  this->tft->setSPISpeed(60000000);
  this->backlight = mat->getPin(PinInfo::TFT_BACKLIGHT);
  pinMode(this->backlight, OUTPUT);
  this->tft->setRotation(1);
  this->tft->fillScreen(ST77XX_BLACK);
}

void SPI2InchLandscape::tick(uint32_t now) {
  if (now - this->lastUpdate > 500) {
    // this->lightOn = (this->lightOn + 1) & 0x7;
    // dbg->log("Flipping backlight (");
    // dbg->log(this->backlight);
    // dbg->logln(this->lightOn ? ") to low" : ") to high");
    // digitalWrite(this->backlight, this->lightOn ? LOW : HIGH);
    // Just turn the backlight off for now
    digitalWrite(this->backlight, LOW);
    this->lastUpdate = now;
  }
}

void SPI2InchLandscape::init() {
  // Don't try to nest this. Anything we're replacing should already be initialized!
}
void SPI2InchLandscape::logln(const char* str) {
  // TODO: Print on the screen, then nest it
}
void SPI2InchLandscape::log(const char* str) {
  // TODO: Print on the screen, then nest it
}
void SPI2InchLandscape::log(uint32_t num) {
  // TODO: Print on the screen, then nest it
}