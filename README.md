# kbfw

This is my "v2" keyboard firmware

Core design philosophy starts with "Works with Arduino IDE" but also must work
with VSCode.

> Personally, I detest the Arduino IDE, but if things work with the Arduino IDE,
> I don't have to worry about API's & stuff. There's huge, moderately maintained
> ecosystem around of that. Don't take on cost that others have already paid. I
> like supporting vendors that have great ecosystems, so at the top of my list
> is Adafruit and PJRC, with Arduino a close third. Adafruit creates usable,
> accessible hardware with amazing software libraries to go with it. If I can
> use an Adafruit part, I will, because I want to support great companies doing
> great things.

# Goals

I want the code to NOT be filled with #ifdef's. You should have some simple
configuration system that handles everything else. I also want the code to be
buildable both inside and outside of the Arduino IDE. I'm not 100% certain this
is doable, but I think that you can have multiple .ino files and they all get
used.

# Design

## High level hand wavy stuff

There are logically 4 phases of what a kb firmware system needs to do:

1. Scan the switches
2. Determine actions to take
3. Report actions to the host (keystrokes)
4. Clean up after reporting

The are a few places where this doesn't quite hold up: The num lock/caps
lock/etc... reports from the host (Light an LED sort of thing), and if you want
your keyboard to do "other things".

I'm going to keep the "other things" to a minimum, and probably want to just
keep them as available plug-ins that can basically hijack steps 2-4 completely.

I'll start with a nice clean design, and it will naturally devolve into a big
mess, but given that I've not really started with any sort of architecture
before, starting with some architecture will hopefully help.

## Hardware "abstraction" levels

I believe there are a few places where you want abstraction. The lowest level is
the MPU itself: Are you using a Teensy? A Pro Micro? An nRF52840? There are at
least a couple layers of mess underneath that (CPU architecture, RAM,
flash/storage, etc...) as well.

You definitely need to abstract out how you're reading switches. Are you pulling
over a keyboard matrix, a serial wire, an I2C connection, maybe SPI, or a
Bluetooth wireless connection? (I've personally implemented 3 of those).

You also want to abstract what your 'target' keyboard protocol might be. USB?
Bluetooth? Maybe even ADB or PS/2?

## Plug in ideas

The 2 basic plugins I can come up with are: Calculator & Emulator.

I have a silly Apple II+ emulator working on an Teensy with a screen, and I
really do want a calculator. These plugins should be able to operate
"independently" of the normal loop, but must also specify an escape to resume
normal keyboard operation.

# Rules

All code should be auto-formatted. I'd love to enforce that with git. I know how
to do it with a javascript package. Worst case, I can use husky to do it, even
for this stuff. Use Prettier whenever possible, and clang-format for C/C++ code
(I with Prettier would support C++).

Also: I think I'm going to try git subtrees for dealing with all the random
dependencies (outside of Arduino IDE). I've been using git submodules, and
they're really a PITA. Hopefully git subtrees work better and are easier to
manage.
