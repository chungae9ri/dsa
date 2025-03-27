#include <iostream>

#include <dsa.h>

#include <gtest/gtest.h>

TEST(AdderTest, AddPos)
{
    EXPECT_EQ(add(2, 3), 5);
}

TEST(AdderTest, AddNeg)
{
    EXPECT_EQ(add(-2, -3), -5);
}