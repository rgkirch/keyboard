// clang-format off
#include "keylayout.h"
#include "keyboard.hpp"
#include "umm.hpp"
// clang-format on
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::A;
using ::testing::AtLeast;
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
  setup();
  ASSERT_EQ(2, keymapLayers.size());
}