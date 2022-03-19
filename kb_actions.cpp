#include <initializer_list>
#include <stdint.h>
#include <tuple>

#include "kb_actions.h"

// Key
KeyboardAction::KeyboardAction(uint32_t keyCode)
  : action(ActionType::Key), mods(Modifier::None), code(keyCode), tap(nullptr) {
  // TODO: check for a consumer key
}

// Modifier
KeyboardAction::KeyboardAction(Modifier mod)
  : action(ActionType::Modifier), mods(mod), code(0), tap(nullptr) {}

// Layer "things"
KeyboardAction::KeyboardAction(ActionType layerAction, uint8_t val)
  : action(layerAction), mods(Modifier::None), code(val), tap(nullptr) {
  if ((val == 0xFF) != (layerAction == ActionType::LayerPop) &&
      (layerAction != ActionType::LayerPop &&
       layerAction != ActionType::LayerPush &&
       layerAction != ActionType::LayerShift)) {
    this->action = ActionType::Error;
  }
}

// Layer Rotation
KeyboardAction::KeyboardAction(std::initializer_list<uint8_t> rotate)
  : action(ActionType::LayerRotate),
    mods(Modifier::None),
    code(0),
    tap(nullptr) {
  uint8_t layerCount = 0;
  uint32_t layers = 0;
  for (uint8_t lyr : rotate) {
    layers = layers << 5 | (0x10 | lyr);
    layerCount++;
  }
  if (layerCount > 6) {
    this->action = ActionType::Error;
  }
  this->code = layers;
}

// Combo key: Key plus a set of modifiers
KeyboardAction::KeyboardAction(uint32_t keyCode,
                               std::initializer_list<Modifier> ms)
  : action(ActionType::ComboKey),
    mods(Modifier::None),
    code(keyCode),
    tap(nullptr) {
  Modifier mod = Modifier::None;
  for (Modifier m : ms) {
    mod = mod | m;
  }
  this->mods = mod;
}

// TapOrHold
KeyboardAction::KeyboardAction(Modifier hold, KeyboardAction* tap)
  : action(ActionType::TapOrHold), mods(hold), code(0), tap(tap) {}
