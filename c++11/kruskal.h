#include <iostream>
#include <chrono>
#include <set>
#include "graphgen.h"
#include "sort.h"

namespace kruskal {
	class kruskal_vertex;
	using KVREF = std::reference_wrapper<kruskal_vertex>;
	// neighbor vertex of Kruskal's mst tree, should be unique set
	// used for finding path s-t in the mst 
	class compVertexKey {
		public:
			bool operator()(const KVREF& v, const KVREF& w);
	};

	class kruskal_vertex: public mygraph::vertex<kruskal_vertex> {
		public:
			// for set (findset, makeset, unionset) operation
			kruskal_vertex* pParv;
			int rank;
			// should be std::set for unique entry
			std::set<KVREF, compVertexKey> mst_nei; 
			bool bVisited;
			kruskal_vertex(int i): vertex{i} {
				bVisited = false;
				pParv = nullptr;
				rank = 1;
			}
	};

	class kruskal_ops {
		public:
			std::vector<mygraph::edge<kruskal_vertex>> mst;
			void operator()(mygraph::graph<kruskal_vertex>& g, int sIdx, int tIdx); 
			bool kruskal_dfs(mygraph::graph<kruskal_vertex>& g, int sIdx, int tIdx);
			void makeset(kruskal_vertex& v);
			KVREF findset(const KVREF& v);
			void unionset(KVREF& v, KVREF& w);
	};

	bool compVertexKey::operator()(const KVREF& v, const KVREF& w) 
	{
		return (v.get().idx < w.get().idx);
	}


	void kruskal_ops::makeset(kruskal_vertex& v) 
	{
		v.rank = 1;
		v.pParv = nullptr;
	}

	KVREF kruskal_ops::findset(const KVREF& v) 
	{
		if (v.get().pParv) {
			kruskal_vertex* pv = v.get().pParv;
			while(pv->pParv) {
				pv = pv->pParv;
			}	
			return std::ref(*pv);
		} else 
			return v;
	}

	void kruskal_ops::unionset(KVREF& v, KVREF& w) 
	{
		if (v.get().rank > w.get().rank) {
			w.get().pParv = &(v.get());
		} else if (v.get().rank < w.get().rank) {
			v.get().pParv = &(w.get());
		} else {
			v.get().pParv = &(w.get());
			w.get().rank++; // worst case lgN
		}
	}

	// DFS for tIdx and reverse back to sIdx
	bool kruskal_ops::kruskal_dfs(mygraph::graph<kruskal_vertex>& g, int sIdx, int tIdx)
	{
		for (auto& v : g.vertices[sIdx].mst_nei) {
			if (v.get().idx == tIdx) {
				std::cout << v.get().idx << " <- ";
				return true;
			} else if (!v.get().bVisited) {
				v.get().bVisited = true;
				auto bFound = kruskal_dfs(g, v.get().idx, tIdx);
				if (bFound) {
					std::cout << v.get().idx << " <- ";
					return true;
				}
			}
		}

		return false;
	}

	void kruskal_ops::operator()(mygraph::graph<kruskal_vertex>& g, int sIdx, int tIdx) 
	{
		mysort::qsort(g.edges, 0, g.edges.size() - 1);

#if 0
		std::cout << "sorted edges: \n";
		for (auto& e: g.edges) {
			std::cout << "v: " << e.vref[0].get().idx << ", w: " << e.vref[1].get().idx << "\n";
		}
#endif

		for (auto& v : g.vertices)
			makeset(v);

		for (auto& e : g.edges) {
			auto v = e.vref[0];
			auto w = e.vref[1];
			auto s1 = findset(v);
			auto s2 = findset(w);
			if (s1.get().idx != s2.get().idx) {
				unionset(s1, s2);
				mst.push_back(e);
				v.get().mst_nei.insert(w);
				w.get().mst_nei.insert(v);
				/*std::cout << "v: " << v.get().idx << ", w: " << w.get().idx << "\n";*/
			}
		}

#if 0
		std::cout << "mst_nei:\n";
		for (auto& e: g.vertices) {
			std::cout << "curv: " << e.idx << ", : ";
			for (auto& p : e.mst_nei)
				std::cout << "mst_nei: " << p.get().idx << ", ";

			std::cout << "\n";
		}
#endif


		std::cout << "Kruskal's mst edges: \n";
		for (auto& e: mst) {
			std::cout << "v: " << e.vref[0].get().idx << ", w: " << e.vref[1].get().idx << "\n";
		}

		std::cout << "Kruskal path in the MST:\n";
		g.vertices[sIdx].bVisited = true;
		auto bFound = kruskal_dfs(g, sIdx, tIdx);
		if (bFound)
			std::cout << g.vertices[sIdx].idx << "\n";
		else 
			std::cout << "Path not found\n";
	}
}
