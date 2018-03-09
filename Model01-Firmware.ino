// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

/////////
// Notes:
// semicolon and quote swapped
// any key is `one-shot command (leftgui) key
// butterfly is spacebar
// LED => backspace
// left thumb key 1 => Shift
// right thumb key 4 => Shift





/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numlock" mode, which is mostly just the Numlock specific LED mode
#include "Kaleidoscope-Numlock.h"

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for an LED mode that makes a red pixel chase a blue pixel across the keyboard
#include "Kaleidoscope-LEDEffect-Chase.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for an LED mode that prints the keys you press in letters 4px high
#include "Kaleidoscope-LED-AlphaSquare.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-Model01-TestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Benji's customizations
#include <Kaleidoscope-ShapeShifter.h>
// #include <Kaleidoscope-TopsyTurvy.h>
#include <Kaleidoscope-Macros.h>

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO,
       MACRO_ANY,
       MACRO_PD_LEFT_CURLY,
       MACRO_PD_RIGHT_CURLY,
       MACRO_PD_LEFT_PAREN,
       MACRO_PD_ASTERISK,
       MACRO_PD_RIGHT_PAREN,
       MACRO_PD_PLUS,
       MACRO_PD_EXCLAMATION,
       MACRO_PD_CUT,
       MACRO_PD_COPY,
       MACRO_PD_PASTE,
       SHIFT_Backtick, SHIFT_Semicolon,     SHIFT_Comma, SHIFT_Period, SHIFT_P, SHIFT_Y, SHIFT_Tab,
       SHIFT_PageUp,   SHIFT_A,             SHIFT_O,     SHIFT_E,      SHIFT_U, SHIFT_I,
       SHIFT_PageDown, SHIFT_Quote,         SHIFT_Q,     SHIFT_J,      SHIFT_K, SHIFT_X, SHIFT_Escape,
       SHIFT_LeftGui,
       SHIFT_Enter,      SHIFT_F, SHIFT_G, SHIFT_C, SHIFT_R, SHIFT_L, SHIFT_Slash,
                         SHIFT_D, SHIFT_H, SHIFT_T, SHIFT_N, SHIFT_S, SHIFT_Minus,
       SHIFT_Spacebar,   SHIFT_B, SHIFT_M, SHIFT_W, SHIFT_V, SHIFT_Z,
       MACRO_PD_AT, MACRO_PD_CARET
     };

//
/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  */

enum { PDVORAK, SHIFT, FUNCTION, NUMPAD}; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

const Key keymaps[][ROWS][COLS] PROGMEM = {
  [PDVORAK] = KEYMAP_STACKED
  (___,          Key_LeftBracket,         M(MACRO_PD_LEFT_CURLY),     M(MACRO_PD_RIGHT_CURLY),      M(MACRO_PD_LEFT_PAREN), Key_Equals, Key_Backspace,
   Key_Backtick, Key_Semicolon,     Key_Comma, Key_Period, Key_P, Key_Y, Key_Tab,
   Key_PageUp,   Key_A,             Key_O,     Key_E,      Key_U, Key_I,
   Key_PageDown, Key_Quote,         Key_Q,     Key_J,      Key_K, Key_X, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, ShiftToLayer(SHIFT),
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),   M(MACRO_PD_ASTERISK), M(MACRO_PD_RIGHT_PAREN), M(MACRO_PD_PLUS), Key_RightBracket, M(MACRO_PD_EXCLAMATION), Key_KeypadNumLock,
   Key_Enter,      Key_F, Key_G, Key_C, Key_R, Key_L, Key_Slash,
                   Key_D, Key_H, Key_T, Key_N, Key_S, Key_Minus,
   Key_Spacebar,   Key_B, Key_M, Key_W, Key_V, Key_Z, M(MACRO_PD_AT),
   ShiftToLayer(SHIFT), Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),

  [SHIFT] = KEYMAP_STACKED
  (___,               Key_7,                  Key_5,          Key_3,           Key_1,      Key_9, ___,
   M(SHIFT_Backtick), M(SHIFT_Semicolon),     M(SHIFT_Comma), M(SHIFT_Period), M(SHIFT_P), M(SHIFT_Y), M(SHIFT_Tab),
   M(SHIFT_PageUp),   M(SHIFT_A),             M(SHIFT_O),     M(SHIFT_E),      M(SHIFT_U), M(SHIFT_I),
   M(SHIFT_PageDown), M(SHIFT_Quote),         M(SHIFT_Q),     M(SHIFT_J),      M(SHIFT_K), M(SHIFT_X), M(SHIFT_Escape),
   ___, ___,  Key_LeftGui,    ___,
   ___,

   ___,                 Key_0,      Key_2,      Key_4,      Key_6,      Key_8,      ___,
   M(SHIFT_Enter),      M(SHIFT_F), M(SHIFT_G), M(SHIFT_C), M(SHIFT_R), M(SHIFT_L), M(SHIFT_Slash),
                        M(SHIFT_D), M(SHIFT_H), M(SHIFT_T), M(SHIFT_N), M(SHIFT_S), M(SHIFT_Minus),
   M(SHIFT_Spacebar),   M(SHIFT_B), M(SHIFT_M), M(SHIFT_W), M(SHIFT_V), M(SHIFT_Z), M(MACRO_PD_CARET),
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           XXX,
   Key_Tab,  ___,              Key_mouseUp, ___,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseScrollUp,
   Key_Home, Key_mouseL,       Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,
   Key_End,  Key_PrintScreen,  Key_Insert,  ___,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseScrollDn,
   ___, Key_Delete, ___, Key_LeftShift,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_Find,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  ___,              ___,
   Key_PcApplication,          Key_Mute,               Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   Key_RightShift, ___, Key_Enter, ___,
   ___),


  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, Key_LEDEffectNext,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___,
   ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___,
                           ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         Key_Quote,
   ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
   ___, ___, ___, ___,
   ___)
};

