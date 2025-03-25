#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

template<typename T> class SData{
	public:
		T data;
		char name[16];
		SData(const T d, char *str):data(d) {
			strcpy(name, str);
		}
		SData(){}
		~SData(){}
};

template<typename T> class Stack{
	SData<T> *sbase;
	public:
		Stack(){
			sbase = new SData<T>[5];
			sp = NULL;
		}
		SData<T> *sp;
		void push(const SData<T> &el) {
			if(sp) {
				sp++;
			} else {
				sp = sbase;
			}
			sp->data = el.data;
			strcpy(sp->name,el.name);
		}
		 SData<T> *pop(){
			 SData<T> *tmp;
			 tmp = sp;
			 if(sp == sbase) sp = NULL;
			 else --sp;
			 return tmp;
		 }
		 bool isempty() {
			 if(sp) return false;
			 else return true;
		 }
};

int main()
{
	int c, data;
	char name[16];
	Stack<int> s;
	/*SData<int> d;*/
	c = getchar();
	while(c!='q') {
		if(c=='p') {
			cout << "push data: " << endl;
			scanf("%d",&data);
			cout << "push name : " << endl;
			scanf("%s", name);
			SData<int> d(data, name);
			s.push(d);
		} else if(c == 'o') {
			if(s.isempty()) cout << "stack empty" << endl;
			else {
				SData<int> *d = s.pop();
				cout << "pop data : " << d->data << endl;
				cout << "pop name : " << d->name << endl;
			}
		}
		c = getchar();
	}

	return 0;
}
