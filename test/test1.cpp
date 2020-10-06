#include "gtest/gtest.h"
#include "static.h"

TEST(testA, test1) {
    auto t = 10;
    EXPECT_EQ (sampleStatic::testStaticAdd10(10), t+10);
    EXPECT_EQ (true, true);
    EXPECT_NE (true, false);
}