#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <chrono>
#include <map>
#include <stack>
#include <functional>

using namespace std;
/* Fibonarcci with memo */
#define _FIB_		1
/* grid traveller with memo */
#define _GRID_TRAV_	0
#define _MOV_TOWER_	0
#define _STRING_PERM_	0
#define _ADD_PAREN_	0
#define _N_CENTS_	0
/* check cycle in directed graph */
#define _CHK_CYCLE_	0

int main()
{
#if _FIB_
	class fib {
		public:
			uint64_t operator() (int n, std::map<int, uint64_t> &memo) {
				if (memo.find(n) != memo.end())
					return memo[n];

				if (n <= 2) return 1;

				uint64_t f = ((*this)(n - 1, memo) + (*this)(n - 2, memo));
				memo[n] = f;
				return f;
			}
	};

	std::map<int, uint64_t> memo;
	fib fi;
	int num;
	std::cout << "input fib num: ";
	std::cin >> num;
	auto start = std::chrono::high_resolution_clock::now();
	uint64_t f = fi(num, memo);
	auto end = std::chrono::high_resolution_clock::now();
	auto elapse = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "fib(" << num << ") is " << f << ", takes "<< elapse.count() << " usec\n";
#endif

#if _GRID_TRAV_
	class gridtrav {
		public:
			uint64_t operator() (int i, int j, std::map<std::pair<int, int>, uint64_t> &memo) {
				if (i == 0 && j == 0) return 1;
				if (i < 0 || j < 0) return 0;

				if (memo.find(std::make_pair(i, j)) != memo.end())
					return memo[std::make_pair(i, j)];

				uint64_t cnt = (*this)(i - 1, j, memo) + (*this)(1, j - 1, memo);

				memo[std::make_pair(i, j)] = cnt;
				return cnt;
			}
	};

	gridtrav gt;
	std::map<std::pair<int, int>, uint64_t> memo;
	int x, y;
	std::cout << "input grid dim(x, y): \n" ;
	std::cin >> x >> y; 
	auto start = std::chrono::high_resolution_clock::now();
	uint64_t g = gt(x - 1, y - 1, memo);
	auto end = std::chrono::high_resolution_clock::now();
	auto elapse = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "ways to gridtravel(" << x << ", " << y  << ") is " << g << ", takes "<< elapse.count() << " usec\n";
#endif

#if _MOV_TOWER_
	class Tower {
		public:
			std::stack<int> disks;
			int index;
			Tower(int i) {
				index = i;
			}
			void add (int d) {
				if (!disks.empty() && disks.top() <= d) {
					std::cout << "error placing disk: " << d << "\n";
				} else {
					disks.push(d);
				}
			}
			void movetoTop(Tower& t) {
				int top = disks.top();
				t.add(top);
				disks.pop();
			}
			void moveDisks(int n, Tower& dest, Tower& buff) {
				if (n > 0) {
					moveDisks(n - 1, buff, dest);
					movetoTop(dest);
					buff.moveDisks(n - 1, dest, *this);
				}
			}
	};

	int n = 10;
	std::vector<Tower> towers;
	Tower t1(1), t2(2), t3(3);
	towers.push_back(t1);
	towers.push_back(t2);
	towers.push_back(t3);

	for (int i = n - 1; i >= 0; i--) {
		towers[0].add(i);
	}

	towers[0].moveDisks(n, towers[2], towers[1]);

	while (!towers[2].disks.empty()) {
		int d = towers[2].disks.top();
		std::cout << d << ", " ;
		towers[2].disks.pop();
	}
	std::cout << "\n";

#endif

#if _STRING_PERM_
	class cpermute {
		public:
			std::vector<std::string> operator()(std::string s) {
				std::vector<std::string> vs;
				std::vector<std::string> vs2;

				if (s.size() == 1) {
					vs.push_back(s);
					return vs;
				}

				vs = (*this)(s.substr(0, s.size() - 1));
				char c = s.at(s.size() - 1);
				for (auto p : vs) {
					for (int i = 0; i <= p.size(); i++) {
						auto t = p;
						t.insert(i, 1, c); 
						vs2.push_back(t);
					}
				}
				return vs2;
			}
	};
	std::vector<std::string> vs;
	std::string str;
	std::cout << "input string: " ;
	std::cin >> str;
	cpermute perm;
	vs = perm(str);
	for (auto p: vs) {
		std::cout << p << "\n";
	}
#endif

#if _ADD_PAREN_
	class addparen {
		public:
			void operator()(std::vector<std::string>& l, int leftrem, int rightrem, std::string str, int count) {
				if (leftrem < 0 || rightrem < leftrem) return;
				if (leftrem == 0 && rightrem == 0) {
					l.push_back(str);
				} else {
					if (leftrem > 0) {
						str.replace(count, 1, 1, '(');
						(*this)(l, leftrem - 1, rightrem, str, count + 1);
					} 
					
					if (rightrem > leftrem) {
						str.replace(count, 1, 1, ')');
						(*this)(l, leftrem, rightrem - 1, str, count + 1);
					}
				}
			}
	};
	int n = 0;
	std::vector<std::string> vs;
	std::string str;
	std::cout<< "input paren number: ";
	std::cin >> n;
	addparen paren;
	paren(vs, n, n, str, 0);
	for (auto p : vs) {
		std::cout << p << ", ";
	}
	std::cout << "\n";
#endif

#if _N_CENTS_
	class ncents{
		public:
			uint64_t operator()(int amount, std::vector<int> denoms, int idx, std::map<std::pair<int, int>, int>& ways_map) {
				if (ways_map.find(std::make_pair(amount, idx)) != ways_map.end())
					return ways_map[std::make_pair(amount, idx)];

				if (idx >= denoms.size() - 1)
					return 1;
				int denom_amt = denoms[idx];
				int ways = 0;
				for (int i = 0; denom_amt * i <= amount; i++) {
					int amt_remaining = amount - denom_amt * i;
					ways += (*this)(amt_remaining, denoms, idx + 1, ways_map);
				}
				ways_map[std::make_pair(amount, idx)] = ways;
				return ways;
			}
	};

	int amount;
	std::vector<int> denoms = {25, 10, 5, 1};
	std::map<std::pair<int, int>, int> ways_map;
	std::cout << "input amount: ";
	std::cin >> amount;
	ncents ncents_ways;
	int ways = ncents_ways(amount, denoms, 0, ways_map);
	std::cout << "ways to build " << amount << " cents: " << ways << "\n";
#endif

#if _CHK_CYCLE_
	class vertex {
		public:
			int key;
			bool visited;
			std::vector<std::reference_wrapper<vertex>> n;
			vertex(int i): key{i},visited{false} {}
	};
	class graph {
		public:
			std::vector<std::reference_wrapper<vertex>> v;
	};

	graph g;
	vertex v_1(1), v_2(2), v_3(3), v_0(0), v_4(4), v_5(5);
	std::reference_wrapper<vertex> v1(v_1), v2(v_2), v3(v_3), v0(v_0), v4(v_4), v5(v_5);
	v0.get().n.push_back(v2);
	v0.get().n.push_back(v1);
	v1.get().n.push_back(v2);
	v1.get().n.push_back(v4);
	v1.get().n.push_back(v5);
	v2.get().n.push_back(v0);
	v2.get().n.push_back(v3);
	v3.get().n.push_back(v3);
	v3.get().n.push_back(v4);
	v4.get().n.push_back(v5);

	g.v.push_back(v0);
	g.v.push_back(v1);
	g.v.push_back(v2);
	g.v.push_back(v3);
	g.v.push_back(v4);
	g.v.push_back(v5);

	class findcyc {
		public:
			bool operator() (graph &g) {
				std::map<int, bool> s;
				for (auto& v : g.v) {
					if (iscycle(v, s) == true) {
						std::cout << "cycle in vertex: " << v.get().key << "\n";
					}
				}
			}

			bool iscycle(std::reference_wrapper<vertex>& v, std::map<int, bool> &s) {

				for (auto& w : v.get().n) {
					if (s.find(w.get().key) != s.end())
						return true;

					s[w.get().key] = true;
					bool b = iscycle(w, s);
					if (b) {
						return true;
					} 
					s.clear();
				}
				return false;
			}
	};

	findcyc fc;
	fc(g);
#endif
	return 0;
}
