#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdint>
#include <chrono>

using namespace std;

uint32_t partition(vector<uint64_t> &v, uint32_t left, uint32_t right)
{
	uint32_t last = left;

	for (uint32_t i = left + 1; i <= right; i++) {
		if (v[i] < v[left])
			swap(v[++last], v[i]);
	}

	return last;
}

void qsort(vector<uint64_t> &v, uint32_t left, uint32_t right)
{
	uint32_t last; 
	if (left >= right)
		return;

	swap(v[left], v[left + (right - left) / 2]);
	last = partition(v, left, right);
	swap(v[left], v[last]);
	qsort(v, left, last); 
	qsort(v, last + 1, right);
}

void merge(vector<uint64_t> &v, int32_t left, int32_t mid, int32_t right)
{
	vector<uint64_t> w(right - left + 1);

	for (int i = 0, j = left, k = mid + 1; i < w.size(); i++) {
		if (j == mid + 1) 
			w[i] = v[k++];
		else if (k == right + 1)
			w[i] = v[j++];
		else if (v[j] > v[k]) 
			w[i] = v[k++];
		else 
			w[i] = v[j++];
	}

	for (int i = 0; i < w.size(); i++) {
		v[i + left] = w[i];
	}
}

void merge_sort(vector<uint64_t> &v, int32_t left, int32_t right)
{
	if (left < right) {
		uint32_t mid = left + (right - left) / 2;
		merge_sort(v, left, mid);
		merge_sort(v, mid + 1, right);

		merge(v, left, mid, right);
	}
}

/* 
 * if not using reference, it takes so long 
 * because every recursing copies the v to the subsequent calls 
 */
uint64_t find_max(const vector<uint64_t> &v, int32_t i, int32_t j)
{
	int max; 

	if (i + 1 == j) {
		return (v[i] > v[j] ? v[i] : v[j]);
	}

	max = find_max(v, i + 1, j);

	if (max > v[i])
		return max;
	else 
		return v[i];
}

uint64_t find_max2(const vector<uint64_t> v)
{
	uint64_t max = 0;

	for (auto num: v) {
		if (num > max)
			max = num;
	}

	return max;
}

int main()
{
	vector<uint64_t> v;

	for (int32_t i = 0; i < 10000; i++) {
		v.push_back(rand() % 10000);
	}

	auto start = chrono::high_resolution_clock::now();
	auto max1 = find_max(v, 0, (int32_t)(v.size() - 1));
	auto end = chrono::high_resolution_clock::now();
	auto dur = chrono::duration_cast<chrono::microseconds>(end - start);

	cout << "max: " << max1 << " takes: " << dur.count() << "usec" <<endl;

	auto start2 = chrono::high_resolution_clock::now();
	auto max2 = find_max2(v);
	auto end2 = chrono::high_resolution_clock::now();
	auto dur2 = chrono::duration_cast<chrono::microseconds>(end2 - start2);
	cout << "max: " << max2 << " takes: " << dur2.count() << "usec" <<endl;

	/* use merge sort */
	vector<uint64_t> v3 = v;
	auto start3 = chrono::high_resolution_clock::now();
	merge_sort(v3, 0, v3.size() - 1);
	auto max3 = v3.back();
	auto end3 = chrono::high_resolution_clock::now();
	auto dur3 = chrono::duration_cast<chrono::microseconds>(end3 - start3);
	cout << "max: " << max3 << " takes: " << dur3.count() << "usec" <<endl;

	/* use quick sort*/
	vector<uint64_t> v4 = v;
	auto start4 = chrono::high_resolution_clock::now();
	qsort(v4, 0, v4.size() - 1); 
	auto max4 = v4.back();
	auto end4 = chrono::high_resolution_clock::now();
	auto dur4 = chrono::duration_cast<chrono::microseconds>(end4 - start4);
	cout << "max: " << max4 << " takes: " << dur4.count() << "usec" <<endl;
}
