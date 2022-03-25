#include "karbon.h"
#include <usb_keyboard.h>

Teensy4* mpu;
Split34* matrix;
DualSerialScanner* scanner;
KBState* kbstate;
SPI2InchLandscape* display;
Freik68* keymap;
DebugLog* dbg;

#define ______ KeymapAction()
#define KY_(CHR) KeymapAction(KEY_##CHR)
#define CN_(CHR) KeymapAction(KEY_MEDIA_##CHR) // Consumer
#define MD_(CHR) KeymapAction(Modifier::CHR)
#define LS_(NUM) KeymapAction(ActionType::LayerShift, NUM)
#define PSH(NUM) KeymapAction(ActionType::LayerPush, NUM)
#define POP() KeymapAction(ActionType::LayerPop)
#define ROT(...) KeymapAction({__VA_ARGS__})
#define CM_(CODE, ...) KeymapAction(KEY_##CHR, {__VA_ARGS__})
// Just modifiers
#define MODS(...) KeymapAction(0, {__VA_ARGS__})
#define TAPHOLD(CHR, KA) KeymapAction(KEY_##CHR, &KA)

constexpr uint32_t Base = 0;
constexpr uint32_t Func = 1;
constexpr uint32_t Win = 2;
constexpr uint32_t Linux = 3;
constexpr uint32_t MacCap = 4;
constexpr uint32_t WinCap = 5;
constexpr uint32_t WinCtl = 6;
constexpr uint32_t Raw = 7;

void InitKarbon() {
  dbg = new SerialLog();
  mpu = new Teensy4();
  matrix = new Split34();
  scanner = new DualSerialScanner();
  kbstate = new KBState();
  display = new SPI2InchLandscape();
  keymap = new Freik68({
    // clang-format off
{ // Base
KY_(ESC),     KY_(1),    KY_(2),    KY_(3),       KY_(4),          KY_(5),            KY_(6),    KY_(7),     KY_(8),     KY_(9),      KY_(0),         KY_(MINUS),
KY_(TAB),     KY_(Q),    KY_(W),    KY_(E),       KY_(R),          KY_(T),            KY_(Y),    KY_(U),     KY_(I),     KY_(O),      KY_(P),         KY_(BACKSLASH),
MD_(Cmd),     KY_(A),    KY_(S),    KY_(D),       KY_(F),          KY_(G),            KY_(H),    KY_(J),     KY_(K),     KY_(L),      KY_(SEMICOLON), KY_(QUOTE),
MD_(LShf),    KY_(Z),    KY_(X),    KY_(C),       KY_(V),          KY_(B),            KY_(N),    KY_(M),     KY_(COMMA), KY_(PERIOD), KY_(SLASH),     MD_(RShf),
MD_(LCtl), MD_(LOpt), MD_(LCmd), KY_(PAGE_UP), KY_(LEFT_BRACE), KY_(BACKSPACE),      KY_(SPACE), KY_(EQUAL), KY_(UP),    LS_(Func),      KY_(DELETE), KY_(TILDE),
                      KY_(HOME), KY_(PAGE_DOWN), KY_(END),       KY_(RIGHT_BRACE),  KY_(ENTER),  KY_(LEFT),  KY_(DOWN),  KY_(RIGHT)
},
{ // Func
______, KY_(F1), KY_(F2), KY_(F3),  KY_(F4),    KY_(F5),              KY_(F6),  KY_(F7), KY_(F8), KY_(F9),  KY_(F10),          KY_(F11),
______, ______,  ______,  ______,   ______,     ______,               ______,   ______,  ______, ______,    ______,            KY_(F12),
______, ______,  ______,  ______,   ______,     ______,               ______,   ______,  ______, ______,    ______,            ______,
______, ______,  ______,  ______,   ______,     ______,               ______,   ______,  ______, ______,    ______,            ______,
______, ______,  ______, CN_(VOLUME_INC),   ______,  ______,         ______,  ______,  ______,  ______, ROT(Base, Win, Linux), ______,
        CN_(PREV_TRACK), CN_(VOLUME_DEC), CN_(NEXT_TRACK), ______,  ______,  ______, ______, ______
},
{ // Windows
______,   ______,   ______,   ______, ______, ______,      ______, ______, ______, ______, ______, ______,
______,   ______,   ______,   ______, ______, ______,      ______, ______, ______, ______, ______, ______,
MD_(Ctl), ______,   ______,   ______, ______, ______,      ______, ______, ______, ______, ______, ______,
______,   ______,   ______,   ______, ______, ______,      ______, ______, ______, ______, ______, ______,
______,   MD_(GUI), MD_(Alt), ______, ______,  ______,    ______, ______,  ______, ______, ______, ______,
            ______, ______,   ______,           ______,  ______,   ______, ______, ______
},
{ // Linux
______,   ______,   ______,   ______, ______, ______,      ______, ______, ______, ______, ______, ______,
______,   ______,   ______,   ______, ______, ______,      ______, ______, ______, ______, ______, ______,
MD_(Ctl), ______,   ______,   ______, ______, ______,      ______, ______, ______, ______, ______, ______,
______,   ______,   ______,   ______, ______, ______,      ______, ______, ______, ______, ______, ______,
______,   MD_(GUI), MD_(Alt), ______, ______,  ______,    ______, ______,  ______, ______, ______, ______,
            ______, ______,   ______,           ______,  ______,   ______, ______, ______
},
    // clang-format on
  });
}