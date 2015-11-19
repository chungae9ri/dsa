#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "MyClasses.h"

/*#define VERTEXNUM 	5000*/
/*#define EDGENUM		6	*/

using namespace std;

int main()
{
	int vn, en, ss, tt;
	Graph<int> g;

	cout << "input Vertex number : " << endl;
	cin >> vn;
	cout << "input edge number : " << endl;
	cin >> en;
	cout << "input Source : " << endl;
	cin >> ss;
	cout << "input Target : " << endl;
	cin >> tt;

	g.initGraph(vn, en, ss, tt);
	g.genGraph();
	g.chkGraph();

	return 0;
}
