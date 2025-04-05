#include <memory>
#include <vector>

#pragma once

namespace quick_uf
{
class quick_uf
{
      private:
	int sz;
	std::vector<int> id;

      public:
	void union_set(int p, int q);
	int root(int p);
	bool is_connected(int p, int q);
	int get_id(int p) { return id[p]; };
	void set_sz(int sz);
	int get_sz() { return sz; };
	std::vector<int> &get_id_vec(void) { return id; }
};

class percolation : public quick_uf
{
      private:
	int width;
	std::vector<int> start;
	std::vector<int> end;
	void build_union_set(void);

      public:
	void initialize_cells(int w, int open_num);
	bool is_percolated(void);
	void show_cells(void);
};
} // namespace quick_uf