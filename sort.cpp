#include <iostream>
#include <stdio.h>

using namespace std;
#define LEN 128

template <typename T> class Xsort{
	T data[LEN];
	int len;
	public :
		Xsort(){
			len = 0;
			for(int i=0 ; i<LEN; i++)
				data[i] = 0;
		}
		~Xsort(){}
		void Xinsert(T in) {
			if(len > LEN-1) return;
			data[len++] = in;
		}
		void Xdisplay() {
			for(int i=0 ; i<len; i++) {
				cout << data[i] << endl;
			}
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
			for(i=0 ; i<len-1 ; i++) {
				for(j=i+1 ; j<len ; j++) {
					if(data[j] < data[i]) {
						Xswap(data[i], data[j]);
					}
				}
			}
		}
		void Xinsertionsort() {
			int i, j;
			T temp;
			for(i=1 ; i<len ; i++) {
				temp = data[i];
				for(j=i ; j>0 && temp<data[j-1] ; j--) {
					data[j] = data[j-1];
				}
				data[j] = temp;
			}
		}
		void Xbubblesort() {
			int i, j;
			for(i=0 ; i<len ; i++) {
				for(j=len-1 ; j>i ; j--) {
					if(data[j] < data[j-1])
						Xswap(data[j], data[j-1]);
				}
			}
		}
		void Xcombsort() {
			int step=len, i, j, k;

#if 1
			/*while((step=(int)(step/1.3) > 1) || again == 1) {*/
			while((step=(int)(step/1.3)) >= 1) {
				/*if(step < 1) step = 1;*/
				for(i=0, j=step ; j<len ; i++, j++) {
					if(data[i] > data[j]) {
						Xswap(data[i], data[j]);
					}
				}
			}
#else
			bool again;
			/* 1st phase */
			while((step=(int)(step/1.3)) > 1) {
				for(j=len-1 ; j>=step ; j--) {
					k = j-step;
					if(data[j] < data[k])
						Xswap(data[j], data[k]);
				}
			}
			/* 2nd phase */
			again = true;
			for(i=0 ; i<len-1 && again ; i++){
				for(j=len-1, again=false ; j>i ; --j){
					if(data[j] < data[j-1]) {
						Xswap(data[j], data[j-1]);
						again = true;
					}
				}
			}
#endif
		}
};

int main()
{
	Xsort<int> data;
	int c, d;

#if 1
	data.Xinsert(41);
	data.Xinsert(11);
	data.Xinsert(18);
	data.Xinsert(7);
	data.Xinsert(16);
	data.Xinsert(25);
	data.Xinsert(4);
	data.Xinsert(23);
	data.Xinsert(32);
	data.Xinsert(31);
	data.Xinsert(22);
	data.Xinsert(9);
	data.Xinsert(1);
	data.Xinsert(22);
	data.Xinsert(3);
	data.Xinsert(7);
	data.Xinsert(31);
	data.Xinsert(6);
	data.Xinsert(10);
#endif
	cout << "q : quit, i : insert data" << endl;
	cout << "1 : selectionsort, 2 : insertionsort, 3 : bubblesort" << endl;
	cout << "4 : combsort" << endl;
	c = getchar();
	while(c != 'q') {
		if(c == 'i') {
			scanf("%d", &d);
			data.Xinsert(d);
		} else if(c == '1') {
			data.Xselectionsort();
		} else if(c == '2') {
			data.Xinsertionsort();
		} else if(c == '3') {
			data.Xbubblesort();
		} else if(c == '4') {
			data.Xcombsort();
		}
		c = getchar();
	}
	data.Xdisplay();
	return 0;
}
