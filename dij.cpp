#include <cstdlib>
#include <vector>
#include <iostream>
#include <set>
#include <functional>
#include <memory>
#include <chrono>

#define INF	0x7FFFFFFF;

enum class eSTATUS {
	UNSEEN,
	FRINGE,
	INTREE,
};


class vertex;
using VREF = std::reference_wrapper<vertex>;
using VSPTR = std::shared_ptr<vertex>;

class edge;
using EREF = std::reference_wrapper<edge>;
using ESPTR = std::shared_ptr<edge*>;

using IT = std::multiset<VREF>::iterator;
using ITPTR = std::multiset<VSPTR>::iterator;

class vertex {
	public:
		int idx;
		int dist;
		int weight;
		int par_idx;
		eSTATUS status;
		std::vector<VREF> nei;
		std::vector<VSPTR> pnei;
		vertex(int i):idx{i} {
			dist = INF;
			weight = std::rand() % 100 + 1;
			status = eSTATUS::UNSEEN;
			par_idx = -1;
		}

		~vertex() {
			//std::cout << "~vertex(" << idx <<")" << "\n";
			nei.clear();
			pnei.clear();
		}
};

class edge {
	public:
		std::vector<VREF> vref;
		int weight;
		edge(VREF v, VREF w) {
			//auto re = std::make_pair(v, w);
			vref.push_back(v);
			vref.push_back(w);
			weight = v.get().weight + w.get().weight;
		}
};

class graph {
	public:
		std::vector<vertex> vertices;
		std::vector<VSPTR> pvertices;
		std::vector<edge> edges;

		graph(int v_count, int n_count) {
			for (int i = 0; i < v_count; i++) {
				vertices.push_back(vertex(i));
				auto pv = new vertex(i);
				pv->weight = vertices[i].weight;
				pvertices.push_back(std::make_shared<vertex>(*pv));
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
						vertices[nei_idx].nei.push_back(std::ref(v));
						pvertices[nei_idx]->pnei.push_back(pvertices[v.idx]);
						//
						auto e = edge(std::ref(v), std::ref(vertices[nei_idx]));
						edges.push_back(e);
					}
				}
			}

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
		}
		~graph() {
		}
};

class vptrComp {
	public:
		bool operator()(VSPTR vptr, VSPTR wptr) {
			return (vptr->dist < wptr->dist);
		}
};

class dijkstra_ptr{
	public:
		std::vector<VSPTR> mst;
		std::multiset<VSPTR, vptrComp> fringeSet;

		void operator() (graph &g, int sIdx, int tIdx) {
			auto ps = g.pvertices[sIdx];
			auto pt = g.pvertices[tIdx];
			ps->dist = 0;
			mst.push_back(ps);

			for (auto& pv : ps->pnei) {
				pv->dist = ps->weight + pv->weight;
				pv->par_idx = ps->idx;
				pv->status = eSTATUS::FRINGE;
				fringeSet.insert(pv);
			}

			while (!fringeSet.empty()) {
				auto itr = fringeSet.begin();
				auto& curvptr = g.pvertices[(*itr)->idx];
				curvptr->status = eSTATUS::INTREE;
				fringeSet.erase(itr);
				mst.push_back(curvptr);
				for (auto& pv : curvptr->pnei) {
					if (pv->status == eSTATUS::UNSEEN) {
						pv->dist = curvptr->dist + (curvptr->weight + pv->weight);
						pv->par_idx = curvptr->idx;
						pv->status = eSTATUS::FRINGE;
						fringeSet.insert(pv);
					} else if (pv->status == eSTATUS::FRINGE) {
						int tempdist = curvptr->dist + (curvptr->weight + pv->weight);
						if (tempdist < pv->dist) {
							std::pair<ITPTR, ITPTR> ret = fringeSet.equal_range(pv);
							for (auto p = ret.first; p != ret.second; p++) {
								if ((*p)->idx == pv->idx) {
									fringeSet.erase(p);
									break;
								}
							}
							pv->dist = tempdist;
							pv->par_idx = curvptr->idx;
							fringeSet.insert(pv);
						}
					}
				}
			}

			std::cout << "shortest path with shared_ptr " << "\n";
			for (auto& pv : mst) {
				if (pv->idx == tIdx) {
					std::cout << pv->idx << "(" << pv->dist << ")";
					auto& pw = g.pvertices[pv->par_idx];
					while (pw->idx != ps->idx) {
						std::cout << " <- " << pw->idx << "(" << pw->dist << ")";
						pw = g.pvertices[pw->par_idx];
					}
					std::cout << " <- " << ps->idx << "\n";
				}
			}
		}
};


