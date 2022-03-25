#include <vector>

#include "keymaps/keymap.h"
#include "scancode.h"
#include "scanner/scanner.h"

std::vector<const KeymapAction*> Keymap::mapToActions(Scanner* scanner,
                                                      uint32_t now) {
  std::vector<const KeymapAction*> actions;
  while (scanner->pendingScanCodes(now)) {
    scancode_t code = scanner->getNext();
    const KeymapAction* ka = this->getActionForScancode(code);
    actions.push_back(ka);
  }
  return actions;
}