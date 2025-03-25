#include <iostream>
#include <stdio.h>
/* for RAND_MAX */
#include <stdlib.h>
/* for using random number generator */
#include <time.h>

using namespace std;
#define MAXLEN		256	

template <typename T> class Xsort{
	public :
		T data[MAXLEN];
		int last;
		Xsort(){
			last = 0;
			for(int i=0 ; i<MAXLEN; i++)
				data[i] = 0;
		}
		~Xsort(){}
		void Xinsert(T in) {
			if(last > MAXLEN-1) return;
			data[last++] = in;
		}
		void Xdisplay() {
			for(int i=0 ; i<last; i++) {
				cout << i << "th : " << data[i] << endl;
			}
		}
		void Xchksort() {
			bool sorted = true;
			for(int i=0 ; i<last-1 ; i++) {
				if(data[i] > data[i+1]) {
					sorted = false;
					cout << "not sorted btwn " << i << " and " << i+1 << endl;
				}
			}
			if(sorted) cout << "correctly sorted " << endl;
		}
		void Xswap(T &a, T &b) {
			T temp;
			temp = a;
			a = b;
			b = temp;
		}
		void Xselectionsort() {
			int i, j;
			T temp;
			for(i=0 ; i<last-1 ; i++) {
				for(j=i+1 ; j<last ; j++) {
					if(data[j] < data[i]) {
						Xswap(data[i], data[j]);
					}
				}
			}
		}
		void Xinsertionsort() {
			int i, j;
			T temp;
			for(i=1 ; i<last ; i++) {
				temp = data[i];
				for(j=i ; j>0 && temp<data[j-1] ; j--) {
					data[j] = data[j-1];
				}
				data[j] = temp;
			}
		}
		void Xbubblesort() {
			int i, j;
			for(i=0 ; i<last ; i++) {
				for(j=last-1 ; j>i ; j--) {
					if(data[j] < data[j-1])
						Xswap(data[j], data[j-1]);
				}
			}
		}
		void Xcombsort() {
			int step=last, i, j, k;

#if 1
			/*while((step=(int)(step/1.3) > 1) || again == 1) {*/
			while((step=(int)(step/1.3)) >= 1) {
				/*if(step < 1) step = 1;*/
				for(i=0, j=step ; j<last ; i++, j++) {
					if(data[i] > data[j]) {
						Xswap(data[i], data[j]);
					}
				}
			}
#else
			bool again;
			/* 1st phase */
			while((step=(int)(step/1.3)) > 1) {
				for(j=last-1 ; j>=step ; j--) {
					k = j-step;
					if(data[j] < data[k])
						Xswap(data[j], data[k]);
				}
			}
			/* 2nd phase */
			again = true;
			for(i=0 ; i<last-1 && again ; i++){
				for(j=last-1, again=false ; j>i ; --j){
					if(data[j] < data[j-1]) {
						Xswap(data[j], data[j-1]);
						again = true;
					}
				}
			}
#endif
		}

		/* shell sort = comb sort + insertion sort */
		void Xshellsort() {
#if 1
			int h, i, j;
			T t;
			h = last;
			while((h=(int)(h/2)) >= 1) { /* similiar with comb sort */
				/* insertion sort with gap h */
				for(i=h ; i<last ; i++) {
					t = data[i];
					for(j=i ; j>=h && t<data[j-h] ; j-=h) {
						data[j] = data[j-h];
					}
					data[j] = t;
				}
			}
#else
			int step, i, j, inc;
			int seq[5] = {5,4,3,2,1};
			for (step = 0; seq[step] >= 1; step++) {
				inc = seq[step];
				for (i = inc; i < last ; i++) {
					j = i;
					T val = data[i];
					while ((j >= inc) && val < data[j - inc]) {
						data[j] = data[j - inc];
						j -= inc;
					}
					data[j] = val;
				}
			}
#endif
		}

		void Xheapsort() {
			int i;
			/* max heap */
			Xheapify();
			for(i=last-1 ; i>0 ; i--) {
				Xswap(data[0], data[i]);
				Xmovedown(0, i-1);
			}
		}

		void Xmovedown(int idx, int stop) {
			int i, lc, rc;
			if(idx == stop) return;
			lc = 2*idx+1;
			rc = lc+1;
			i = idx;
			if(rc >= stop) rc = lc;
			while(data[i] < data[lc] || data[i] < data[rc]) {
				if(data[lc] >= data[rc] && data[lc] > data[i]) {
					Xswap(data[lc], data[i]);
					i = lc;
					lc = 2*i + 1;
					rc = lc + 1;
					if(lc >= stop) break;
				} else if(data[lc] <= data[rc] && data[rc] > data[i]) {
					Xswap(data[rc], data[i]);
					i = rc;
					lc = 2*i + 1;
					rc = lc + 1;
					if(lc >= stop) break;
				}
			}
		}

		/* make a heap from an arbitrary array */
		void Xheapify() {
			int i, j, lc, rc;
			int lastpar = (int)(last/2);
			for(i=lastpar ; i>=0 ; i--) {
				Xmovedown(i, last);
			}
			xchkheapify();
		}

		void xchkheapify() {
			bool b = true;
			int rc, lc;
			for(int i=0 ; i<(int)(last/2) ; i++) {
				lc = 2*i + 1;
				rc = lc + 1;
				if(rc >= last) rc = lc;
				if(data[rc] > data[i] || data[lc] > data[i]) {
					b = false;
					cout << "not heap in " << i << endl;
				}
			}
			if(b) cout << "correct max heap." << endl;
			else cout << " not correct max heap." << endl;
		}

		void Xquicksort(T *a, int n) {
			int i, j,k, p, t;
			if (n < 2)
				return;
			p = a[n / 2];
			for (i = 0, j = n - 1; ; i++, j--) {
				while (a[i] < p)
					i++;
				while (p < a[j])
					j--;
				if (i >= j)
					break;
				Xswap(a[i], a[j]);
			}
			Xquicksort(a, i);
			Xquicksort(a + i, n - i);
		}

		void Xmergesort(T *a, int n) {
			if(n < 2) return;
			int m = (int)(n / 2);
			Xmergesort(a, m);
			Xmergesort(a + m, n - m);
			Xmerge(a, n, m);
		}

		void Xmerge(T *a, int n, int m) {
			int i, j, k;
			int *x = (int *)malloc(n * sizeof (int));
			for(i = 0, j = m, k = 0; k < 2*m; k++) {
				x[k] = j == 2*m ? a[i++] : i == m ? a[j++] : a[j] < a[i] ? a[j++] : a[i++];
			}
			for(i = 0; i < 2*m; i++) {
				a[i] = x[i];
			}
			free(x);
		}

		/* using count sort */
		void Xradixsort() {
			int exp, mod, max = 0;
			int count[10] = {0,};
			T out[last];
			int i;

			for(i = 0 ; i < last ; i++) {
				if(data[i] > max) max = data[i];
			}

			for(exp = 1 ; max/exp > 0 ; exp *= 10) {
				for(i = 0 ; i < 10 ; i++)
					count[i] = 0;
				for(i = 0 ; i < last ; i++) {
					count[(data[i]/exp)%10]++;
				}
				/* the last real index in data */
				for(i = 1 ; i < 10 ; i++)
					count[i] += count[i-1];
				for(i = last - 1 ; i >= 0 ; i--) {
					out[count[(data[i]/exp)%10] - 1] = data[i];
					count[(data[i]/exp)%10]--;
				}

				for(i = 0 ; i < last ; i++) {
					data[i] = out[i];
				}
			}
		}

			/* using queue */
		void XradixsortQ() {
			int exp, mod, max = 0;
			/* queue for saving data of each mod */
			int q0[last], q1[last], q2[last], q3[last], q4[last];
			int q5[last], q6[last], q7[last], q8[last], q9[last];
			int a, b, c, d, e, f, g, h, i, j, k, l;
			for(k = 0 ; k < last ; k++) {
				if(data[k] > max) max = data[k];
			}

			for(exp = 1 ; max/exp > 0 ; exp *= 10) {
				a = b = c = d = e = f = g = h = i = j = l = 0;
				for(k = 0 ; k < last ; k++) {
					mod = (data[k] / exp) % 10;
					if(mod == 0) q0[a++] = data[k];
					else if(mod == 1) q1[b++] = data[k];
					else if(mod == 2) q2[c++] = data[k];
					else if(mod == 3) q3[d++] = data[k];
					else if(mod == 4) q4[e++] = data[k];
					else if(mod == 5) q5[f++] = data[k];
					else if(mod == 6) q6[g++] = data[k];
					else if(mod == 7) q7[h++] = data[k];
					else if(mod == 8) q8[i++] = data[k];
					else if(mod == 9) q9[j++] = data[k];
				}
				for(k = 0 ; k < a ; k++)
					data[k] = q0[k];
				l = a;
				for(k = 0 ; k < b ; k++)
					data[l + k] = q1[k];
				l +=  b;
				for(k = 0 ; k < c ; k++)
					data[l + k] = q2[k];
				l += c;
				for(k = 0 ; k < d ; k++)
					data[l + k] = q3[k];
				l += d;
				for(k = 0 ; k < e ; k++)
					data[l + k] = q4[k];
				l += e;
				for(k = 0 ; k < f ; k++)
					data[l + k] = q5[k];
				l += f;
				for(k = 0 ; k < g ; k++)
					data[l + k] = q6[k];
				l += g;
				for(k = 0 ; k < h ; k++)
					data[l + k] = q7[k];
				l += h;
				for(k = 0 ; k < i ; k++)
					data[l + k] = q8[k];
				l += i;
				for(k = 0 ; k < j ; k++)
					data[l + k] = q9[k];
			}
		}
};

