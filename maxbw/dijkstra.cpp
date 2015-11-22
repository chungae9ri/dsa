#include <iostream>
#include <stdio.h>
#include "MyClasses.h"

using namespace std;

int main()
{
	/* source, target, vertex number, edge number */

	int s, t, vn, en, c='c'; 
	cout << "input vertex number : " << endl;
	cin >> vn;
	cout << "input edge number : " << endl;
	cin >> en;
	Dijkstra<int> dij(vn, en);
	dij.makeTestPath();

	while(c != 'q') {
		cout << "input source idx : " << endl;
		cin >> s;
		cout << "input target idx : " << endl;
		cin >> t;
		cout << "find shortest path : Dijkstra" << endl;
		dij.findMaxBWPath(s, t);
		cout << "------------------------------" << endl;
		cout << "find shortest path : Dijkstra with Heap" << endl;
		dij.findMaxBWPathHeap(s, t);
		cout << "------------------------------" << endl;
		cout << "press q to quit or press any key to continue " << endl;
		c = getchar();
		c = getchar();
		if(c == 'q') break;
	}
		return 0;
}
