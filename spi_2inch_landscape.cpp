#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_ST77XX.h>
#include <stdint.h>


#include "displays/spi_2inch_landscape.h"
#include "matrix/matrix.h"
#include "mpu/mpu.h"
#include "scanner/scanner.h"

void SPI2InchLandscape::setup(MPU* mpu, Matrix* mat, Scanner* scn) {
  this->tft = new Adafruit_ST7789(mat->getPin(PinInfo::TFT_CS),
                                  mat->getPin(PinInfo::TFT_DC),
                                  mat->getPin(PinInfo::TFT_RESET));
}

void SPI2InchLandscape::tick(uint32_t now) {
  //
}