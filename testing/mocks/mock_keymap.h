#pragma once
#include <array>
#include <initializer_list>
#include <vector>

#include "keymaps/keymap.h"
#include "scancode.h"

class Matrix;
class KeymapAction;
class Scanner;

class MockKeymap : public Keymap {
  std::array<std::array<KeymapAction, 5>, 3> layers;

 protected:
  const KeymapAction* getActionForScancode(scancode_t) override;

 public:
  void setup(Matrix*) override;
};