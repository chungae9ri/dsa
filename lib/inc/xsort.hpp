#include <cstdint>
#include <vector>

#pragma once

namespace xsort
{

template <class T> class entry
{
	T val;

      public:
	entry() = default;
	entry(const T &v) : val{v} {}
	entry(const entry &e) : val{e.val} {}
	entry(entry &&e) noexcept : val{std::move(e.val)} {}
	entry &operator=(const entry &e)
	{
		if (this != &e) {
			this->val = e.val;
		}
		return *this;
	}

	entry &operator=(entry &&e) noexcept
	{
		if (this != &e) {
			val = std::move(e.val);
		}
		return *this;
	}

	bool operator<(const entry &o) { return (this->val < o.val); }

	bool operator>(const entry &o) { return (this->val > o.val); }

	bool operator<(const entry &o) const { return (this->val < o.val); }

	bool operator>(const entry &o) const { return (this->val > o.val); }

	bool operator==(const entry &o) { return (this->val == o.val); }
};

template <class T> static uint32_t partition(std::vector<entry<T>> &v, uint32_t l, uint32_t r)
{
	uint32_t last = l;

	for (uint32_t i = l + 1; i <= r; i++) {
		if (v[i] < v[l])
			std::swap(v[i], v[++last]);
	}

	return last;
}

template <class T> void xqsort(std::vector<T> &v, uint32_t l, uint32_t r)
{
	uint32_t last;

	if (l >= r)
		return;

	last = xsort::partition(v, l, r);
	std::swap(v[l], v[last]);
	xsort::xqsort(v, l, last);
	xsort::xqsort(v, last + 1, r);
}

} // namespace xsort