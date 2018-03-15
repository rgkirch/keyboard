// clang-format off
#include "keylayout.h"
#include "keyboard.hpp"
#include "umm.hpp"
// clang-format on
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::A;
using ::testing::An;
using ::testing::AtLeast;
using ::testing::Eq;
using ::testing::InSequence;
using ::testing::Invoke;
using ::testing::Matcher;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::StrictMock;
using ::testing::_;

using namespace std;

TEST(hello, one) { cout << "hello there how are you" << endl; }
TEST(setup, one) {
  EXPECT_CALL(myTestableKeyboardMock, begin()).Times(1);
  EXPECT_CALL(myTestableMouseMock, begin()).Times(1);
  for (uint8_t x : {6, 7, 8, 9}) {
    EXPECT_CALL(myTestableCoreMock, pinMode(x, (uint8_t)INPUT_PULLDOWN))
        .Times(1);
  }
  for (uint8_t x : {10, 11, 12, 15, 16, 17, 18, 19, 20, 21, 22, 23}) {
    EXPECT_CALL(myTestableCoreMock, pinMode(x, (uint8_t)OUTPUT)).Times(1);
    EXPECT_CALL(myTestableCoreMock, digitalWrite(x, (uint8_t)LOW)).Times(1);
  }
  setup();
  ASSERT_EQ(2, keymapLayers.size());
}