#pragma once
#include <stdint.h>

class MPU;
class Keymap;
class Display;
class KeyboardAction;

class USBReporter {
 public:
  void setup(MPU*, Keymap*, Display*);
  void handleActions(const KeyboardAction &a, uint32_t now);
};
