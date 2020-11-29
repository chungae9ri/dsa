#include "dijkstra.h"
#include "kruskal.h"

// performance test for reference_wrapper, shared_ptr and naked pointer
// naked pointer is always winner.
// reference_wrapper is a little bit slower than naked pointer
// shared_ptr takes much longer than other, almost two times than naked pointer
// vertex 100000, neighbor 20 (random), src 0, tgt 99999
// naked pointer takes 1623208usec
// reference_wrapper takes 1858301usec
// shared_ptr takes 2759880usec

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

	std::cout << "graph generation for dijkstra\n";
	mygraph::graph<dijkstra::dijkstra_vertex> g(vNum, nNum);
	std::cout << "\ngraph has " << g.vertices.size() << " vertices, " << g.edges.size() << " edges" << std::endl;
	std::cout << "\n";

	//shortest path using dijkstra reference wrapper
	dijkstra::dijkstra_ref dij_ref;
	auto start1 = std::chrono::high_resolution_clock::now();
	dij_ref(g, sIdx, tIdx);
	auto end1 = std::chrono::high_resolution_clock::now();
	auto elapse1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
	std::cout << "reference_wrapper imple for dijkstra takes " << elapse1.count() <<"usec\n"; 
	std::cout << "\n";

	// shortest path using dijkstra smart pointer
	dijkstra::dijkstra_ptr dij_ptr;
	auto start2 = std::chrono::high_resolution_clock::now();
	dij_ptr(g, sIdx, tIdx);
	auto end2 = std::chrono::high_resolution_clock::now();
	auto elapse2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
	std::cout << "shared_ptr imple for dijkstra takes " << elapse2.count() <<"usec\n"; 
	std::cout << "\n";

	// shortest path using dijkstra naked pointer
	dijkstra::dijkstra_nkd_ptr dij_nkd_ptr;
	auto start3 = std::chrono::high_resolution_clock::now();
	dij_nkd_ptr(g, sIdx, tIdx);
	auto end3 = std::chrono::high_resolution_clock::now();
	auto elapse3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3);
	std::cout << "naked ptr imple for dijkstra takes " << elapse3.count() <<"usec\n"; 
	std::cout << "\n";
	//
	std::cout << "graph generation for kruskal\n";
	mygraph::graph<kruskal::kruskal_vertex> g_kruskal(vNum, nNum);
	std::cout << "\ngraph has " << g_kruskal.vertices.size() << " vertices, " << g_kruskal.edges.size() << " edges" << std::endl;
	std::cout << "\n";


	// shortest path using kruskal reference wrapper
	kruskal::kruskal_ops krus;
	auto start4 = std::chrono::high_resolution_clock::now();
	krus(g_kruskal, sIdx, tIdx);
	auto end4 = std::chrono::high_resolution_clock::now();
	auto elapse4 = std::chrono::duration_cast<std::chrono::microseconds>(end4 - start4);
	std::cout << "reference_wrapper imple for kruskal's mst takes " << elapse4.count() <<"usec\n"; 

	return 0;
}
