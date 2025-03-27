#include <iostream>
#include <chrono>
#include "sort.h"

using namespace std;

#define NODE_NUM 	100000

int main()
{
	vector<mysort::Entry<uint64_t>> v;

	for (int32_t i = 0; i < NODE_NUM; i++) {
		uint64_t key = rand() % NODE_NUM;
		v.push_back(mysort::Entry<uint64_t>(key));
	}

	/* use merge sort */
	vector<mysort::Entry<uint64_t>> v3 = v;
	auto start3 = chrono::high_resolution_clock::now();
	mysort::merge_sort(v3, 0, v3.size() - 1);
	auto end3 = chrono::high_resolution_clock::now();
	auto dur3 = chrono::duration_cast<chrono::microseconds>(end3 - start3);
	cout << "merge sort takes: " << dur3.count() << "usec" <<endl;

	for (int32_t i = 0; i < NODE_NUM - 1; i++) {
		if (v3[i] > v3[i + 1]) {
			cout << "wrong merge sort:v[" << i << "]: " << v3[i].key << ", v[" << i + 1 << "]: " << v3[i + 1].key << "\n";
			break;
		}
	}

	/* use quick sort*/
	vector<mysort::Entry<uint64_t>> v4 = v;
	auto start4 = chrono::high_resolution_clock::now();
	mysort::qsort(v4, 0, v4.size() - 1); 
	auto end4 = chrono::high_resolution_clock::now();
	auto dur4 = chrono::duration_cast<chrono::microseconds>(end4 - start4);
	cout << "quick sort takes: " << dur4.count() << "usec" <<endl;

	for (int32_t i = 0; i < NODE_NUM - 1; i++) {
		if (v4[i] > v4[i + 1]) {
			cout << "wrong qsort:v[" << i << "]: " << v4[i].key << ", v[" << i + 1 << "]: " << v4[i + 1].key<< "\n";
			break;
		}
	}

	/* use heap sort */
	vector<mysort::Entry<uint64_t>> v5 = v;
	auto start5 = chrono::high_resolution_clock::now();
	mysort::heap_sort(v5); 
	auto end5 = chrono::high_resolution_clock::now();
	auto dur5 = chrono::duration_cast<chrono::microseconds>(end5 - start5);
	cout << "heap sort takes: " << dur5.count() << "usec" <<endl;

	for (int32_t i = 0; i < NODE_NUM - 1; i++) {
		if (v5[i] > v5[i + 1]) {
			cout << "wrong heap sort:v[" << i << "]: " << v5[i].key << ", v[" << i + 1 << "]: " << v5[i + 1].key << "\n";
			break;
		}
	}

	/* use radix sort */
#if 1
	vector<mysort::Entry<uint64_t>> v6 = v;
#else
	vector<mysort::Entry<uint64_t>> v6;
	mysort::Entry<uint64_t> e1(5);
	mysort::Entry<uint64_t> e2(1);
	mysort::Entry<uint64_t> e3(4);
	mysort::Entry<uint64_t> e4(3);
	mysort::Entry<uint64_t> e5(2);
	mysort::Entry<uint64_t> e6(6);
	mysort::Entry<uint64_t> e7(2);
	mysort::Entry<uint64_t> e8(8);
	mysort::Entry<uint64_t> e9(6);
	mysort::Entry<uint64_t> e10(1);
	/*mysort::Entry<uint64_t> e11(12);*/
	/*mysort::Entry<uint64_t> e12(123);*/
	/*mysort::Entry<uint64_t> e13(83);*/
	v6.push_back(e1);
	v6.push_back(e2);
	v6.push_back(e3);
	v6.push_back(e4);
	v6.push_back(e5);
	v6.push_back(e6);
	v6.push_back(e7);
	v6.push_back(e8);
	v6.push_back(e9);
	v6.push_back(e10);
	/*v6.push_back(e11);*/
	/*v6.push_back(e12);*/
	/*v6.push_back(e13);*/
#endif

	auto start6 = chrono::high_resolution_clock::now();
	mysort::radix_sort(v6, 10); 
	auto end6 = chrono::high_resolution_clock::now();
	auto dur6 = chrono::duration_cast<chrono::microseconds>(end6 - start6);
	cout << "radix sort takes: " << dur6.count() << "usec" <<endl;

	for (int32_t i = 0; i < NODE_NUM - 1; i++) {
		if (v6[i] > v6[i + 1]) {
			cout << "wrong radix sort:v[" << i << "]: " << v6[i].key << ", v[" << i + 1 << "]: " << v6[i + 1].key << "\n";
			break;
		}
	}

	vector<mysort::Entry<std::string>> v7;
	mysort::Entry<std::string> e1("Hello World!");
	mysort::Entry<std::string> e2("How are you?");
	mysort::Entry<std::string> e3("I am FINE....");
	mysort::Entry<std::string> e4("This is sorted by radix_sort");
	mysort::Entry<std::string> e5("               It looks good!");
	v7.push_back(e1);
	v7.push_back(e2);
	v7.push_back(e3);
	v7.push_back(e4);
	v7.push_back(e5);

	auto start7 = chrono::high_resolution_clock::now();
	mysort::radix_sort(v7, 128); 
	auto end7 = chrono::high_resolution_clock::now();
	auto dur7 = chrono::duration_cast<chrono::microseconds>(end7 - start7);
	cout << "radix sort takes: " << dur7.count() << "usec" <<endl;

	for (auto p : v7) {
		std::cout << p.key << "\n";
	}
}
