#include "karbon.h"

Teensy4* mpu;
Split34* matrix;
DualSerialScanner* scanner;
USBReporter* reporter;
SPI2InchLandscape* display;
Freik68* keymap;

void InitKarbon() {
  mpu = new Teensy4();
  matrix = new Split34();
  scanner = new DualSerialScanner();
  reporter = new USBReporter();
  display = new SPI2InchLandscape();
  keymap = new Freik68({} // TODO:    KeyboardAction(KC::Escape, KC::)
  );
}