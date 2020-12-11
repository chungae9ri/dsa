#ifndef _SORT_H_
#define _SORT_H_
#include <vector>
#include <typeinfo>
#include <cmath>
#include <cstring>

namespace mysort {
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

	template<typename T>
		void radix_sort(std::vector<T>& v, uint32_t radix) {
			T max;
			max.key = 0;
			for (auto p : v) {
				if (max < p)
					max = p;
			}
			uint32_t digit_num = 1;
			uint64_t max_num = 1;
			// C++ stl doesn't have an arbitrary log base 
			while (max_num * radix < max.key) {
				max_num *= radix;
				digit_num++;
			}
			int count[radix] = {0,};
			std::vector<T> w(v.size());
			// counting sort
			for (int i = 0; i < digit_num; i++) {
				std::memset(count, 0, sizeof(count));
				// counting
				for (auto p : v) {
					int r = p.key / std::pow(radix, i);
					r %= radix;
					count[r]++;
				}
				// actual position from end
				for (int j = 1; j < radix; j++) 
					count[j] += count[j - 1];
				// 
				for (int j = v.size() - 1; j >= 0; j--) {
					int r = v[j].key / std::pow(radix, i);
					r %= radix;
					w[count[r] - 1] = v[j];
					count[r]--;
				}
				// update source v
				v = w;
			}

		}
	// radix_sort specialization for std::string type key
	template<> 
		void radix_sort<Entry<std::string>>(std::vector<Entry<std::string>>& v, uint32_t radix) {
			Entry<std::string> max;
			max.key = "";
			char r;
			for (auto p: v) {
				if (p.key.size() > max.key.size()) {
					max = p;
				}
			}
			int count[radix] = {0, };
			std::vector<Entry<std::string>> w(v.size());
			for (int i = 0; i < max.key.size(); i++) {
				std::memset(count, 0, sizeof(count));

				for (int j = 0; j < v.size(); j++) {
					if (i > v[j].key.size() - 1) 
						r = 0;
					else 
						r = v[j].key.at(i);

					count[r]++;
				}
				for (int j = 1; j < radix; j++)
					count[j] += count[j - 1];

				for (int j = v.size() - 1; j >= 0; j--) {
					if (i > v[j].key.size() - 1) 
						r = 0;
					else 
						r = v[j].key.at(i);

					w[count[r] - 1] = v[j];
					count[r]--;
				}
				v = w;
			}

		}
	template<typename T>
		void heapify(std::vector<T> &v, int32_t len, uint32_t cur)
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
				std::swap(v[cur], v[largest]);
				heapify(v, len, largest);
			}
		}

	template<typename T>
		void heap_sort(std::vector<T> &v)
		{
			uint32_t len = (uint32_t)v.size();
			/* build max heap */
			for (int32_t i = len / 2 - 1; i >= 0; i--) 
				heapify(v, len, i);

			/* heap sort */
			for (int32_t i = len - 1; i > 0 ; i--) {
				std::swap(v[0], v[i]);
				heapify(v, i, 0);
			}

		}

	template<typename T>
		uint32_t partition(std::vector<T> &v, uint32_t left, uint32_t right)
		{
			uint32_t last = left;

			for (uint32_t i = left + 1; i <= right; i++) {
				if (v[i] < v[left])
					std::swap(v[++last], v[i]);
			}

			return last;
		}

	template<typename T>
		void qsort(std::vector<T> &v, uint32_t left, uint32_t right)
		{
			uint32_t last; 
			if (left >= right)
				return;

			std::swap(v[left], v[left + (right - left) / 2]);
			last = partition(v, left, right);
			std::swap(v[left], v[last]);
			qsort(v, left, last); 
			qsort(v, last + 1, right);
		}

	template<typename T>
		void merge(std::vector<T> &v, int32_t left, int32_t mid, int32_t right)
		{
			std::vector<T> w(right - left + 1);

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
		void merge_sort(std::vector<T> &v, int32_t left, int32_t right)
		{
			if (left < right) {
				uint32_t mid = left + (right - left) / 2;
				merge_sort(v, left, mid);
				merge_sort(v, mid + 1, right);

				merge(v, left, mid, right);
			}
		}
}
#endif
