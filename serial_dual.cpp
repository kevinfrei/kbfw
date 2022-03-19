#include "scanner/serial_dual.h"
#include "matrix/remote_matrix.h"
#include "mpu/mpu.h"

void DualSerialScanner::setup(MPU* mp, Matrix* mat) {
  mpu = mp;
  matrix = static_cast<RemoteMatrix*>(mat);
}

bool DualSerialScanner::pendingScanCodes(uint32_t now) {
  uint8_t port = 0;
  for (HardwareSerial* ser = mpu->getSerialPort(port); ser != nullptr;
       ser = mpu->getSerialPort(++port)) {
    while (ser->available()) {
      uint8_t value = ser->read();
      uint8_t scanCode = matrix->translateWireToScancode(value, port);
      if ((scanCode & 0x7f) < 0x7f) {
        codes.push_back(scanCode);
      } else {
        // Error!
      }
    }
  }
  return !codes.empty();
}
