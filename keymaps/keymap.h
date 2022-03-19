#pragma once
#include <initializer_list>
#include <stdint.h>
#include <vector>

class Matrix;
class Scanner;
class KeyboardAction;

class Keymap {
 public:
  virtual void setup(Matrix*) = 0;
  virtual std::vector<const KeyboardAction*> mapToActions(Scanner*) = 0;
};