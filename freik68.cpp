#include <initializer_list>
#include <stdint.h>
#include <vector>

#include "kb_actions.h"
#include "keymaps/freik68.h"
#include "scanner/scanner.h"

Freik68::Freik68(std::initializer_list<std::initializer_list<KeyboardAction>> lst) {}

void Freik68::setup(Matrix* mat) {}

std::vector<const KeyboardAction*> Freik68::mapToActions(Scanner* scanner) {
  std::vector<const KeyboardAction*> actions;
  // TODO: Fill in the actions
  return actions;
}