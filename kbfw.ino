#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_ST77xx.h>
#include <SPI.h>

#include <stdint.h>
#include <vector>

// Change the include line of this file and you're good to go
#include "karbon.h"

void setup() {
  allocate();
  // Initialize debug output
  dbg->init();
  // The device
  dbg->logln("Setting up MPU");
  mpu->setup();
  // The "keypress acquisition" system:
  // either a switch matrix or a 'remote' matrix through some other means
  dbg->logln("Setting up Matrix");
  matrix->setup(mpu);
  // The thing that sucks in matrix/switch data and translates it to
  // scan codes (0-127, plus the hi-bit flag as a pressed/released)
  dbg->logln("Setting up Scanner");
  scanner->setup(mpu, matrix);
  // This is potentially a NOP, or an actual LCD, or maybe something else,
  // like a Serial debugger?
  dbg->logln("Setting up Display");
  display->setup(mpu, matrix, scanner);
  // This configures the display for debugging output also
  display->init();
  // This is the thing that's reporting the keypresses to the device
  // Currently, probably only USB or Bluetooth
  dbg->logln("Setting up Reporter");
  kbstate->setup(mpu, keymap, display);
  dbg->logln("Setup complete");
}

uint32_t lastTick = 0;

void loop() {
  uint32_t now = millis();
  // Check to see if there are any scan codes for us to process
  if (scanner->pendingScanCodes(now)) {
    dbg->logln("Found pending scan codes");
    // Collect all the action that should be triggered with what the
    // scanner sees
    std::vector<const KeymapAction*> actions =
      keymap->mapToActions(scanner, now);
    // Process each of the actions
    for (const KeymapAction* a : actions) {
      kbstate->registerAction(a, now);
    }
    // Now report the actions
    kbstate->completeActions();
    dbg->logln("Codes reported");
  }
  // We allow an update to the 'display' every millisecond
  if (lastTick != now) {
    display->tick(now);
  }
  lastTick = now;
}