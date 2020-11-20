#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdint>
#include <chrono>

using namespace std;

#define NODE_NUM 	100000
template <typename T>
class Entry {
	public:
		T val;
		Entry(T i): val{i} {};
		Entry(): val{0}{};
		bool operator<(const Entry& o) {
			return (this->val < o.val);
		}

		bool operator>(const Entry& o) {
			return (this->val > o.val);
		}

		bool operator<(const Entry& o) const {
			return (this->val < o.val);
		}

		bool operator>(const Entry& o) const {
			return (this->val > o.val);
		}

		bool operator==(const Entry& o) {
			return (this->val == o.val);
		}
};

template<typename T>
void heapify(vector<Entry<T>> &v, int32_t len, uint32_t cur)
{
	uint32_t largest;
	uint32_t lc = 2 * cur + 1;
	uint32_t rc = 2 * cur + 2;

	largest = cur;

	if (lc < len && v[largest] < v[lc])
		largest = lc;
	if (rc < len && v[largest] < v[rc])
		largest = rc;

	if (largest != cur) {
		swap(v[cur], v[largest]);
		heapify(v, len, largest);
	}
}

template<typename T>
void heap_sort(vector<Entry<T>> &v)
{
	uint32_t len = (uint32_t)v.size();
	/* build max heap */
	for (int32_t i = len / 2 - 1; i >= 0; i--) 
		heapify(v, len, i);

	/* heap sort */
	for (int32_t i = len - 1; i > 0 ; i--) {
		swap(v[0], v[i]);
		heapify(v, i, 0);
	}

}

template<typename T>
uint32_t partition(vector<Entry<T>> &v, uint32_t left, uint32_t right)
{
	uint32_t last = left;

	for (uint32_t i = left + 1; i <= right; i++) {
		if (v[i] < v[left])
			swap(v[++last], v[i]);
	}

	return last;
}

template<typename T>
void qsort(vector<Entry<T>> &v, uint32_t left, uint32_t right)
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

template<typename T>
void merge(vector<Entry<T>> &v, int32_t left, int32_t mid, int32_t right)
{
	vector<Entry<T>> w(right - left + 1);

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

template<typename T>
void merge_sort(vector<Entry<T>> &v, int32_t left, int32_t right)
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
template<typename T>
Entry<T> find_max(const vector<Entry<T>>& v, int32_t i, int32_t j)
{
	Entry<T> max(0); 

	if (i + 1 == j) {
		return (v[i] > v[j] ? v[i] : v[j]);
	}

	max = find_max(v, i + 1, j);

	if (max > v[i])
		return max;
	else 
		return v[i];
}

template<typename T>
Entry<T> find_max2(const vector<Entry<T>>& v)
{
	Entry<T> max(0);

	for (auto& e : v) {
		if (e > max)
			max = e;
	}

	return max;
}

int main()
{
	vector<Entry<uint64_t>> v;

	for (int32_t i = 0; i < NODE_NUM; i++) {
		uint64_t val = rand() % NODE_NUM;
		v.push_back(Entry<uint64_t>(val));
	}

	auto start = chrono::high_resolution_clock::now();
	auto max1 = find_max(v, 0, (int32_t)(v.size() - 1));
	auto end = chrono::high_resolution_clock::now();
	auto dur = chrono::duration_cast<chrono::microseconds>(end - start);

	cout << "max: " << max1.val << " takes: " << dur.count() << "usec" <<endl;

	auto start2 = chrono::high_resolution_clock::now();
	auto max2 = find_max2(v);
	auto end2 = chrono::high_resolution_clock::now();
	auto dur2 = chrono::duration_cast<chrono::microseconds>(end2 - start2);
	cout << "max: " << max2.val << " takes: " << dur2.count() << "usec" <<endl;

	/* use merge sort */
	vector<Entry<uint64_t>> v3 = v;
	auto start3 = chrono::high_resolution_clock::now();
	merge_sort(v3, 0, v3.size() - 1);
	auto max3 = v3.back();
	auto end3 = chrono::high_resolution_clock::now();
	auto dur3 = chrono::duration_cast<chrono::microseconds>(end3 - start3);
	cout << "max: " << max3.val << " takes: " << dur3.count() << "usec" <<endl;

	for (int32_t i = 0; i < NODE_NUM - 1; i++) {
		if (v3[i] > v3[i + 1]) {
			cout << "wrong merge sort:v[" << i << "]: " << v3[i].val << "v[" << i + 1 << "]: " << v3[i + 1].val << "\n";
			break;
		}
	}

	/* use quick sort*/
	vector<Entry<uint64_t>> v4 = v;
	auto start4 = chrono::high_resolution_clock::now();
	qsort(v4, 0, v4.size() - 1); 
	auto max4 = v4.back();
	auto end4 = chrono::high_resolution_clock::now();
	auto dur4 = chrono::duration_cast<chrono::microseconds>(end4 - start4);
	cout << "max: " << max4.val << " takes: " << dur4.count() << "usec" <<endl;

	for (int32_t i = 0; i < NODE_NUM - 1; i++) {
		if (v4[i] > v4[i + 1]) {
			cout << "wrong qsort:v[" << i << "]: " << v4[i].val << "v[" << i + 1 << "]: " << v4[i + 1].val << "\n";
			break;
		}
	}

	/* use heap sort */
	vector<Entry<uint64_t>> v5 = v;
	auto start5 = chrono::high_resolution_clock::now();
	heap_sort(v5); 
	auto max5 = v5.back();
	auto end5 = chrono::high_resolution_clock::now();
	auto dur5 = chrono::duration_cast<chrono::microseconds>(end5 - start5);
	cout << "max: " << max5.val << " takes: " << dur5.count() << "usec" <<endl;

	for (int32_t i = 0; i < NODE_NUM - 1; i++) {
		if (v5[i] > v5[i + 1]) {
			cout << "wrong heap sort:v[" << i << "]: " << v5[i].val << "v[" << i + 1 << "]: " << v5[i + 1].val << "\n";
			break;
		}
	}
}
