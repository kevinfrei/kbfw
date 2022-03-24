#include <vector>

#include "keymaps/keymap.h"
#include "scancode.h"
#include "scanner/scanner.h"

std::vector<const KeyboardAction*> Keymap::mapToActions(Scanner* scanner, uint32_t now) {
  std::vector<const KeyboardAction*> actions;
  while (scanner->pendingScanCodes(now)) {
    scancode_t code = scanner->getNext();
    const KeyboardAction* ka = this->getActionForScancode(code);
    actions.push_back(ka);
  }
  return actions;
}