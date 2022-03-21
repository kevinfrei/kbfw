#include "mpu/mpu.h"

class MockMPU : public MPU {
 public:
  void setup() override;
  void configOutputPin(uint8_t pin) override;
  void configInputPin(uint8_t pin) override;
  void prepPinForRead(uint8_t pin) override;
  void completePin(uint8_t pin) override;
  HardwareSerial* getSerialPort(uint8_t) override;
};