#include <iostream>
#include <vector>
#include <algorithm> // for shuffle
#include <random>

#include <quick_uf.hpp>

namespace quick_uf
{
void quick_uf::set_sz(int n)
{
	sz = n;
	id = {};

	for (int i = 0; i < sz; i++) {
		id.push_back(i);
	}
}

void quick_uf::union_set(int p, int q)
{
	if (id[p] == id[q]) {
		return;
	}

	if (id[p] < id[q]) {
		id[q] = id[p];
	} else {
		id[p] = id[q];
	}
}

int quick_uf::root(int p)
{
	int trace[sz] = {0};
	int trace_len = 0;
	int i = 0;

	while (id[p] != p) {
		trace[i++] = p;
		p = id[p];
	}

	trace_len = i;

	// path compression for flattening
	for (i = 0; i < trace_len; i++) {
		id[trace[i]] = p;
	}

	return p;
}

bool quick_uf::is_connected(int p, int q)
{
	return root(p) == root(q);
}

void percolation::initialize_cells(int w, int open_num)
{
	// 1 initialize cell vectors
	set_sz(w * w);
	width = w;
	start = {};
	end = {};

	// 2 initialize array as closed
	for (int i = 0; i < get_sz(); i++) {
		get_id_vec()[i] = 0;
	}

	// 3 fill a vector with all values 0..N-1
	std::vector<int> values(get_sz());
	for (int i = 0; i < get_sz(); ++i)
		values[i] = i;

	// 4 shuffle it randomly
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(values.begin(), values.end(), gen);

	// 5 take the first `n` numbers
	std::vector<int> result(values.begin(), values.begin() + open_num);

	// 6 set open for the random location cells
	for (int i = 0; i < result.size(); i++) {
		auto idx = result[i];
		// initialize (open) the random cells
		get_id_vec()[idx] = idx;
		// build start, end cells
		if (idx < width) {
			start.push_back(idx);
		} else if (idx > width * width - width) {
			end.push_back(idx);
		}
	}
}

void percolation::build_union_set(void)
{
	for (int i = 0; i < get_sz(); i++) {
		if (get_id_vec()[i] != 0) {
			if ((i % width != width - 1) && (get_id_vec()[i + 1] != 0)) {
				union_set(i, i + 1);
			}
			if ((i < (get_sz() - width)) && (get_id_vec()[i + width] != 0)) {
				union_set(i, i + width);
			}
		}
	}
}

void percolation::show_cells(void)
{
	for (int i = 0; i < get_sz(); i++) {
		std::cout << "idx[" << i << "]: " << get_id_vec()[i] << std::endl;
	}
	std::cout << "--------------\n";
}

bool percolation::is_percolated(void)
{
	build_union_set();

	for (auto i : start) {
		for (auto j : end) {
			if (is_connected(i, j)) {
				return true;
			}
		}
	}

	return false;
}
} // namespace quick_uf