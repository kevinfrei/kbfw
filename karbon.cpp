#include "karbon.h"

Teensy4* mpu;
Split34* matrix;
DualSerialScanner* scanner;
USBReporter* reporter;
SPI2InchLandscape* display;
Freik68* keymap;

void InitKarbon() {
  mpu = new Teensy4();
  matrix = new Split34();
  scanner = new DualSerialScanner();
  reporter = new USBReporter();
  display = new SPI2InchLandscape();
  keymap = new Freik68({{
    // esc 1 2 3 4 5 6
    KeyboardAction(0xe5c),
    KeyboardAction('1'),
    KeyboardAction('2'),
    KeyboardAction('3'),
    KeyboardAction('4'),
    KeyboardAction('5'),

    // 6 7 8 9 0 -
    KeyboardAction('6'),
    KeyboardAction('7'),
    KeyboardAction('8'),
    KeyboardAction('9'),
    KeyboardAction('0'),
    KeyboardAction('-'),

    // tab q w e r t
    KeyboardAction(0x1ab),
    KeyboardAction('q'),
    KeyboardAction('w'),
    KeyboardAction('e'),
    KeyboardAction('r'),
    KeyboardAction('t'),

    // y u i o p \|
    KeyboardAction('y'),
    KeyboardAction('u'),
    KeyboardAction('i'),
    KeyboardAction('o'),
    KeyboardAction('p'),
    KeyboardAction('\\'),

    // caps a s d f g
    KeyboardAction(0xca95),
    KeyboardAction('a'),
    KeyboardAction('s'),
    KeyboardAction('d'),
    KeyboardAction('f'),
    KeyboardAction('g'),

    // h j k l ; '
    KeyboardAction('h'),
    KeyboardAction('j'),
    KeyboardAction('k'),
    KeyboardAction('l'),
    KeyboardAction(';'),
    KeyboardAction('\''),

    // lshift z x c v b
    KeyboardAction(0x15f1),
    KeyboardAction('z'),
    KeyboardAction('x'),
    KeyboardAction('c'),
    KeyboardAction('v'),
    KeyboardAction('b'),

    // n m , . / rshift
    KeyboardAction('n'),
    KeyboardAction('m'),
    KeyboardAction(','),
    KeyboardAction('.'),
    KeyboardAction('/'),
    KeyboardAction(0x95f1),

    // ctl opt cmd pgup [ backspace
    KeyboardAction(0x1cf1),
    KeyboardAction(0x109f),
    KeyboardAction(0x1c3d),
    KeyboardAction('^'),
    KeyboardAction('['),
    KeyboardAction(0xb59c),

    // space = up fn del `
    KeyboardAction(' '),
    KeyboardAction('='),
    KeyboardAction('^'), 
    KeyboardAction(0xf5),
    KeyboardAction(0xde1),
    KeyboardAction('`'),

    // home pagedown end ]
    KeyboardAction(0x4033),
    KeyboardAction('V'),
    KeyboardAction(0xe5d),
    KeyboardAction(']'),

    // enter left down right
    KeyboardAction(0xe5134),
    KeyboardAction('<'), 
    KeyboardAction(0xd035),
    KeyboardAction('>') 
  }});
}