class vertexComp{
	public:
		bool operator()(VREF v, VREF w) {
			return (v.get().dist < w.get().dist);
		}
};

class dijkstra_ref {
	public:
		std::vector<VREF> mst;
		std::multiset<VREF, vertexComp> fringeSet;

		void operator()(graph &g, int sIdx, int tIdx) {
			VREF s = std::ref(g.vertices[sIdx]);
			VREF t = std::ref(g.vertices[tIdx]);
			s.get().dist = 0;
			mst.push_back(s);

			for (auto& v : s.get().nei) {
				v.get().dist = s.get().weight + v.get().weight;
				v.get().status = eSTATUS::FRINGE;
				v.get().par_idx = s.get().idx;
				fringeSet.insert(v);
			}

			while(!fringeSet.empty()) {
				auto vItr = fringeSet.begin();
				auto& curv = g.vertices[(*vItr).get().idx];
				fringeSet.erase(vItr);
				curv.status = eSTATUS::INTREE;
				mst.push_back(std::ref(curv));
				for (auto& v : curv.nei) {
					if (v.get().status == eSTATUS::UNSEEN) {
						v.get().dist = curv.dist + (curv.weight + v.get().weight);
						v.get().status = eSTATUS::FRINGE;
						v.get().par_idx = curv.idx;
						fringeSet.insert(v);
					} else if (v.get().status == eSTATUS::FRINGE) {
						int tempdist = curv.dist + (curv.weight + v.get().weight);
						if (tempdist < v.get().dist) {
							std::pair<IT, IT> ret = fringeSet.equal_range(v);
							for (auto w = ret.first; w != ret.second; w++) {
								if ((*w).get().idx == v.get().idx) {
									fringeSet.erase(w);
									break;
								}
							}
							v.get().dist = tempdist;
							v.get().par_idx = curv.idx;
							fringeSet.insert(v);
						}
					}
				}
			}

			std::cout << "shortest path with reference_wrapper" << "\n";
			for (auto& v : mst) {
				if (v.get().idx == tIdx) {
					std::cout << v.get().idx << "(" << v.get().dist << ")";
					auto& w = g.vertices[v.get().par_idx];
					while (w.idx != s.get().idx) {
						std::cout << " <- " << w.idx << "(" << w.dist << ")";
						w = g.vertices[w.par_idx];
					}
					std::cout << " <- " << s.get().idx << "\n";
				}
			}
		}
};

int main()
{
	int vNum = 10, nNum = 2, sIdx = 0, tIdx = 4;
	std::cout << "input vertex number: " ;
	std::cin >> vNum;
	std::cout << '\n';
	std::cout << "input seed neighbor number: " ;
	std::cin >> nNum;
	std::cout << '\n';
	std::cout << "input src vertex idx: ";
	std::cin >> sIdx;
	std::cout << '\n';
	std::cout << "input tgt vertex idx: ";
	std::cin >> tIdx;
	std::cout << '\n';

	graph g(vNum, nNum);
	std::cout << "\ngraph has " << g.vertices.size() << " vertices, " << g.edges.size() << " edges" << std::endl;

	dijkstra_ref dij_ref;
	auto start1 = std::chrono::high_resolution_clock::now();
	dij_ref(g, sIdx, tIdx);
	auto end1 = std::chrono::high_resolution_clock::now();
	auto elapse1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
	std::cout << "reference_wrapper imple for dijkstra takes " << elapse1.count() <<"msec\n"; 
	std::cout << "\n";

	dijkstra_ptr dij_ptr;
	auto start2 = std::chrono::high_resolution_clock::now();
	dij_ptr(g, sIdx, tIdx);
	auto end2 = std::chrono::high_resolution_clock::now();
	auto elapse2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
	std::cout << "shared_ptr imple for dijkstra takes " << elapse2.count() <<"msec\n"; 

	return 0;
}
