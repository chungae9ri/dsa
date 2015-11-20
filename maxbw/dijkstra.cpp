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
	dij.makeTestPath();
#else
	Dijkstra<int> dij(5000, 50, 0, 1024);
	dij.makeTestPath();
	
#endif

#if 1	
	cout << "find shortest path : Dijkstra" << endl;
	dij.findMaxBWPath();
	cout << "------------------------------" << endl;
	cout << "find shortest path : Dijkstra with Heap" << endl;
	dij.findMaxBWPathHeap();

#else
	if(dij.chkGraph()) {
		cout << "graph is correct " << endl;
		dij.findMaxBandwidth();
		cout << "------------------------------" << endl;
		dij.findMaxBandwidthwithHeap();
	} else {
		cout << "graph is not correct !!" << endl;
		return 0;
	}
#endif
	
	return 0;
}
