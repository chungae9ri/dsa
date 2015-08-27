/* max-heap(priority Q) is implemented.
   Bottom-up insert.
   if the comprison is changed to less-than from large-than
   the min-heap is accomplished.
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
#define LEN	256	
#define SWAP(t, A, B) { t temp = A; A = B; B = temp; }

template <typename T> class heap {
	public:
	T *ph;
	int last;
	heap(){
		last = 0;
		ph = new T[LEN];
	}
	/* test constructor */
	heap(int type) {
		last = 0;
		ph = new T[LEN];
		/*
		ph[0] = 2;
		ph[1] = 8;
		ph[2] = 6;
		ph[3] = 1;
		ph[4] = 10;
		ph[5] = 15;
		ph[6] = 3;
		ph[7] = 12;
		ph[8] = 11;
		last = 9;
		*/
		float stretch = 1000.0f;
		srand(time(NULL));
		for(int i=0 ; i< LEN ; i++) {
			ph[i] = (int)(((float)rand()/(float)RAND_MAX)*stretch);
		}
		last = LEN;
	}
	~heap(){
		delete[] ph;
	}

	void xdisplay() {
		for(int i=0 ; i<last ; i++) {
			cout << ph[i] << endl;
		}
	}

	/* make a heap from an arbitrary array */
	void xheapify() {
		int i, j, lc, rc;
		int lastpar = (int)(last/2);
		for(i=lastpar ; i>=0 ; i--) {
			lc = 2*i+1;
			rc = lc+1;
			j = i;
			if(rc >= last) rc = lc;
			while(ph[j] < ph[lc] || ph[j] < ph[rc]) {
				if(ph[lc] >= ph[rc] && ph[lc] > ph[j]) {
					xswap(ph[lc], ph[j]);
					j = lc;
					lc = 2*j + 1;
					rc = lc + 1;
					if(lc >= last) break;

				} else if(ph[lc] <= ph[rc] && ph[rc] > ph[j]) {
					xswap(ph[rc], ph[j]);
					j = rc;
					lc = 2*j + 1;
					rc = lc + 1;
					if(lc >= last) break;
				}
			}
		}
	}

	void xchkheapify() {
		bool b = true;
		int rc, lc;
		for(int i=0 ; i<(int)(last/2) ; i++) {
			lc = 2*i + 1;
			rc = lc + 1;
			if(rc >= last) rc = lc;
			if(ph[rc] > ph[i] || ph[lc] > ph[i]) {
				b = false;
				cout << "not heapify() in " << i << endl;
			}
		}
		if(b) cout << "correct max heap." << endl;
		else cout << " not correct max heap." << endl;
	}

	void xswap(T &lhs, T &rhs) {
		T temp;
		temp = lhs;
		lhs = rhs;
		rhs = temp;
	}

	/* this rearrange should be done on heap arrary. 
	   If the arrary is not a heap, heapify() must be used.
	 */
	void rearrange(int idx) {
		int par, cur = idx, lc, rc;

		par = (int)((cur-1)/2);
		if(par <= 0) par = 0;

		while(ph[par] < ph[cur]) {
			xswap(ph[par], ph[cur]);
			cur = par;
			par = (int)((cur-1)/2);
			if(par<0) break;
		}
	
		lc = cur*2+1;
		rc = lc+1;
		while(lc < last) {
			if(ph[cur] <= ph[lc] && ph[cur] <= ph[rc]) {
				break;
			} else if(ph[rc] < ph[lc]) {
				xswap(ph[cur], ph[rc]);
				cur = rc;
				lc = cur*2+1;
				rc = lc + 1;
			} else {
				xswap(ph[cur], ph[lc]);
				cur = lc;
				lc = cur*2+1;
				rc = lc + 1;
			}
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
#if 1
	heap<int> hip(1);
	hip.xheapify();
	hip.xdisplay();
	hip.xchkheapify();
#else
	heap<int> hip;

	hip.xinsert(2);
	hip.xinsert(8);
	hip.xinsert(6);
	hip.xinsert(1);
	hip.xinsert(10);
	hip.xinsert(15);
	hip.xinsert(3);
	hip.xinsert(12);
	hip.xinsert(11);

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
#endif
	return 0;
}
