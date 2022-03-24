#pragma once
#include <stdint.h>

enum class scancode_t : uint8_t {
  firstPress = 0,
  lastPress = 0x7e,
  invalid = 0x7f,
  firstRelease = 0x80,
  lastRelease = 0xfe,
  error = 0xff
};

inline uint8_t codeToVal(scancode_t v) {
  return static_cast<uint8_t>(v);
}

inline scancode_t valToCode(uint8_t v) {
  return static_cast<scancode_t>(v);
}

inline bool isPressed(scancode_t v) {
  return (codeToVal(v) & 0x80) == 0 && v != scancode_t::invalid;
}

inline bool isReleased(scancode_t v) {
  return (codeToVal(v) & 0x80) == 0x80 && v != scancode_t::error;
}

inline scancode_t press(scancode_t v) {
  return valToCode(codeToVal(v) & 0x7f);
}

inline scancode_t release(scancode_t v) {
  return valToCode(codeToVal(v) | 0x80);
}

inline bool isValid(scancode_t v) {
  return v != scancode_t::error && v != scancode_t::invalid;
}
