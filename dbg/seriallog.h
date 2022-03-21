#pragma once

#include "debuglog.h"

class SerialLog : public DebugLog {
 public:
  SerialLog() : DebugLog() {}
  void init() override;
  void logln(const char* str = 0) override;
  void log(const char*) override;
  void log(uint32_t) override;
};