#include <iostream>
#include <stdio.h>
#include "MyClasses.h"

using namespace std;

int main()
{
	/* VertexNum, EdgeNum, Source, Target */
	int s, t, vn, en; 
	int c = 'c';
	cout << "input vertex number : " << endl;
	cin >> vn;
	cout << "input edge number : " << endl;
	cin >> en;
	Kruskal<int> ksl(vn, en);
	ksl.makeTestPath();

	while(c != 'q') {
		cout << "input source idx : " << endl;
		cin >> s;
		cout << "input target idx : " << endl;
		cin >> t;
		ksl.findMaxBWPath(s, t);
		cout << "------------------------------" << endl;
		cout << "press q to quit or press any key to continue " << endl;
		fflush(stdin);
		c = getchar();
		c = getchar();
		if(c == 'q') break;
	}

	return 0;
}
