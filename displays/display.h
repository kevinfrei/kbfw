#pragma once
#include <stdint.h>

class MPU;
class Matrix;
class Scanner;

class Display {
 public:
  virtual void setup(MPU*, Matrix*, Scanner*) = 0;
  virtual void tick(uint32_t now) = 0;
};