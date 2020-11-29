#include <iostream>
#include <chrono>
#include <set>
#include "graphgen.h"
#include "sort.h"

#define INF	0x7FFFFFFF

namespace dijkstra {
	enum class eSTATUS {
		UNSEEN,
		FRINGE,
		INTREE,
	};


	class dijkstra_vertex;
	using DVREF = std::reference_wrapper<dijkstra_vertex>;
	using IT = std::multiset<std::reference_wrapper<dijkstra_vertex>>::iterator;
	using ITPTR = std::multiset<std::shared_ptr<dijkstra_vertex>>::iterator;
	using ITNPTR = std::multiset<dijkstra_vertex*>::iterator;

	class dijkstra_vertex: public mygraph::vertex<dijkstra_vertex> {
		public:
			// for dijkstra
			int pred_idx; // mst parent of Dijkstra
			eSTATUS status;
			int dist;
			dijkstra_vertex(int i): vertex{i} {
				dist = INF;
				status = eSTATUS::UNSEEN;
				pred_idx = -1;
			}
	};

	class vptrnComp{
		public:
			bool operator()(dijkstra_vertex *v, dijkstra_vertex *w);
	};

	class dijkstra_nkd_ptr {
		public:
			std::multiset<dijkstra_vertex*, vptrnComp> fringeSet;
			void operator()(mygraph::graph<dijkstra_vertex>& g, int sIdx, int tIdx);
	};

	class vptrComp {
		public:
			bool operator()(std::shared_ptr<dijkstra_vertex> vptr, std::shared_ptr<dijkstra_vertex> wptr);
	};

	class dijkstra_ptr{
		public:
			std::multiset<std::shared_ptr<dijkstra_vertex>, vptrComp> fringeSet;
			void operator() (mygraph::graph<dijkstra_vertex>& g, int sIdx, int tIdx);
	};

	class vertexComp{
		public:
			bool operator()(DVREF v, DVREF w);
	};

	class dijkstra_ref {
		public:
			std::multiset<DVREF, vertexComp> fringeSet;
			void operator()(mygraph::graph<dijkstra_vertex>& g, int sIdx, int tIdx);
	};

	bool vptrnComp::operator()(dijkstra_vertex *v, dijkstra_vertex *w) 
	{
		return (v->dist < w->dist);
	}

	bool vptrComp::operator()(std::shared_ptr<dijkstra_vertex> vptr, std::shared_ptr<dijkstra_vertex> wptr) 
	{
		return (vptr->dist < wptr->dist);
	}

	bool vertexComp::operator()(DVREF v, DVREF w) 
	{
		return (v.get().dist < w.get().dist);
	}

	void dijkstra_nkd_ptr::operator()(mygraph::graph<dijkstra_vertex>& g, int sIdx, int tIdx) 
	{
		auto ps = g.pnvertices[sIdx];
		auto pt = g.pnvertices[tIdx];
		ps->dist = 0;
		for (auto pv : ps->pnnei) {
			pv->dist = ps->dist + ps->weight + pv->weight;
			pv->pred_idx = ps->idx;
			pv->status = eSTATUS::FRINGE;
			fringeSet.insert(pv);
		}
		while(!fringeSet.empty()) {
			auto itr = fringeSet.begin();
			/*auto curpv = (*itr);*/
			auto curpv = g.pnvertices[(*itr)->idx];
			fringeSet.erase(itr);
			curpv->status = eSTATUS::INTREE;
			for (auto pv : curpv->pnnei) {
				if (pv->status == eSTATUS::UNSEEN) {
					pv->dist = curpv->dist + (curpv->weight + pv->weight);
					pv->pred_idx = curpv->idx;
					pv->status = eSTATUS::FRINGE;
					fringeSet.insert(pv);
				} else if (pv->status == eSTATUS::FRINGE) {
					auto temp = curpv->dist + (curpv->weight + pv->weight);
					if (pv->dist > temp) {
						std::pair<ITNPTR, ITNPTR> ret = fringeSet.equal_range(pv);
						for (auto t = ret.first; t != ret.second; t++) {
							if ((*t)->idx == pv->idx) {
								fringeSet.erase(t);
								break;
							}
						}
						pv->dist = temp;
						pv->pred_idx = curpv->idx;
						fringeSet.insert(pv);
					}
				}
			}
		}

		std::cout << "Dijkstra shortest path with naked ptr" << "\n";
		auto& pv = g.pnvertices[tIdx];
		std::cout << pv->idx << "(" << pv->dist << ")";
		auto pw = g.pnvertices[pv->pred_idx];
		while (pw->idx != ps->idx) {
			std::cout << " <- " << pw->idx << "(" << pw->dist << ")";
			pw = g.pnvertices[pw->pred_idx];
		}
		std::cout << " <- " << ps->idx << "\n";
	}

