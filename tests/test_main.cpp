#include "gtest/gtest.h"

TEST(Welcome, HelloFromFastLsp) {
  EXPECT_STREQ("foo", "foo");
  EXPECT_STRNE("foo", "bar");
}
