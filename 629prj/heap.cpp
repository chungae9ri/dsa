#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
#define LEN	5000	

/* heap class */
template <typename T> class heap {
	public:
		/* heap data. data is idx and 
		   it is the name of each vertex */
		T *ph;
		int arrlen, last;

		heap() {
			last = 0;
			arrlen = LEN;
			/* mem allocation for heap */
			ph = (T *)malloc(sizeof(T) * arrlen);
			/* initialize the name of each vertex */
			for(int i=0 ; i<LEN ; i++) 
				ph[i] = i+1;
			last = LEN;
		}
		~heap(){
			cout << "arrlen : " << arrlen << endl;
			/* free alloced mem */
			free(ph);
		}

		/* display heap */
		void xdisplay() {
			for(int i=0 ; i<last; i++) {
				cout << ph[i] << endl;
			}
		}

		/* move down current vertex until the stop location */
		void xmovedown(int idx, int stop ) {
			int i, lc, rc;
			if(idx == stop) return; 
			/* left child */
			lc = 2*idx+1;
			/* right child */
			rc = lc+1;
			i = idx;
			if(rc > stop) rc = lc;
			/* while left child is bigger or 
			   right child is bigger than current vertex do
			   swap and move down */
			while(ph[i] < ph[lc] || ph[i] < ph[rc]) {
				if(ph[lc] >= ph[rc] && ph[lc] > ph[i]) {
					xswap(ph[lc], ph[i]);
					i = lc;
					lc = 2*i + 1;
					rc = lc + 1;
					if(lc == stop) {
						if(ph[lc] >= ph[i]) 
							xswap(ph[lc], ph[i]);
					}

					if(lc >= stop) break;

				} else if(ph[lc] < ph[rc] && ph[rc] > ph[i]) {
					xswap(ph[rc], ph[i]);
					i = rc;
					lc = 2*i + 1;
					rc = lc + 1;
					if(lc == stop) {
						if(ph[lc] >= ph[i]) 
							xswap(ph[lc], ph[i]);
					}

					if(lc >= stop) break;
				}
			}
		}

		/* make a heap from an arbitrary array */
		void xheapify() {
			int i, j, lc, rc;
			int lastpar = (int)(last/2);
			for(i=lastpar ; i>=0 ; i--) {
				xmovedown(i, last-1);
			}
		}

		/* check heap is correct or not */
		void xchkheap() {
			bool b = true;
			int rc, lc;
			/* for each vertex do
			   check if any child is bigger than parent*/
			for(int i=0 ; i<(int)(last/2) ; i++) {
				lc = 2*i + 1;
				rc = lc + 1;
				if(rc >= last) rc = lc;
				if(ph[rc] > ph[i] || ph[lc] > ph[i]) {
					b = false;
					cout << "not heap in " << i << endl;
				}
			}
			if(b) cout << "correct max heap." << endl;
			else cout << " not correct max heap." << endl;
		}

		/* swap func */
		void xswap(T &lhs, T &rhs) {
			T temp;
			temp = lhs;
			lhs = rhs;
			rhs = temp;
		}

		/* heap insert. add current vertex to
		   the last location and move up to correct location*/
		void xinsert(T dat) {
			int par, cur;

			/* if heap size grows over the alloced mem, 
			   then realloc the heap mem*/
			if(last>=arrlen) {
				ph = (T *)realloc(ph, arrlen*2*sizeof(T));
				arrlen = arrlen*2;
			}

			cur = last;

			/* add current vertex to the last location */
			ph[cur] = dat;
			par = (int)((cur-1)/2);
			if(par<=0) par=0;

			/* move up the current vertex to the proper location*/
			while(ph[par] < ph[cur]) {
				xswap(ph[par], ph[cur]);
				cur = par;
				par = (int)((cur-1)/2);
			}
			last++;
		}

		/* get the first item(maximum) in the heap and
		   move the last item to the first location and
		   move it down to correct loaction */
		T xmaximum() {
			int child, cur = 0;
			T data = ph[0];
			xswap(ph[0], ph[last-1]);
			last -= 1;
			xmovedown(0, last-1);

			return data;
		}

		/* rearrange the current idx.
		   it can move up or move down
		 */
		void rearrange(int idx) {
			int par, cur = idx, lc, rc;

			par = (int)((cur-1)/2);
			if(par <= 0) par = 0;

			/* if current is larger than parent, 
			   then it should move up */
			while(ph[par] < ph[cur]) {
				xswap(ph[par], ph[cur]);
				cur = par;
				par = (int)((cur-1)/2);
				if(par<0) break;
			}

			/* current need to move down */
			lc = cur*2+1;
			rc = lc+1;
			while(lc < last) {
				if(rc == last) rc = lc;
				if(ph[cur] > ph[lc] && ph[cur] > ph[rc]) {
					break;
				} else if(ph[rc] > ph[lc]) {
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

		/* delete item in heap.
		   move last item to the deleted item's location
		   and rearrange it */
		void xdelete(int idx) {
			xswap(ph[idx], ph[last-1]);
			last -= 1;
			rearrange(idx);
		}
};

int main()
{
	int data, c, i, maxi, cntdel=0, cntinst=0;
	float stretch = 10000.f;
	int D[LEN];

	heap<int> H;
	H.xheapify();
	/*H.xdisplay();*/
	H.xchkheap();

	srand(time(NULL));

	for(i=0 ; i<5000 ; i++) {
		D[i] = (int)((float)rand()/(float)RAND_MAX * stretch);
	}

	for(i=0 ; i<5000 ; i++) {
		int k = (int)((float)rand()/(float)RAND_MAX * stretch);
		if(k%3 == 0){
			H.xinsert(k);
			cntinst++;
		} else if(k%3==1 && H.last>0 && k<H.last){
			H.xdelete(k);
			cntdel++;
		} else {
			maxi = H.xmaximum();
			/*cout << "maximum : "  << maxi <<endl;*/
		}
	}
	cout << "del " << cntdel << " times" << endl;
	cout << "insert " << cntinst << " times" << endl;
	H.xchkheap();

	while(c != 'q') {
		cout << "input idx to get value : " << endl;
		/*scanf("%d", &i);*/
		cin >> i;
		cout << "value of " << i << " is " << D[H.ph[i+1]] << endl;
		c = getchar();
	}
	return 0;
}
