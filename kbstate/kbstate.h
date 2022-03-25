#pragma once
#include <stdint.h>

class MPU;
class Keymap;
class Display;
class KeymapAction;

// This was helpful reading:
// https://www.devever.net/~hl/usbnkro

class KBState {
 protected:
  MPU* mpu;
  Keymap* keymap;
  Display* display;
  uint8_t activeLayer;

 public:
  virtual void setup(MPU*, Keymap*, Display*);
  virtual void registerAction(const KeymapAction* a, uint32_t now);
  virtual void completeActions();
};
