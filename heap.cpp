/* max-heap(priority Q) is implemented.
   Bottom-up insert.
   if the comprison is changed to less-than from large-than
   the min-heap is accomplished.
 */
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
		delete[] ph;
	}
	int pri;

	void xswap(hNod<T> &lhs, hNod<T> &rhs) {
		hNod<T> temp;
		temp = lhs;
		lhs = rhs;
		rhs = temp;
	}

	void rearrange(int idx) {
		int par, cur = idx;

		par = (int)((cur-1)/2);
		if(par <= 0) par = 0;

		while(ph[par].dist > ph[cur].dist) {
			xswap(ph[par], ph[cur]);
			cur = par;
			par = (int)((cur-1)/2);
			if(par<0) break;
		}
	}

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

	T xdequeue() {
		int child, cur = 0;
		T data = ph[0];
		/* put the last node to the first pos */
		ph[0] = ph[last-1];
		/* move the first node down to correct position */
		child = cur*2 + 1;
		/* no child, that is, if leaf */
		if(child > last-2) {
			last -= 1;
			return data;
		} else {
			/* if there are children */
			while(child <= last-2) {
				/* there are two children */
				if(child+1 <= last-2) {
					if(ph[child] > ph[child+1] && ph[cur] < ph[child]) {
						SWAP(T, ph[cur], ph[child]);
					} else if(ph[child+1] >= ph[child] && ph[cur] < ph[child+1]) {
						SWAP(T, ph[cur], ph[child+1]);
					} else {
						last -= 1;
						return data;
					}
				} else {
				/* there is only one left child*/
					if(ph[cur] < ph[child]) {
						SWAP(T, ph[cur], ph[child]);
						last -= 1;
						return data;
					} else {
						last -= 1;
						return data;
					}
				}

				cur = child;
				child = cur*2 + 1;
			}
			last -= 1;
			return data;
		}
	}
};

int main()
{
	int data, c, i;
	heap<int> hip;
#if 1
	hip.xinsert(2);
	hip.xinsert(8);
	hip.xinsert(6);
	hip.xinsert(1);
	hip.xinsert(10);
	hip.xinsert(15);
	hip.xinsert(3);
	hip.xinsert(12);
	hip.xinsert(11);
#endif

	cout << "i:insert, d:dequeue, l:list up, q:quit" << endl;
	c = getchar();
	while(c != 'q') {
		if(c == 'i') {
			cout << "insert data : " << endl;
			/*scanf("%d", &data);*/
			cin >> data;
			hip.xinsert(data);
		} else if(c == 'l') {
			for(i=0 ; i<hip.last ; i++)
				cout << hip.ph[i] << endl;
		} else if(c == 'd') {
			cout << "dequeue : " << hip.xdequeue() << endl;
		}
		c = getchar();
	}
	return 0;
}
