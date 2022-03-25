#pragma once
#include <initializer_list>
#include <stdint.h>
#include <vector>

#include "../scancode.h"

class Matrix;
class Scanner;
class KeymapAction;

class Keymap {
 protected:
  virtual const KeymapAction* getActionForScancode(scancode_t sc) = 0;

 public:
  virtual void setup(Matrix*) = 0;
  virtual std::vector<const KeymapAction*> mapToActions(Scanner*, uint32_t);
};