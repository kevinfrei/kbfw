#include <array>
#include <initializer_list>
#include <stdint.h>
#include <vector>

#include "kb_actions.h"
#include "keymaps/freik68.h"
#include "scanner/scanner.h"

Freik68::Freik68(
  std::initializer_list<std::initializer_list<const KeymapAction>> lst)
  : layers() {
  for (auto& layer : lst) {
    std::array<KeymapAction, 68> actions{};
    uint32_t cur = 0;
    for (auto& action : layer) {
      actions[cur++] = action;
    }
  }
}

void Freik68::setup(Matrix* mat) {
  //
}

const KeymapAction* Freik68::getActionForScancode(scancode_t sc) {
  // TODO: Fix this
  return nullptr;
}