static const kaleidoscope::ShapeShifter::dictionary_t shape_shift_dictionary[] PROGMEM = {
 {Key_NoKey, Key_NoKey},
};
/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

bool LEFT_GUI_ON = false;

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;

  case MACRO_ANY:
    anyKeyMacro(keyState);
    break;

  case MACRO_PD_LEFT_CURLY:
    if (keyToggledOn(keyState)) {
      return Macros.type(PSTR("{"));
    }
    break;

  case MACRO_PD_RIGHT_CURLY:
  if (keyToggledOn(keyState)) {
      return Macros.type(PSTR("}"));
    }
    break;

  case MACRO_PD_LEFT_PAREN:
  if (keyToggledOn(keyState)) {
      return Macros.type(PSTR("("));
    }
    break;

  case MACRO_PD_ASTERISK:
  if (keyToggledOn(keyState)) {
      return Macros.type(PSTR("*"));
    }
    break;

  case MACRO_PD_AT:
  if (keyToggledOn(keyState)) {
      return Macros.type(PSTR("@"));
    }
    break;

  case MACRO_PD_CARET:
  if (keyToggledOn(keyState)) {
      return Macros.type(PSTR("^"));
    }
    break;

  case MACRO_PD_RIGHT_PAREN:
  if (keyToggledOn(keyState)) {
      return Macros.type(PSTR(")"));
    }
    break;

  case MACRO_PD_PLUS:
  if (keyToggledOn(keyState)) {
      return Macros.type(PSTR("+"));
    }
    break;

  case MACRO_PD_EXCLAMATION:
  if (keyToggledOn(keyState)) {
      return Macros.type(PSTR("!"));
    }
    break;
  case SHIFT_LeftGui:
    if (keyToggledOn(keyState)) {
        LEFT_GUI_ON = true;
    } else if (keyToggledOff(keyState)) {
        LEFT_GUI_ON = false;
    }
    break;

  case SHIFT_Backtick:
    return MACRODOWN(D(LeftShift), T(Backtick), U(LeftShift));
    break;
  case SHIFT_Semicolon:
    return MACRODOWN(D(LeftShift), T(Semicolon), U(LeftShift));
    break;
  case SHIFT_Comma:
    return MACRODOWN(D(LeftShift), T(Comma), U(LeftShift));
    break;
  case SHIFT_Period:
    return MACRODOWN(D(LeftShift), T(Period), U(LeftShift));
    break;
  case SHIFT_P:
    return MACRODOWN(D(LeftShift), T(P), U(LeftShift));
    break;
  case SHIFT_Y:
    return MACRODOWN(D(LeftShift), T(Y), U(LeftShift));
    break;
  case SHIFT_Tab:
    return MACRODOWN(D(LeftShift), T(Tab), U(LeftShift));
    break;

  case SHIFT_PageUp:
    return MACRODOWN(D(LeftShift), T(PageUp), U(LeftShift));
    break;
  case SHIFT_A:
    return MACRODOWN(D(LeftShift), T(A), U(LeftShift));
    break;
  case SHIFT_O:
    return MACRODOWN(D(LeftShift), T(O), U(LeftShift));
    break;
  case SHIFT_E:
    return MACRODOWN(D(LeftShift), T(E), U(LeftShift));
    break;
  case SHIFT_U:
    return MACRODOWN(D(LeftShift), T(U), U(LeftShift));
    break;
  case SHIFT_I:
    return MACRODOWN(D(LeftShift), T(I), U(LeftShift));
    break;

  case SHIFT_PageDown:
    return MACRODOWN(D(LeftShift), T(PageDown), U(LeftShift));
    break;
  case SHIFT_Quote:
    return MACRODOWN(D(LeftShift), T(Quote), U(LeftShift));
    break;
  case SHIFT_Q:
    return MACRODOWN(D(LeftShift), T(Q), U(LeftShift));
    break;
  case SHIFT_J:
    return MACRODOWN(D(LeftShift), T(J), U(LeftShift));
    break;
  case SHIFT_K:
    return MACRODOWN(D(LeftShift), T(K), U(LeftShift));
    break;
  case SHIFT_X:
    return MACRODOWN(D(LeftShift), T(X), U(LeftShift));
    break;
  case SHIFT_Escape:
    return MACRODOWN(D(LeftShift), T(Escape), U(LeftShift));
    break;

  case SHIFT_Enter:
    return MACRODOWN(D(LeftShift), T(Enter), U(LeftShift));
    break;
  case SHIFT_F:
    return MACRODOWN(D(LeftShift), T(F), U(LeftShift));
    break;
  case SHIFT_G:
    return MACRODOWN(D(LeftShift), T(G), U(LeftShift));
    break;
  case SHIFT_C:
    return MACRODOWN(D(LeftShift), T(C), U(LeftShift));
    break;
  case SHIFT_R:
    return MACRODOWN(D(LeftShift), T(R), U(LeftShift));
    break;
  case SHIFT_L:
    if (LEFT_GUI_ON) {
        return MACRODOWN(D(LeftShift), D(LeftGui), T(L), U(LeftGui), U(LeftShift));
    }
    return MACRODOWN(D(LeftShift), T(L), U(LeftShift));
    break;
  case SHIFT_Slash:
    return MACRODOWN(D(LeftShift), T(Slash), U(LeftShift));
    break;

  case SHIFT_D:
    return MACRODOWN(D(LeftShift), T(D), U(LeftShift));
    break;
  case SHIFT_H:
    if (LEFT_GUI_ON) {
        return MACRODOWN(D(LeftShift), D(LeftGui), T(H), U(LeftGui), U(LeftShift));
    }
    return MACRODOWN(D(LeftShift), T(H), U(LeftShift));
    break;
  case SHIFT_T:
    return MACRODOWN(D(LeftShift), T(T), U(LeftShift));
    break;
  case SHIFT_N:
    return MACRODOWN(D(LeftShift), T(N), U(LeftShift));
    break;
  case SHIFT_S:
    return MACRODOWN(D(LeftShift), T(S), U(LeftShift));
    break;
  case SHIFT_Minus:
    return MACRODOWN(D(LeftShift), T(Minus), U(LeftShift));
    break;

  case SHIFT_Spacebar:
    return MACRODOWN(D(LeftShift), T(Spacebar), U(LeftShift));
    break;
  case SHIFT_B:
    return MACRODOWN(D(LeftShift), T(B), U(LeftShift));
    break;
  case SHIFT_M:
    return MACRODOWN(D(LeftShift), T(M), U(LeftShift));
    break;
  case SHIFT_W:
    return MACRODOWN(D(LeftShift), T(W), U(LeftShift));
    break;
  case SHIFT_V:
    return MACRODOWN(D(LeftShift), T(V), U(LeftShift));
    break;
  case SHIFT_Z:
    return MACRODOWN(D(LeftShift), T(Z), U(LeftShift));
    break;


  }

  return MACRO_NONE;
}



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.
static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** The 'setup' function is one of the two standard Arduino sketch functions.
  * It's called when your keyboard first powers up. This is where you set up
  * Kaleidoscope and any plugins.
  */

