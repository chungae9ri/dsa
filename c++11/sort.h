#ifndef _SORT_H_
#define _SORT_H_
#include <vector>

namespace mysort {
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
