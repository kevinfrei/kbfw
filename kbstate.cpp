#include <stdint.h>

#include "dbg/debuglog.h"
#include "kb_actions.h"
#include "kbstate/kbstate.h"

void KBState::setup(MPU* m, Keymap* map, Display* disp) {
  // Save stuff I might need, yeah?
  this->activeLayer = 0;
  this->mpu = m;
  this->keymap = map;
  this->display = disp;
}

void KBState::registerAction(const KeymapAction* a, uint32_t now) {
  // handle 'early' stuff, and collect keypresses to handle once completed
  switch (a->getAction()) {
    case ActionType::Key:
      break;
    default:
      dbg->log("Unhandled Action Type: ");
      dbg->logln(getName(a->getAction()));
  }
}

void KBState::completeActions() {
  // Send the collected set of key presses/releases on to the controller
}