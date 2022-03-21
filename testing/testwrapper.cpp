#include <iostream>

#include "matrix/split_34.h"
#include "mocks/mock_mpu.h"

void testSerialMock(MPU* mpu) {
  for (uint8_t i = 3; i > 0; i--) {
    mpu->getSerialPort(i);
  }
  for (uint8_t i = 0; i < 5; i++) {
    mpu->getSerialPort(i);
  }
  HardwareSerial* s1 = mpu->getSerialPort(1);
  HardwareSerial* s0 = mpu->getSerialPort(0);
  HardwareSerial* s5 = mpu->getSerialPort(5);
  if (s1->available()) {
    std::cerr << "s1 available should be empty!" << std::endl;
  }
  uint8_t val = 5;
  s1->write(val);
  if (!s1->available()) {
    std::cerr << "s1 available should not be empty!" << std::endl;
  }
  uint8_t read = s1->read();
  if (read != val) {
    std::cerr << "s1->read() expected " << read << " but got " << val
              << std::endl;
  }
  // Make sure it buffers alright
  for (uint8_t v = 15; v < 75; v += 5) {
    s1->write(v);
  }
  uint8_t prev = 10;
  uint8_t count = 0;
  while (s1->available()) {
    uint8_t t = s1->read();
    if (t != prev + 5 || t >= 75) {
      std::cerr << "s1->read() got " << (uint32_t)t << " after "
                << (uint32_t)prev << std::endl;
    }
    prev = t;
  }
}

void testDualSerialMatrix(MPU* mpu, Split34* matrix) {
  // TODO
  return;
}

int main(int argc, const char* argv[]) {
  MockMPU mpu;
  mpu.setup();
  Split34 matrix;
  matrix.setup(&mpu);
  testSerialMock(&mpu);
  testDualSerialMatrix(&mpu, &matrix);
  std::cout << "Test Completed" << std::endl;
  return 0;
}