#include <iostream>
#include <chrono>
#include <random>

#include <dsa.h>
#include <functor.hpp>
#include <quick_uf.hpp>
#include <xsort.hpp>

#include <gtest/gtest.h>

using namespace functor;
using namespace quick_uf;
using namespace xsort;

static int test_index = 0;

#define SORT_SAMPLE_NUM (1000000U)

template <class T> void shuffle(std::vector<T> &v)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(v.begin(), v.end(), gen);
}

class main_test : public ::testing::Test
{
      protected:
	void SetUp() override
	{
		std::cout << "Test Case [" << ++test_index << "] running" << std::endl;
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
	quick_uf::quick_uf quf;

	quf.set_sz(13);

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
	int width = 20;
	std::vector<int> oc_stat;

	quick_uf::percolation perco;

	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 20; i++) {
		for (int oc = 1; oc < width * width; oc++) {
			perco.initialize_cells(width, oc);
			if (perco.is_percolated()) {
				oc_stat.push_back(oc);
				break;
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapse = end - start;
	std::cout << "Elapsed time for percolation: " << elapse.count() << "ms \n";

	int sum = 0;
	for (auto i : oc_stat) {
		sum += i;
	}
	float avg_oc = static_cast<float>(sum) / oc_stat.size();
	std::cout << "Total cells: " << width * width
		  << ", average open cell count for first percolation: " << avg_oc << std::endl;
}

TEST_F(main_test, qsort_test)
{
	int i;
	std::vector<entry<uint32_t>> values;

	for (i = 0; i < SORT_SAMPLE_NUM; ++i) {
		values.push_back(entry(SORT_SAMPLE_NUM - i));
	}

	shuffle(values);

	auto start = std::chrono::high_resolution_clock().now();
	xsort::xqsort<entry<uint32_t>>(values, 0, values.size() - 1);
	auto end = std::chrono::high_resolution_clock().now();
	std::chrono::duration<double, std::milli> elapse = end - start;
	std::cout << "Elapsed time for qsort: " << elapse.count() << "ms \n";

	for (i = 0; i < values.size() - 1; i++) {
		if (values[i] > values[i + 1]) {
			std::cout << "xqsort fails at " << i << std::endl;
		}
	}

	EXPECT_EQ(i, values.size() - 1);
}

TEST_F(main_test, mergesort_test)
{
	int i;
	std::vector<entry<uint32_t>> values;

	for (i = 0; i < SORT_SAMPLE_NUM; ++i) {
		values.push_back(entry(SORT_SAMPLE_NUM - i));
	}

	shuffle(values);

	auto start = std::chrono::high_resolution_clock().now();
	xsort::xmergesort<entry<uint32_t>>(values, 0, values.size() - 1);
	auto end = std::chrono::high_resolution_clock().now();
	std::chrono::duration<double, std::milli> elapse = end - start;
	std::cout << "Elapsed time for mergesort: " << elapse.count() << "ms \n";

	for (i = 0; i < values.size() - 1; i++) {
		if (values[i] > values[i + 1]) {
			std::cout << "xmergesort fails at " << i << std::endl;
		}
	}
}

TEST_F(main_test, heapsort_test)
{
	int i;
	std::vector<entry<uint32_t>> values;

	for (i = 0; i < SORT_SAMPLE_NUM; ++i) {
		values.push_back(entry(SORT_SAMPLE_NUM - i));
	}

	shuffle(values);

	auto start = std::chrono::high_resolution_clock().now();
	xsort::xheapsort<entry<uint32_t>>(values);
	auto end = std::chrono::high_resolution_clock().now();
	std::chrono::duration<double, std::milli> elapse = end - start;
	std::cout << "Elapsed time for heapsort: " << elapse.count() << "ms \n";

	for (i = 0; i < values.size() - 1; i++) {
		if (values[i] > values[i + 1]) {
			std::cout << "xheapsort fails at " << i << std::endl;
		}
	}
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}