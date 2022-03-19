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
  Error
};

enum class Modifier : uint8_t {
  None = 0,
  Shift = 1,
  Ctrl = 2,
  Alt = 4,
  Option = 4,
  GUI = 8,
  Command = 8
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
};