#pragma once
#include <stdint.h>

#include "dbg/seriallog.h"

// Which processor/platform is the controller?
#include "mpu/teensy4.h"

// What do the keyboard piece(s) look like?
#include "matrix/split_34.h"

// How are we getting keypress information?
#include "scanner/serial_dual.h"

// What is the keymap we're using?
#include "keymaps/freik68.h"

// How are we recording keyboard events?
#include "kbstate/kbstate.h"

// What are we doing to display information?
#include "displays/spi_2inch_landscape.h"

extern Teensy4* mpu;
extern Split34* matrix;
extern DualSerialScanner* scanner;
extern KBState* kbstate;
extern SPI2InchLandscape* display;
extern Freik68* keymap;
extern DebugLog* dbg;

#define allocate InitKarbon
void InitKarbon();