#include <stdint.h>

#include "matrix/matrix.h"
#include "matrix/split_34.h"

void Split34::setup(MPU* mpu) {}

uint8_t Split34::rows() {
  return 6;
}

uint8_t Split34::cols() {
  return 6;
}

uint8_t Split34::translateWireToScancode(uint8_t val, uint8_t which) {
  which = ((which - 2) / 2);
  // First, get the 'local' scan code:
  val--;
  uint8_t code = val / 3;
  uint8_t chk = val % 3;
  if (code % 3 != chk) {
    return 0x80;
  }
  // Code is now between 0 & 71:
  //  0-35 are "pressed" codes
  //  36-71 are "released"
  // Scan codes are values between 0 and 0x7e
  //  with the high bit being 'pressed' or 'released'
  // Codes 0xff/0x7f are invalid

  // First, extract the pressed value
  bool pressed = code < 36;
  if (!pressed) {
    code -= 36;
  }
  // Now, adjust the scan code to be linearized between two halves, yeah?
  code = (code / cols()) * 2 * cols() + which * cols() + code % cols();
  return code | (pressed ? 0x80 : 0);
}

uint8_t Split34::getPin(PinInfo req) {
  switch (req) {
    case PinInfo::TFT_CS:
      return 10;
    case PinInfo::TFT_DC:
      return 20;
    case PinInfo::TFT_RESET:
      return 21;
    case PinInfo::TFT_BACKLIGHT:
      return 18;
    case PinInfo::SPEAKER_GND:
      return 0;
    case PinInfo::SPEAKER_SIGNAL:
      return 4;
  }
  return 0xff;
}