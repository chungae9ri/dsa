#include <iostream>
#include <quick_uf.hpp>
#include <vector>
#include <algorithm> // for shuffle
#include <random>

namespace quick_uf
{
    quick_uf::quick_uf(int n): sz(n)
    {
        id = std::make_unique<int[]>(sz);
        for (int i = 0; i < sz; i++) {
            id[i] = i;
        }
    }

    void quick_uf::union_set(int p, int q)
    {
        if (id.get()[p] == id.get()[q]) {
            return;
        }

        id.get()[q] = id.get()[p];
    }

    int quick_uf::root(int p)
    {
        int trace[sz] = {0};
        int trace_len = 0;
        int i = 0;

        while (id.get()[p] != p) {
            trace[i++] = p;
            p = id.get()[p];
        }

        trace_len = i;

        // path compression for flattening
        for (i = 0; i < trace_len; i++) {
            id.get()[trace[i]] = p;
        }

        return p;
    }

    bool quick_uf::is_connected(int p, int q)
    {
        return root(p) == root(q);
    }

    void percolation::initialize_cells(int open_num)
    {
        // 0. Initialize array as closed
        for (int i = 0; i < get_sz(); i++) {
            get_id_arr()[i] = 0;
        }

        // 1. Fill a vector with all values 0..N-1
        std::vector<int> values(get_sz());
        for (int i = 0; i < get_sz(); ++i)
            values[i] = i;

        // 2. Shuffle it randomly
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(values.begin(), values.end(), gen);

        // 3. Take the first `n` numbers
        std::vector<int> result(values.begin(), values.begin() + open_num);

        // 4. Set open for the random location cells
        for (int i = 0; i < open_num; i++) {
            get_id_arr()[result[i]] = 1;
        }

        for (int i; i < get_sz(); i++) {
            std::cout << "idx[" << i << "]: " << get_id_arr()[i] << std::endl;
        }
    }

    bool percolation::is_percolated(void)
    {
        return true;
    }
}