#include <vector>

#include "mocks/mock_mpu.h"

std::vector<HardwareSerial*> serialPorts;

void MockMPU::setup() {}
void MockMPU::configOutputPin(uint8_t pin) {}
void MockMPU::configInputPin(uint8_t pin) {}
void MockMPU::prepPinForRead(uint8_t pin) {}
void MockMPU::completePin(uint8_t pin) {}
HardwareSerial* MockMPU::getSerialPort(uint8_t which) {
  while (serialPorts.size() < which) {
    serialPorts.push_back(new HardwareSerial{});
  }
  return serialPorts[which];
}
