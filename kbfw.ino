#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_ST77xx.h>

// Change the include line of this file and you're good to go
#include <stdint.h>
#include <vector>

#include "karbon.h"

void setup() {
  allocate();
  mpu->setup();
  matrix->setup(mpu);
  scanner->setup(mpu, matrix);
  // keymap.setup(matrix);
  display->setup(mpu, matrix, scanner);
  reporter->setup(mpu, keymap, display);
}

uint32_t lastTick = 0;

void loop() {
  uint32_t now = millis();
  if (scanner->pendingScanCodes(now)) {
    std::vector<const KeyboardAction*> actions = keymap->mapToActions(scanner);
    for (const KeyboardAction* a : actions) {
      reporter->handleActions(*a, now);
    }
  }
  if (lastTick != now) {
    display->tick(now);
  }
  lastTick = now;
}