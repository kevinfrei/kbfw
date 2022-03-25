#pragma once

#include <array>
#include <initializer_list>
#include <vector>

#include "../kb_actions.h"
#include "../scancode.h"
#include "keymap.h"

class Matrix;
class Scanner;

class Freik68 : public Keymap {
  std::vector<std::array<const KeymapAction, 68>> layers;

 protected:
  const KeymapAction* getActionForScancode(scancode_t) override;

 public:
  Freik68(std::initializer_list<std::initializer_list<const KeymapAction>>
            init_list);
  void setup(Matrix*) override;
};