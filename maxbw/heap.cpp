#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MyClasses.h"

using namespace std;

int main()
{
	int vn;
	int c = 'c', i, maxi, cntdel=0, cntinst=0, cntmax=0;
	float stretch = 10000.f;
	int *D;

	cout << "input Heap size : " << endl;
	cin >> vn;
	D = (int *)malloc(sizeof(int) * vn);
	Heap<int> H(vn);
	H.xHeapify();
	H.xChkHeap();

	srand(time(NULL));

	for(i=0 ; i<vn; i++) {
		D[i] = (int)((float)rand()/(float)RAND_MAX * stretch);
		H.xInsert(D[i]);
	}

	cout << "heap size : " << H.getSize() << endl;

	for(i=0 ; i<vn; i++) {
		int k = (int)((float)rand()/(float)RAND_MAX * stretch);
		if(k%3 == 0){
			H.xInsert(k);
			cntinst++;
		} else if(k%3==1 && H.getSize()>0 && k<H.getSize()){
			H.xDelete(k);
			cntdel++;
		} else {
			maxi = H.xMaximum();
			cntmax++;
		}
	}
	cout << "del " << cntdel << " times" << endl;
	cout << "insert " << cntinst << " times" << endl;
	cout << "get max " << cntmax<< " times" << endl;
	cout << "heap last index : " << H.getLastIdx() << endl;
	cout << "heap size : " << H.getSize() << endl;
	H.xChkHeap();

	while(c != 'q') {
		cout << "input idx to get value : " << endl;
		/*scanf("%d", &i);*/
		cin >> i;
		cout << "value of " << i << " is " << D[H.ph[i+1]] << endl;
		cout << "------------------------------" << endl;
		cout << "press q to quit or press any key to continue " << endl;
		c = getchar();
		c = getchar();
		if(c == 'q') break;
	}

	H.xChkHeap();
	free(D);
	return 0;
}
