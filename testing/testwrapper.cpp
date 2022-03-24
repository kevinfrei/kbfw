#include <iostream>

#include "keymaps/freik68.h"
#include "matrix/split_34.h"
#include "mocks/mock_keymap.h"
#include "mocks/mock_mpu.h"
#include "reporter/usb.h"
#include "scancode.h"
#include "scanner/serial_dual.h"

template <typename A, typename B>
void is_equal(A val1, B val2, const char* descr) {
  if (val1 != val2) {
    std::cerr << descr << " (expected " << static_cast<uint32_t>(val2)
              << " but got " << static_cast<uint32_t>(val1) << ")" << std::endl;
  }
}

void is_true(bool val, const char* descr) {
  is_equal(val, true, descr);
}

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
  is_true(!s1->available(), "s1 available should be empty!");
  uint8_t val = 5;
  s1->write(val);
  is_true(s1->available(), "s1 available should not be empty!");
  uint8_t read = s1->read();
  is_equal(val, read, "s1->read()");
  // Make sure it buffers alright
  for (uint8_t v = 15; v < 75; v += 5) {
    s1->write(v);
  }
  uint8_t prev = 10;
  uint8_t count = 0;
  while (s1->available()) {
    uint8_t t = s1->read();
    is_equal(t, prev + 5, "5 incremental");
    is_true(t < 75, "less than 75");
    prev = t;
  }
}

uint8_t send(uint8_t i) {
  return i * 3 + i % 3 + 1;
}

void testDualSerialMatrix(MPU* mpu, Split34* matrix) {
  // for values 0 to 71:
  // (val * 3 + val % 3 + 1)

  // Pressed, left
  for (uint8_t i = 0; i < 36; i++) {
    uint8_t snd = send(i);
    is_equal(matrix->translateWireToScancode(send(i), 2),
             press(valToCode((i / 6) * 12 + i % 6)),
             "Simple translation");
  }
  // release, left
  for (uint8_t i = 36; i < 72; i++) {
    uint8_t snd = send(i);
    is_equal(matrix->translateWireToScancode(send(i), 2),
             release(valToCode(((i - 36) / 6) * 12 + i % 6)),
             "Simple translation");
  }
  // Pressed, right
  for (uint8_t i = 0; i < 36; i++) {
    uint8_t snd = send(i);
    is_equal(matrix->translateWireToScancode(send(i), 4),
             press(valToCode((i / 6) * 12 + i % 6 + 6)),
             "Simple translation");
  }
  // release, left
  for (uint8_t i = 36; i < 72; i++) {
    uint8_t snd = send(i);
    is_equal(matrix->translateWireToScancode(send(i), 4),
             release(valToCode(((i - 36) / 6) * 12 + i % 6 + 6)),
             "Simple translation");
  }
  return;
}

void testScanner(MockMPU* mpu, Scanner* scanner) {
  // right Serial2
  // left Serial4
  HardwareSerial* r = mpu->getSerialPort(2);
  HardwareSerial* l = mpu->getSerialPort(4);
  uint8_t max = 0;
  for (uint8_t val = 0; val < 36; val++) {
    uint8_t scanCode1 = send(val);
    r->write(scanCode1);
    l->write(scanCode1);
    while (scanner->pendingScanCodes(0)) {
      scancode_t sc = scanner->getNext();
      is_true(isValid(sc), "Invalid scan code discovered");
      uint8_t code = codeToVal(sc);
      is_true(max <= code || code == max - 5,
              "non-monotonic scan code discovered");
      if (max < code) {
        max = code;
      }
    }
  }
}

void testTyping(MockMPU* mpu,
                Matrix* mat,
                Scanner* scanner,
                Keymap* keymap,
                USBReporter* rpt) {}

int main(int argc, const char* argv[]) {
  MockMPU mpu;
  mpu.setup();
  testSerialMock(&mpu);
  Split34 matrix;
  matrix.setup(&mpu);
  testDualSerialMatrix(&mpu, &matrix);
  DualSerialScanner scanner;
  scanner.setup(&mpu, &matrix);
  testScanner(&mpu, &scanner);
  MockKeymap keymap;
  keymap.setup(&matrix);
  USBReporter reporter;
  reporter.setup(&mpu, &keymap, nullptr);
  testTyping(&mpu, &matrix, &scanner, &keymap, &reporter);
  std::cout << "Test Completed" << std::endl;
  return 0;
}