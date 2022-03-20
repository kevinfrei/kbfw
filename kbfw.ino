#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_ST77xx.h>

#include <stdint.h>
#include <vector>

// Change the include line of this file and you're good to go
#include "karbon.h"

void setup() {
  allocate();
  // The device
  mpu->setup();
  // The "keypress acquisition" system:
  // either a switch matrix or a 'remote' matrix through some other means
  matrix->setup(mpu);
  // The thing that sucks in matrix/switch data and translates it to
  // scan codes (0-127, plus the hi-bit flag as a pressed/released)
  scanner->setup(mpu, matrix);
  // This is potentially a NOP, or an actual LCD, or maybe something else, like
  // a Serial debugger?
  display->setup(mpu, matrix, scanner);
  // This is the thing that's reporting the keypresses to the device
  // Currently, probably only USB or Bluetooth
  reporter->setup(mpu, keymap, display);
}

uint32_t lastTick = 0;

void loop() {
  uint32_t now = millis();
  // Check to see if there are any scan codes for us to process
  if (scanner->pendingScanCodes(now)) {
    // Collect all the action that should be triggered with what the scanner
    // sees
    std::vector<const KeyboardAction*> actions = keymap->mapToActions(scanner);
    // Process each of the actions
    for (const KeyboardAction* a : actions) {
      reporter->registerAction(*a, now);
    }
    // Now report the actions
    reporter->completed();
  }
  // We allow an update to the 'display' every millisecond
  if (lastTick != now) {
    display->tick(now);
  }
  lastTick = now;
}