#include <array>
#include <initializer_list>
#include <stdint.h>
#include <vector>

#include "kb_actions.h"
#include "keymaps/freik68.h"
#include "scanner/scanner.h"

Freik68::Freik68(
  std::initializer_list<std::initializer_list<const KeyboardAction>> lst)
  : layers() {
  for (auto& layer : lst) {
    std::array<KeyboardAction, 68> actions{};
    uint32_t cur = 0;
    for (auto& action : layer) {
      actions[cur++] = action;
    }
  }
}

void Freik68::setup(Matrix* mat) {
  //
}

std::vector<const KeyboardAction*> Freik68::mapToActions(Scanner* scanner) {
  std::vector<const KeyboardAction*> actions;
  // TODO: Fill in the actions
  return actions;
}