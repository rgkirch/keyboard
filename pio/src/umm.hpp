#include "Arduino.h"

void mouseDotBegin(void) { Mouse.begin(); }
void mouseDotEnd(void) { Mouse.end(); }
void mouseDotMove(int8_t x, int8_t y, int8_t wheel = 0, int8_t horiz = 0) {
  Mouse.move(x, y, wheel, horiz);
}
void mouseDotMoveTo(uint16_t x, uint16_t y) { Mouse.moveTo(x, y); }
void mouseDotScreenSize(uint16_t width, uint16_t height,
                        bool isMacintosh = false) {
  Mouse.screenSize(width, height, isMacintosh);
}
void mouseDotClick(uint8_t b = MOUSE_LEFT) { Mouse.click(b); }
void mouseDotScroll(int8_t wheel, int8_t horiz = 0) {
  Mouse.scroll(wheel, horiz);
}
void mouseDotSet_buttons(uint8_t left, uint8_t middle = 0, uint8_t right = 0,
                         uint8_t back = 0, uint8_t forward = 0) {
  Mouse.set_buttons(left, middle, back, right, forward);
}
void mouseDotPress(uint8_t b = MOUSE_LEFT) { Mouse.press(); }
void mouseDotRelease(uint8_t b = MOUSE_LEFT) { Mouse.release(); }
bool mouseDotIsPressed(uint8_t b = MOUSE_ALL) { return Mouse.isPressed(b); }

void keyboardDotPress(uint16_t n) { Keyboard.press(n); }

void keyboardDotRelease(uint16_t n) { Keyboard.release(n); }

void keyboardDotReleaseAll(void) { Keyboard.releaseAll(); }
void keyboardDotBegin(void) { Keyboard.begin(); }
void keyboardDotEnd(void) { Keyboard.end(); }
void ummPinMode(uint8_t pin, uint8_t mode) { pinMode(pin, mode); }

void ummDigitalWrite(uint8_t pin, uint8_t val) { digitalWrite(pin, val); }