#include <iostream>
#include <stdio.h>
#include "classes.h"

using namespace std;

int main()
{
	int c; 
	Dijkstra<int> dij(0,1024);
	/*dij.setVertexStatus(10, INTREE);*/

	c = getchar();
	while(c != 'q') {
		if(dij.chkGraph(0, 1024)) {
			cout << "graph is correct " << endl;
			dij.findShortestPath();
		} else {
			cout << "graph is not correct !!" << endl;
		}
		c = getchar();
	}
	


	return 0;
}
