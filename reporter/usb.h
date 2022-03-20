#pragma once
#include <stdint.h>

class MPU;
class Keymap;
class Display;
class KeyboardAction;

class USBReporter {
 public:
  void setup(MPU*, Keymap*, Display*);
  void registerAction(const KeyboardAction &a, uint32_t now);
  void completed();
};
