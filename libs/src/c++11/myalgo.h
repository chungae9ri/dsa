#include <iostream>
#include <vector>
#include <cmath>

namespace myalgo {
	template <typename T>
		class permute {
			public:
				void operator()(std::vector<T> v, int s, int e) {
					if (s == e) {
						for (auto p : v)
							std::cout << p;

						std::cout << "\n";
						return;
					}

					for (int i = s; i <= e; i++) {
						std::swap(v[s], v[i]);
						(*this)(v, s + 1, e);
						std::swap(v[s], v[i]);
					}

				}
		};

	template <typename T>
		class set {
			public:
				void operator() (std::vector<T> v) {
					int num = std::pow(2, v.size());
					
					for (int i = 0; i < num; i++) {
						if (i == 0) {
							std::cout << "{ }\n";
							continue;
						}
						int mask = 1;
						std::cout << "{";
						for (auto p: v) {
							if (i & mask)
								std::cout << p;
							mask <<= 1;
						}
						std::cout << "}\n";

					}
				}
		};
}

