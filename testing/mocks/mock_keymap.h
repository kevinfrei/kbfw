#pragma once
#include <array>
#include <initializer_list>
#include <vector>

#include "keymaps/keymap.h"

class Matrix;
class KeyboardAction;
class Scanner;

class MockKeymap : public Keymap {
  std::array<std::array<KeyboardAction, 5>, 3> layers;

 public:
  void setup(Matrix*) override;
  std::vector<const KeyboardAction*> mapToActions(Scanner*) override;
};