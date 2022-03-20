#pragma once
#include <stdint.h>

enum class ValueMode { Dec, Hex, Bin };

class DebugLog {
 protected:
  ValueMode mode;

 public:
  DebugLog() : mode(ValueMode::Dec) {}
  virtual void setup() = 0;
  virtual void logln(const char* str = 0) = 0;
  virtual void log(const char*) = 0;
  virtual void log(uint32_t) = 0;
  void setMode(ValueMode m) {
    mode = m;
  }
};

extern DebugLog* dbg;