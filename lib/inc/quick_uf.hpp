#include <memory>
#include <vector>

#pragma once

namespace quick_uf
{
class quick_uf {
    private:
        int sz;
        std::vector<int> id;
    public:
        quick_uf(int n);

        void union_set(int p, int q);

        int root(int p);

        virtual bool is_connected(int p, int q);

        int get_id(int p) {
            return id[p];
        };

        int get_sz() {
            return sz;
        };

        std::vector<int> &get_id_vec(void) {
            return id;
        }
};

class percolation : public quick_uf {
    private:
        int width;
        std::vector<int> start;
        std::vector<int> end;
    public:
        percolation(int w): quick_uf(w * w), width(w){};
        void initialize_cells(int open_num);
        bool is_connected(int p, int q) override;
        bool is_percolated(void);
        void show_cells(void);
        void build_union_set(void);
};
}