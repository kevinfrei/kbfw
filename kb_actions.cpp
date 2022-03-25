#include <initializer_list>
#include <stdint.h>
#include <tuple>

#include "kb_actions.h"

// Transparent slot
KeymapAction::KeymapAction()
  : action(ActionType::Skip), mods(Modifier::None), code(0), tap(nullptr) {}

// Key
KeymapAction::KeymapAction(uint32_t keyCode)
  : action(ActionType::Key), mods(Modifier::None), code(keyCode), tap(nullptr) {
  // TODO: check for a consumer key
}

// Modifier
KeymapAction::KeymapAction(Modifier mod)
  : action(ActionType::Modifier), mods(mod), code(0), tap(nullptr) {}

// Layer "things"
KeymapAction::KeymapAction(ActionType layerAction, uint8_t val)
  : action(layerAction), mods(Modifier::None), code(val), tap(nullptr) {
  if ((val == 0xFF) != (layerAction == ActionType::LayerPop) &&
      (layerAction != ActionType::LayerPop &&
       layerAction != ActionType::LayerPush &&
       layerAction != ActionType::LayerShift)) {
    this->action = ActionType::Error;
  }
}

// Layer Rotation
KeymapAction::KeymapAction(std::initializer_list<uint8_t> rotate)
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
KeymapAction::KeymapAction(uint32_t keyCode, std::initializer_list<Modifier> ms)
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
KeymapAction::KeymapAction(Modifier hold, KeymapAction* tap)
  : action(ActionType::TapOrHold), mods(hold), code(0), tap(tap) {}
