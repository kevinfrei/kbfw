#pragma once
#include <array>
#include <initializer_list>
#include <vector>

#include "scancode.h"
#include "keymaps/keymap.h"

class Matrix;
class KeyboardAction;
class Scanner;

class MockKeymap : public Keymap {
  std::array<std::array<KeyboardAction, 5>, 3> layers;

 protected:
  const KeyboardAction* getActionForScancode(scancode_t) override;

 public:
  void setup(Matrix*) override;
};