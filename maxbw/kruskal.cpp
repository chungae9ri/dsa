#include <iostream>
#include "MyClasses.h"

using namespace std;

int main()
{
	/* VertexNum, EdgeNum, Source, Target */
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
	Kruskal<int> ksl(vn, en, s, t);
	ksl.makeTestPath();
#else
	Kruskal<int> ksl(5000, 50, 0, 1024);
	ksl.makeTestPath();
	
#endif
	ksl.findShortestPathKruskal();

	return 0;
}
