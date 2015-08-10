#include <iostream>
#include <stdio.h>

using namespace std;
#define LEN	16
#define SWAP(t, A, B) { t temp = A; A = B; B = temp; }

template <typename T> class heap {
	public:
	T *ph;
	int last;
	heap(){
		last = 0;
		ph = new T[LEN];
	}
	~heap(){
		delete(ph);
	}
	int pri;
	void xinsert(T dat) {
		int par, cur = last;
		ph[cur] = dat;
		par = (int)((cur-1)/2);
		if(par<=0) par=0;

		while(ph[par] < ph[cur]) {
			SWAP(T, ph[par], ph[cur]);
			cur = par;
			par = (int)((cur-1)/2);
		}
		last++;
	}
};

int main()
{
	int data, c, i;
	heap<int> hip;

	cout << "i :insert, q : quit" << endl;
	c = getchar();
	while(c != 'q') {
		if(c == 'i') {
			cout << "insert data : " << endl;
			/*scanf("%d", &data);*/
			cin >> data;
			hip.xinsert(data);
		}
		c = getchar();
	}
	for(i=0 ; i<hip.last ; i++)
		cout << hip.ph[i] << endl;
	return 0;
}
