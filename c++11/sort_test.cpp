#include <iostream>
#include <chrono>
#include "sort.h"

using namespace std;

#define NODE_NUM 	100000

template <typename T>
class Entry {
	public:
		T key;
		Entry(T o): key{o} {};
		Entry(): key{0}{};
		bool operator<(const Entry& o) {
			return (this->key < o.key);
		}

		bool operator>(const Entry& o) {
			return (this->key > o.key);
		}

		bool operator<(const Entry& o) const {
			return (this->key < o.key);
		}

		bool operator>(const Entry& o) const {
			return (this->key > o.key);
		}

		bool operator==(const Entry& o) {
			return (this->key == o.key);
		}
};

int main()
{
	vector<Entry<uint64_t>> v;

	for (int32_t i = 0; i < NODE_NUM; i++) {
		uint64_t key = rand() % NODE_NUM;
		v.push_back(Entry<uint64_t>(key));
	}

	/* use merge sort */
	vector<Entry<uint64_t>> v3 = v;
	auto start3 = chrono::high_resolution_clock::now();
	mysort::merge_sort(v3, 0, v3.size() - 1);
	auto max3 = v3.back();
	auto end3 = chrono::high_resolution_clock::now();
	auto dur3 = chrono::duration_cast<chrono::microseconds>(end3 - start3);
	cout << "merge sort takes: " << dur3.count() << "usec" <<endl;

	for (int32_t i = 0; i < NODE_NUM - 1; i++) {
		if (v3[i] > v3[i + 1]) {
			cout << "wrong merge sort:v[" << i << "]: " << v3[i].key << "v[" << i + 1 << "]: " << v3[i + 1].key << "\n";
			break;
		}
	}

	/* use quick sort*/
	vector<Entry<uint64_t>> v4 = v;
	auto start4 = chrono::high_resolution_clock::now();
	mysort::qsort(v4, 0, v4.size() - 1); 
	auto max4 = v4.back();
	auto end4 = chrono::high_resolution_clock::now();
	auto dur4 = chrono::duration_cast<chrono::microseconds>(end4 - start4);
	cout << "quick sort takes: " << dur4.count() << "usec" <<endl;

	for (int32_t i = 0; i < NODE_NUM - 1; i++) {
		if (v4[i] > v4[i + 1]) {
			cout << "wrong qsort:v[" << i << "]: " << v4[i].key << "v[" << i + 1 << "]: " << v4[i + 1].key<< "\n";
			break;
		}
	}

	/* use heap sort */
	vector<Entry<uint64_t>> v5 = v;
	auto start5 = chrono::high_resolution_clock::now();
	mysort::heap_sort(v5); 
	auto max5 = v5.back();
	auto end5 = chrono::high_resolution_clock::now();
	auto dur5 = chrono::duration_cast<chrono::microseconds>(end5 - start5);
	cout << "heap sort takes: " << dur5.count() << "usec" <<endl;

	for (int32_t i = 0; i < NODE_NUM - 1; i++) {
		if (v5[i] > v5[i + 1]) {
			cout << "wrong heap sort:v[" << i << "]: " << v5[i].key << "v[" << i + 1 << "]: " << v5[i + 1].key << "\n";
			break;
		}
	}
}