void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Next, tell Kaleidoscope which plugins you want to use.
  // The order can be important. For example, LED effects are
  // added in the order they're listed here.
  Kaleidoscope.use(
    // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
    &BootGreetingEffect,

    // The hardware test mode, which can be invoked by tapping Prog, LED and the left Fn button at the same time.
    &TestMode,

    // LEDControl provides support for other LED modes
    &LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    &LEDOff,

    // The rainbow effect changes the color of all of the keyboard's keys at the same time
    // running through all the colors of the rainbow.
    &LEDRainbowEffect,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    &LEDRainbowWaveEffect,

    // The chase effect follows the adventure of a blue pixel which chases a red pixel across
    // your keyboard. Spoiler: the blue pixel never catches the red pixel
    &LEDChaseEffect,

    // These static effects turn your keyboard's LEDs a variety of colors
    &solidRed, &solidOrange, &solidYellow, &solidGreen, &solidBlue, &solidIndigo, &solidViolet,

    // The breathe effect slowly pulses all of the LEDs on your keyboard
    &LEDBreatheEffect,

    // The AlphaSquare effect prints each character you type, using your
    // keyboard's LEDs as a display
    &AlphaSquareEffect,

    // The stalker effect lights up the keys you've pressed recently
    &StalkerEffect,

    // The numlock plugin is responsible for lighting up the 'numpad' mode
    // with a custom LED effect
    &NumLock,

    // The macros plugin adds support for macros
    &Macros,

    // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
    &MouseKeys,

    // The HostPowerManagement plugin enables waking up the host from suspend,
    // and allows us to turn LEDs off when it goes to sleep.
    &HostPowerManagement,

    // Benji's customiations
    &ShapeShifter, &Macros
  );
  ShapeShifter.dictionary = shape_shift_dictionary;

  // While we hope to improve this in the future, the NumLock plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumLock.numPadLayer = NUMPAD;

  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = { 255, 0, 0 };

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // The LED Stalker mode has a few effects. The one we like is
  // called 'BlazingTrail'. For details on other options,
  // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(BlazingTrail);

  // We want the keyboard to be able to wake the host up from suspend.
  HostPowerManagement.enableWakeup();

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