int main()
{
	Xsort<int> xsort;
	int c, d;

#if 0
	data.Xinsert(41);
	xsort.Xinsert(11);
	xsort.Xinsert(18);
	xsort.Xinsert(7);
	xsort.Xinsert(16);
	xsort.Xinsert(25);
	xsort.Xinsert(4);
	xsort.Xinsert(23);
	xsort.Xinsert(32);
	xsort.Xinsert(31);
	xsort.Xinsert(22);
	xsort.Xinsert(9);
	xsort.Xinsert(1);
	xsort.Xinsert(22);
	xsort.Xinsert(3);
	xsort.Xinsert(7);
	xsort.Xinsert(31);
	xsort.Xinsert(6);
	xsort.Xinsert(10);
#else
	int in, i, stretch = 1024.f;
	srand(time(NULL));
	for(i=0 ; i<256 ; i++) {
		in = (int)((float)(rand())/(float)RAND_MAX*stretch);
		xsort.Xinsert(in);
	}

#endif
	cout << "q : quit, i : insert data" << endl;
	cout << "1 : selectionsort, 2 : insertionsort, 3 : bubblesort" << endl;
	cout << "4 : combsort, 5 : shellsort, 6 : heapsort" << endl;
	cout << "7 : quicksort, 8 : mergesort, 9 : radixsort, a : radixsort Q" << endl;
	c = getchar();
	while(c != 'q') {
		if(c == 'i') {
			scanf("%d", &d);
			xsort.Xinsert(d);
		} else if(c == '1') {
			xsort.Xselectionsort();
		} else if(c == '2') {
			xsort.Xinsertionsort();
		} else if(c == '3') {
			xsort.Xbubblesort();
		} else if(c == '4') {
			xsort.Xcombsort();
		} else if(c == '5') {
			xsort.Xshellsort();
		} else if(c == '6') {
			xsort.Xheapsort();
		} else if(c == '7') { /* quick sort uses recurrence */
			xsort.Xquicksort(xsort.data, xsort.last);
		} else if(c == '8') { /* merge sort uses recurrence */
			xsort.Xmergesort(xsort.data, xsort.last);
		} else if(c == '9') {
			xsort.Xradixsort();
		} else if(c == 'a') {
			xsort.XradixsortQ();
		}
		c = getchar();
	}
	xsort.Xdisplay();
	xsort.Xchksort();
	return 0;
}
