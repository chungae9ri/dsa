#ifndef _GRAPHGEN_H_
#define _GRAPHGEN_H_
#include <vector>
#include <set>
#include <functional>
#include <memory>
#include <iostream>

#define _PRINT_GRAPH_	0

namespace mygraph {
	template <typename T>
		class vertex { 
			public: 
				int idx;
				int weight;

				// neighbor vertices
				std::vector<std::reference_wrapper<T>> nei;
				std::vector<std::shared_ptr<T>> pnei;
				std::vector<T*> pnnei;

				vertex(int i):idx{i} {
					weight = std::rand() % 100 + 1;
				}

				~vertex() {
				}
		};

	template <typename T>
		class edge {
			public:
				std::vector<std::reference_wrapper<T>> vref;
				int weight;
				edge(std::reference_wrapper<T> v, std::reference_wrapper<T> w) {
					vref.push_back(v);
					vref.push_back(w);
					weight = v.get().weight + w.get().weight;
				}

				/* for the comparison of sort  */
				bool operator<(const edge<T>& o) {
					return (this->weight < o.weight);
				}

				bool operator>(const edge<T>& o) {
					return (this->weight > o.weight);
				}

				bool operator==(const edge<T>& o) {
					return (this->weight == o.weight);
				}
		};

	template <typename T>
		class graph {
			public:
				std::vector<T> vertices;
				std::vector<std::shared_ptr<T>> pvertices;
				std::vector<T*> pnvertices;
				std::vector<edge<T>> edges;

				graph(int v_count, int n_count) {
					for (int i = 0; i < v_count; i++) {
						vertices.push_back(T(i));
						auto pv = new T(i);
						pv->weight = vertices[i].weight;
						pvertices.push_back(std::make_shared<T>(*pv));
						auto pnv = new T(i);
						pnv->weight = vertices[i].weight;
						pnvertices.push_back(pnv);
					}

					for (auto& v: vertices) {
						int nei_count = rand() % n_count + 1;
						for (int i = 0; i < nei_count; i++) {
							int nei_idx = rand() % v_count;
							if (nei_idx == v.idx) {
								continue;
							}

							bool alreadyin = false;
							for (auto& n: v.nei) {
								if (n.get().idx == nei_idx) {
									alreadyin = true;
									break;
								}
							}
							if (!alreadyin) {
								v.nei.push_back(std::ref(vertices[nei_idx]));
								pvertices[v.idx]->pnei.push_back(pvertices[nei_idx]);
								pnvertices[v.idx]->pnnei.push_back(pnvertices[nei_idx]);
								vertices[nei_idx].nei.push_back(std::ref(v));
								pvertices[nei_idx]->pnei.push_back(pvertices[v.idx]);
								pnvertices[nei_idx]->pnnei.push_back(pnvertices[v.idx]);
								//
								auto e = edge<T>(std::ref(vertices[v.idx]), std::ref(vertices[nei_idx]));
								edges.push_back(e);
							}
						}
					}
#if _PRINT_GRAPH_
					std::cout << "\n vertices using std::reference_wrapper\n";
					for (auto& v : vertices) {
						std::cout << v.idx << " has " ; 
						for (auto &w : v.nei) {
							std::cout << w.get().idx << "(" << v.weight + w.get().weight << ")" << ", ";
						}
						std::cout << "\n";
					}
					std::cout << "\n vertices using std::shared_ptr\n";
					for (auto& pv : pvertices) {
						std::cout << pv->idx << " has " ;
						for (auto& pw: pv->pnei) {
							std::cout << pw->idx << "(" << pv->weight + pw->weight << ")" << ", ";
						}
						std::cout << "\n";
					}
					std::cout << "\n vertices using naked ptr\n";
					for (auto& pv : pnvertices) {
						std::cout << pv->idx << " has " ;
						for (auto& pw: pv->pnnei) {
							std::cout << pw->idx << "(" << pv->weight + pw->weight << ")" << ", ";
						}
						std::cout << "\n";
					}
#endif
				}
				~graph() {
					for (auto pv : pnvertices)
						delete pv;
				}
		};
}
#endif
