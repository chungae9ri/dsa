#include <iostream>

#include <dsa.h>
#include <functor.hpp>

#include <gtest/gtest.h>

using namespace functor;

TEST(addertest, addpos)
{
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-2, -3), -5);
}

TEST(functortest, functor)
{
    EXPECT_EQ(square_functor::square(2.0), 4.0);
    square_functor callable_obj_sq;
    EXPECT_EQ(callable_obj_sq(3.0), 9.0);
}