#include <iostream>

#include <dsa.h>
#include <functor.hpp>

#include <gtest/gtest.h>

using namespace functor;

static int test_index = 0;

class main_test: public ::testing::Test {
protected:
    void SetUp() override {
        std::cout << "[" << ++test_index << "] Running Test "<< std::endl;
    }
};

TEST_F(main_test, functor)
{
    EXPECT_EQ(square_functor::square(2.0), 4.0);
    square_functor callable_obj_sq;
    EXPECT_EQ(callable_obj_sq(3.0), 9.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}