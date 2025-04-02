#include <iostream>

#include <dsa.h>
#include <functor.hpp>
#include <quick_uf.hpp>

#include <gtest/gtest.h>

using namespace functor;
using namespace quick_uf;

static int test_index = 0;

class main_test: public ::testing::Test {
protected:
    void SetUp() override {
        std::cout << "Test case [" << ++test_index << "] running"<< std::endl;
    }
};

TEST_F(main_test, functor_test)
{
    EXPECT_EQ(square_functor::square(2.0), 4.0);
    square_functor callable_obj_sq;
    EXPECT_EQ(callable_obj_sq(3.0), 9.0);
}

TEST_F(main_test, union_find_test)
{
    quick_uf::quick_uf quf{13};

    quf.union_set(9, 11);
    quf.union_set(9, 12);
    quf.union_set(8, 10);
    quf.union_set(6, 8);
    quf.union_set(6, 9);
    quf.union_set(3, 6);
    quf.union_set(3, 7);
    quf.union_set(1, 3);
    quf.union_set(1, 4);
    quf.union_set(1, 5);
    quf.union_set(0, 1);
    quf.union_set(0, 2);

    EXPECT_EQ(0, quf.get_id(1));
    EXPECT_EQ(0, quf.get_id(2));
    EXPECT_EQ(1, quf.get_id(3));
    EXPECT_EQ(3, quf.get_id(7));
    EXPECT_EQ(6, quf.get_id(8));
    EXPECT_EQ(9, quf.get_id(11));

    quf.root(9);

    EXPECT_EQ(0, quf.get_id(1));
    EXPECT_EQ(0, quf.get_id(2));
    EXPECT_EQ(0, quf.get_id(6));
    EXPECT_EQ(0, quf.get_id(3));
    EXPECT_EQ(0, quf.get_id(9));
    EXPECT_EQ(6, quf.get_id(8));
    EXPECT_EQ(9, quf.get_id(11));
    EXPECT_EQ(8, quf.get_id(10));
}

TEST_F(main_test, percolation_test)
{
    quick_uf::percolation perco{5 * 5};

    perco.initialize_cells(10);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}