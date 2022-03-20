#pragma once

#include <initializer_list>
#include <stdint.h>
#include <tuple>

enum class ActionType : uint8_t {
  Key,
  Modifier,
  ConsumerKey,
  LayerShift,
  LayerPush,
  LayerPop,
  LayerRotate,
  ComboKey,
  TapOrHold,
  Skip,
  Error
};

enum class Modifier : uint8_t {
  None = 0,
  Shf = 1,
  LShf = 1,
  RShf = 2,
  Ctl = 4,
  LCtl = 4,
  RCtl = 8,
  Alt = 16,
  Opt = 16,
  LAlt = 16,
  LOpt = 16,
  RAlt = 32,
  ROpt = 32,
  GUI = 64,
  Cmd = 64,
  LGUI = 64,
  LCmd = 64,
  RGUI = 128,
  RCmd = 128
};

inline Modifier operator|(Modifier a, Modifier b) {
  typedef std::underlying_type<Modifier>::type etype;
  return static_cast<Modifier>(static_cast<etype>(a) | static_cast<etype>(b));
}

inline bool has(Modifier mods, Modifier flag) {
  typedef std::underlying_type<Modifier>::type etype;
  return (static_cast<etype>(mods) & static_cast<etype>(flag)) != 0;
}

class KeyboardAction {
  ActionType action;
  Modifier mods;
  uint32_t code;
  KeyboardAction* tap;

 public:
  // 'transparent'
  KeyboardAction();
  // Key
  KeyboardAction(uint32_t keyCode);
  // Modifier
  KeyboardAction(Modifier mod);
  // Layer "things"
  KeyboardAction(ActionType layer, uint8_t val = 0xFF);
  // Layer Rotation
  KeyboardAction(std::initializer_list<uint8_t> rotate);
  // Combo key: Key plus a set of modifiers
  KeyboardAction(uint32_t keyCode, std::initializer_list<Modifier> mods);
  // TapOrHold
  KeyboardAction(Modifier hold, KeyboardAction* tap);
  ActionType getAction() const {
    return action;
  }
  Modifier getModifier() const {
    return mods;
  }
  uint32_t getCode() const {
    return code;
  }
  KeyboardAction* getTap() const {
    return tap;
  }
};