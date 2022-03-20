#include <stdint.h>

#include "kb_actions.h"
#include "reporter/usb.h"

void USBReporter::setup(MPU*, Keymap*, Display*) {}
void USBReporter::registerAction(const KeyboardAction& a, uint32_t now) {}
void USBReporter::completed() {}