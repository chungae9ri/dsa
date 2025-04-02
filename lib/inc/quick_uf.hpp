#include <memory>

#pragma once

namespace quick_uf
{
class quick_uf {
    private:
        int sz;
        std::unique_ptr<int []> id;
    public:
        quick_uf(int n);

        void union_set(int p, int q);

        int root(int p);

        bool is_connected(int p, int q);

        int get_id(int p) {
            return id.get()[p];
        };

        int get_sz() {
            return sz;
        };

        int *get_id_arr(void) {
            return static_cast<int *>(id.get());
        }
};

class percolation : public quick_uf {
    private:
        std::unique_ptr<int []> start;
        std::unique_ptr<int []> end;
    public:
        percolation(int sz): quick_uf(sz){};
        void initialize_cells(int open_num);
        bool is_percolated(void);
};
}