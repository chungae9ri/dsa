#include <iostream>
#include <stdio.h>

using namespace std;

template <typename T> class Xsort{
	T dat[16];
	int len;
	public :
		Xsort(){
			len = 0;
			for(int i=0 ; i<16 ; i++)
				dat[i] = 0;
		}
		~Xsort(){}
		void Xinsert(T in) {
			if(len > 15) return;
			dat[len++] = in;
		}
		void Xdisplay() {
			for(int i=0 ; i<len; i++) {
				cout << dat[i] << endl;
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
					if(dat[j] < dat[i]) {
						Xswap(dat[i], dat[j]);
					}
				}
			}
		}
		void Xinsertionsort() {
			int i, j;
			T temp;
			for(i=1 ; i<len ; i++) {
				temp = dat[i];
				for(j=i ; j>0 && temp<dat[j-1] ; j--) {
					dat[j] = dat[j-1];
				}
				dat[j] = temp;
			}
		}
		
};

int main()
{
	Xsort<int> data;
	int c, d;

#if 1
	data.Xinsert(5);
	data.Xinsert(2);
	data.Xinsert(3);
	data.Xinsert(8);
	data.Xinsert(1);
	data.Xinsert(9);
	data.Xinsert(4);
	data.Xinsert(0);
#endif
	cout << "q : quit, i : insert data" << endl;
	cout << "1 : selectionsort, 2 : insertionsort" << endl;
	c = getchar();
	while(c != 'q') {
		if(c == 'i') {
			scanf("%d", &d);
			data.Xinsert(d);
		} else if(c == '1') {
			data.Xselectionsort();
		} else if(c == '2') {
			data.Xinsertionsort();
		}
		c = getchar();
	}
	data.Xdisplay();
	return 0;
}
