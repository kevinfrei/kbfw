#pragma once

#include <array>
#include <vector>

#include "../kb_actions.h"
#include "keymap.h"

class Matrix;
class Scanner;

class Freik68 : public Keymap {
  std::vector<std::array<const KeyboardAction, 68>> layers;

 public:
  Freik68(std::initializer_list<std::initializer_list<const KeyboardAction>>
            init_list);
  void setup(Matrix*) override;
  std::vector<const KeyboardAction*> mapToActions(Scanner*) override;
};