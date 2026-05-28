#include <gtest/gtest.h>
#include "interval.h"

TEST(IntervalStatic, EmptyContainsNothing) {
    EXPECT_FALSE(interval::empty.contains(0.0));
    EXPECT_FALSE(interval::empty.contains(rt::infinity));
    EXPECT_FALSE(interval::empty.contains(-rt::infinity));
}

TEST(IntervalStatic, UniverseContainsArbitraryValues) {
    EXPECT_TRUE(interval::universe.contains(0.0));
    EXPECT_TRUE(interval::universe.contains(1e9));
    EXPECT_TRUE(interval::universe.contains(-1e9));
}

TEST(IntervalSize, CorrectSize) {
    interval i(1.0, 5.0);
    EXPECT_DOUBLE_EQ(i.size(), 4.0);
}

TEST(IntervalSize, ZeroSizeWhenMinEqualsMax) {
    interval i(3.0, 3.0);
    EXPECT_DOUBLE_EQ(i.size(), 0.0);
}

TEST(IntervalSize, EmptyHasNegativeSize) {
    EXPECT_LT(interval::empty.size(), 0.0);
}

TEST(IntervalContains, ValueInsideReturnsTrue) {
    interval i(0.0, 10.0);
    EXPECT_TRUE(i.contains(5.0));
}

TEST(IntervalContains, ValueAtMinReturnsTrue) {
    interval i(0.0, 10.0);
    EXPECT_TRUE(i.contains(0.0));
}

TEST(IntervalContains, ValueAtMaxReturnsTrue) {
    interval i(0.0, 10.0);
    EXPECT_TRUE(i.contains(10.0));
}

TEST(IntervalContains, ValueBelowMinReturnsFalse) {
    interval i(0.0, 10.0);
    EXPECT_FALSE(i.contains(-1.0));
}

TEST(IntervalContains, ValueAboveMaxReturnsFalse) {
    interval i(0.0, 10.0);
    EXPECT_FALSE(i.contains(11.0));
}

TEST(IntervalSurrounds, ValueInsideReturnsTrue) {
    interval i(0.0, 10.0);
    EXPECT_TRUE(i.surrounds(5.0));
}

TEST(IntervalSurrounds, ValueAtMinReturnsFalse) {
    interval i(0.0, 10.0);
    EXPECT_FALSE(i.surrounds(0.0));
}

TEST(IntervalSurrounds, ValueAtMaxReturnsFalse) {
    interval i(0.0, 10.0);
    EXPECT_FALSE(i.surrounds(10.0));
}

TEST(IntervalSurrounds, ValueBelowMinReturnsFalse) {
    interval i(0.0, 10.0);
    EXPECT_FALSE(i.surrounds(-1.0));
}

TEST(IntervalSurrounds, ValueAboveMaxReturnsFalse) {
    interval i(0.0, 10.0);
    EXPECT_FALSE(i.surrounds(11.0));
}