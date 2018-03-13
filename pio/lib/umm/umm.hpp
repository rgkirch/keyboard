#pragma once
#include "Arduino.h"

struct testable_keyboard_class {
  void press(uint16_t n) { Keyboard.press(n); }
  void release(uint16_t n) { Keyboard.release(n); }
  void releaseAll(void) { Keyboard.releaseAll(); }
  void begin(void) { Keyboard.begin(); }
  void end(void) { Keyboard.end(); }
  virtual ~testable_keyboard_class() = default;
};
testable_keyboard_class my_testable_keyboard;
testable_keyboard_class *myTestableKeyboard = &my_testable_keyboard;

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
void ummPinMode(uint8_t pin, uint8_t mode) { pinMode(pin, mode); }

void ummDigitalWrite(uint8_t pin, uint8_t val) { digitalWrite(pin, val); }
size_t serialDotPrintln() { Serial.println(); }
template <typename A> size_t serialDotPrint(A a) { Serial.print(a); }
template <typename A, typename B> size_t serialDotPrint(A a, B b) {
  Serial.print(a, b);
}
template <typename A> size_t serialDotPrintln(A a) { Serial.println(a); }
template <typename A, typename B> size_t serialDotPrintln(A a, B b) {
  Serial.println(a, b);
}
void serialDotBegin(long a) { Serial.begin(a); }