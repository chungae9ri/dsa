#include <quick_uf.hpp>
#include <vector>
#include <array>

namespace quick_uf
{
    quick_uf::quick_uf(int n): sz(n)
    {
        id.reset(new int(sz));
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

    int quick_uf::get_id(int p)
    {
        return id.get()[p];
    }
}