	void dijkstra_ptr::operator() (mygraph::graph<dijkstra_vertex>& g, int sIdx, int tIdx) 
	{
		auto ps = g.pvertices[sIdx];
		auto pt = g.pvertices[tIdx];
		ps->dist = 0;

		for (auto& pv : ps->pnei) {
			pv->dist = ps->weight + pv->weight;
			pv->pred_idx = ps->idx;
			pv->status = eSTATUS::FRINGE;
			fringeSet.insert(pv);
		}

		while (!fringeSet.empty()) {
			auto itr = fringeSet.begin();
			auto& curvptr = g.pvertices[(*itr)->idx];
			curvptr->status = eSTATUS::INTREE;
			fringeSet.erase(itr);
			for (auto& pv : curvptr->pnei) {
				if (pv->status == eSTATUS::UNSEEN) {
					pv->dist = curvptr->dist + (curvptr->weight + pv->weight);
					pv->pred_idx = curvptr->idx;
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
						pv->pred_idx = curvptr->idx;
						fringeSet.insert(pv);
					}
				}
			}
		}

		std::cout << "Dijkstra shortest path with shared_ptr " << "\n";
		auto& pv = g.pvertices[tIdx];
		std::cout << pv->idx << "(" << pv->dist << ")";
		auto pw = g.pvertices[pv->pred_idx];
		while (pw->idx != ps->idx) {
			std::cout << " <- " << pw->idx << "(" << pw->dist << ")";
			pw = g.pvertices[pw->pred_idx];
		}
		std::cout << " <- " << ps->idx << "\n";
	}

	void dijkstra_ref::operator()(mygraph::graph<dijkstra_vertex>& g, int sIdx, int tIdx) 
	{
		DVREF s = std::ref(g.vertices[sIdx]);
		DVREF t = std::ref(g.vertices[tIdx]);
		s.get().dist = 0;

		for (auto& v : s.get().nei) {
			v.get().dist = s.get().weight + v.get().weight;
			v.get().status = eSTATUS::FRINGE;
			v.get().pred_idx = s.get().idx;
			fringeSet.insert(v);
		}

		while(!fringeSet.empty()) {
			auto vItr = fringeSet.begin();
			auto& curv = g.vertices[(*vItr).get().idx];
			fringeSet.erase(vItr);
			curv.status = eSTATUS::INTREE;
			for (auto& v : curv.nei) {
				if (v.get().status == eSTATUS::UNSEEN) {
					v.get().dist = curv.dist + (curv.weight + v.get().weight);
					v.get().status = eSTATUS::FRINGE;
					v.get().pred_idx = curv.idx;
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
						v.get().pred_idx = curv.idx;
						fringeSet.insert(v);
					}
				}
			}
		}

		std::cout << "Dijkstra shortest path with reference_wrapper" << "\n";
		auto& v = g.vertices[tIdx];
		std::cout << v.idx << "(" << v.dist << ")";
		auto w = g.vertices[v.pred_idx];
		while (w.idx != s.get().idx) {
			std::cout << " <- " << w.idx << "(" << w.dist << ")";
			w = g.vertices[w.pred_idx];
		}
		std::cout << " <- " << s.get().idx << "\n";
	}
}
