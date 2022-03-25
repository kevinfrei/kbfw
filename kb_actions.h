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

inline const char* getName(ActionType a) {
  switch (a) {
    case ActionType::Key:
      return "Key";
    case ActionType::Modifier:
      return "Modifier";
    case ActionType::ConsumerKey:
      return "Consumer Key";
    case ActionType::LayerShift:
      return "Layer Shift";
    case ActionType::LayerPush:
      return "Layer Push";
    case ActionType::LayerPop:
      return "Layer Pop";
    case ActionType::LayerRotate:
      return "Layer Rotate";
    case ActionType::ComboKey:
      return "Combo Key";
    case ActionType::TapOrHold:
      return "TapOrHold";
    case ActionType::Skip:
      return "Skip";
    case ActionType::Error:
      return "Error";
  }
}

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

class KeymapAction {
  ActionType action;
  Modifier mods;
  uint32_t code;
  KeymapAction* tap;

 public:
  // 'transparent'
  KeymapAction();
  // Key
  KeymapAction(uint32_t keyCode);
  // Modifier
  KeymapAction(Modifier mod);
  // Layer "things"
  KeymapAction(ActionType layer, uint8_t val = 0xFF);
  // Layer Rotation
  KeymapAction(std::initializer_list<uint8_t> rotate);
  // Combo key: Key plus a set of modifiers
  KeymapAction(uint32_t keyCode, std::initializer_list<Modifier> mods);
  // TapOrHold
  KeymapAction(Modifier hold, KeymapAction* tap);
  ActionType getAction() const {
    return action;
  }
  Modifier getModifier() const {
    return mods;
  }
  uint32_t getCode() const {
    return code;
  }
  KeymapAction* getTap() const {
    return tap;
  }
};

class KeyboardResult {
 protected:
  bool press;

 public:
  KeyboardResult(bool isPressed) : press(isPressed) {}
};

class Keypress : public KeyboardResult {
 protected:
  char key;

 public:
  Keypress(bool isPressed, char k) : KeyboardResult(isPressed), key(k) {}
};

class Modifiers : public KeyboardResult {
 protected:
  uint8_t mods;

 public:
  Modifiers(bool isPress, uint8_t modifiers)
    : KeyboardResult(isPress), mods(modifiers) {}
};

class ConsumerKey : public KeyboardResult {
 protected:
  uint16_t consKey;

 public:
  ConsumerKey(bool isPress, uint16_t consumerKey)
    : KeyboardResult(isPress), consKey(consumerKey) {}
};