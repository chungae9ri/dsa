#include <iostream>
#include <stdio.h>
#include "MyClasses.h"

using namespace std;

int main()
{
	/* source, target, vertex number, edge number */

#if 1
	int s, t, vn, en; 
	cout << "input vertex number : " << endl;
	cin >> vn;
	cout << "input edge number : " << endl;
	cin >> en;
	cout << "input source idx : " << endl;
	cin >> s;
	cout << "input target idx : " << endl;
	cin >> t;
	Dijkstra<int> dij(vn, en, s, t);
#else
	Dijkstra<int> dij(5000, 100, 0, 1024);
#endif

	/*dij.chkGraph();*/
	dij.editEdge4Test(0, 203, 2, WEIGHTRANGE+1);
	dij.editEdge4Test(203, 2043, 5, WEIGHTRANGE+1);
	dij.editEdge4Test(2043, 1837, 0, WEIGHTRANGE+1);
	dij.editEdge4Test(1837, 396, 1, WEIGHTRANGE+1);
	dij.editEdge4Test(396, 4930, 2, WEIGHTRANGE+1);
	dij.editEdge4Test(4930, 1912, 5, WEIGHTRANGE+1);
	dij.editEdge4Test(1912, 882, 4, WEIGHTRANGE+1);
	dij.editEdge4Test(882, 549, 2, WEIGHTRANGE+1);
	dij.editEdge4Test(549, 2943, 4, WEIGHTRANGE+1);
	dij.editEdge4Test(2943, 3367, 2, WEIGHTRANGE+1);
	dij.editEdge4Test(3367, 2939, 2, WEIGHTRANGE+1);
	dij.editEdge4Test(2939, 4102, 2, WEIGHTRANGE+1);
	dij.editEdge4Test(4102, 88, 3, WEIGHTRANGE+1);

	dij.editEdge4Test(88, 2733, 3, WEIGHTRANGE+1);
	dij.editEdge4Test(2733, 1023, 5, WEIGHTRANGE+1);
	dij.editEdge4Test(1023, 923, 0, WEIGHTRANGE+1);
	dij.editEdge4Test(923, 102, 3, WEIGHTRANGE+1);
	dij.editEdge4Test(102, 485, 3, WEIGHTRANGE+1);
	dij.editEdge4Test(485, 775, 3, WEIGHTRANGE+1);
	dij.editEdge4Test(775, 120, 3, WEIGHTRANGE+1);
	dij.editEdge4Test(120, 1, 5, WEIGHTRANGE+1);
	dij.editEdge4Test(1, 4022, 3, WEIGHTRANGE+1);
	dij.editEdge4Test(4022, 1024, 3, WEIGHTRANGE+1);
	
#if 1	
	cout << "find shortest path : Dijkstra" << endl;
	dij.findShortestPath();
	cout << "------------------------------" << endl;
	cout << "find shortest path : Dijkstra with Heap" << endl;
	dij.findShortestPathwithHeap();

#else
	if(dij.chkGraph()) {
		cout << "graph is correct " << endl;
		dij.findShortestPath();
		cout << "------------------------------" << endl;
		dij.findShortestPathwithHeap();
	} else {
		cout << "graph is not correct !!" << endl;
		return 0;
	}
#endif
	
	return 0;
}
