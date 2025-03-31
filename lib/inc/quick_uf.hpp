#include <memory>

#pragma once

namespace quick_uf
{
class quick_uf {
    private:
        std::unique_ptr<int []> id;
        int sz;
    public:
        quick_uf(int n);
        void union_set(int p, int q);
        int root(int p);
        bool is_connected(int p, int q);
        int get_id(int p);
};
}