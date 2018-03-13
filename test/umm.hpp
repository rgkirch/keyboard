#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <inttypes.h>
#include <stdlib.h>

using ::testing::A;
using ::testing::AtLeast;
using ::testing::Invoke;
using ::testing::Matcher;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::StrictMock;
using ::testing::_;

#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define INPUT_PULLDOWN 3
#define OUTPUT_OPENDRAIN 4
#define INPUT_DISABLE 5
#define LSBFIRST 0
#define MSBFIRST 1
#define _BV(n) (1 << (n))
#define CHANGE 4
#define FALLING 2
#define RISING 3

#define MOUSE_LEFT 1
#define MOUSE_MIDDLE 4
#define MOUSE_RIGHT 2
#define MOUSE_BACK 8
#define MOUSE_FORWARD 16
#define MOUSE_ALL                                                              \
  (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE | MOUSE_BACK | MOUSE_FORWARD)

struct testable_keyboard_class {
  virtual void press(uint16_t n) {}
  virtual void release(uint16_t n) {}
  virtual void releaseAll(void) {}
  virtual void begin(void) {}
  virtual void end(void) {}
  virtual ~testable_keyboard_class() = default;
};

struct mock_testable_keyboard_class : public testable_keyboard_class {
  MOCK_METHOD1(press, void(uint16_t n));
  MOCK_METHOD1(release, void(uint16_t n));
  MOCK_METHOD0(releaseAll, void(void));
  MOCK_METHOD0(begin, void(void));
  MOCK_METHOD0(end, void(void));
};

mock_testable_keyboard_class myTestableKeyboardMock;
testable_keyboard_class *myTestableKeyboard =
    static_cast<testable_keyboard_class *>(&myTestableKeyboardMock);

void mouseDotBegin(void) {}
void mouseDotEnd(void) {}
void mouseDotMove(int8_t x, int8_t y, int8_t wheel = 0, int8_t horiz = 0) {}
void mouseDotMoveTo(uint16_t x, uint16_t y) {}
void mouseDotScreenSize(uint16_t width, uint16_t height,
                        bool isMacintosh = false) {}
void mouseDotClick(uint8_t b = MOUSE_LEFT) {}
void mouseDotScroll(int8_t wheel, int8_t horiz = 0) {}
void mouseDotSet_buttons(uint8_t left, uint8_t middle = 0, uint8_t right = 0,
                         uint8_t back = 0, uint8_t forward = 0) {}
void mouseDotPress(uint8_t b = MOUSE_LEFT) {}
void mouseDotRelease(uint8_t b = MOUSE_LEFT) {}
bool mouseDotIsPressed(uint8_t b = MOUSE_ALL) { return true; }
void ummPinMode(uint8_t pin, uint8_t mode) {}

void ummDigitalWrite(uint8_t pin, uint8_t val) {}
size_t serialDotPrintln() { return 0; }
template <typename A> size_t serialDotPrint(A a) { return 0; }
template <typename A, typename B> size_t serialDotPrint(A a, B b) { return 0; }
template <typename A> size_t serialDotPrintln(A a) { return 0; }
template <typename A, typename B> size_t serialDotPrintln(A a, B b) {
  return 0;
}
void serialDotBegin(long a) {}