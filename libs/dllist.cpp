/* doubly linked list in c++ */
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

template<typename T> class Node{
	public:
		T age;
		char name[16];
		Node<T> *next;
		Node<T> *prev;
		Node(const T a, char *str, Node<T> *h):age(a){
			next = h;
			if(h) h->prev = this;
			prev = NULL;
			strcpy(name,str);
			/*cout << "con Node" << endl;*/
		}
		~Node(){
			/*cout << "des Node" << endl;*/
		}
};

template<typename T> class diterator {
	Node<T> *cur;
	public:
		diterator(Node<T> *p):cur(p) {
			cout << "con diterator" << endl;
		}
		~diterator() {
			cout << "des diterator" << endl;
		}

		Node<T> *getCur() {return cur;}
		diterator &operator+(int i) {
			while(i-- > 0) if(cur->next) cur = cur->next;
			return *this;
		}
		diterator &operator-(int i) {
			while(i-- > 0) if(cur->prev) cur = cur->prev;
			return *this;
		}
		diterator & operator++() {cur = cur->next; return *this;};
		T& operator*() {return cur->age;}
		bool operator==(const diterator &it) {return it.cur == cur;}
		bool operator!=(const diterator &it) {return it.cur != cur;}
};

template<typename T> class DList {
	Node<T> *head;
	public:
		DList():head(0){}
		void xpush(T dat, char *str) {
			head = new Node<T>(dat, str, head);
		}

		template<typename T1> void xdelete(T1 first, T1 last, char *str) {
			while(first != last && strcmp(first.getCur()->name, str))
				++first;
			if(first != last) {
				if(first.getCur() == head) {
					head = first.getCur()->next;
					if(first.getCur()->next) first.getCur()->next->prev = NULL;
				} else {
					first.getCur()->prev->next = first.getCur()->next;
					if(first.getCur()->next)
					first.getCur()->next->prev = first.getCur()->prev;
				}
				delete(first.getCur());
			}
		}

		template<typename T1> T& xfind(T1 first, T1 last, char *str) {
			while(first != last && strcmp(first.getCur()->name, str))
				++first;
			if(first != last) {
				return *first;
			}
		}

		template<typename T1> void xfree(T1 first, T1 last) {
			while(first != last) {
				++first;
				delete(head);
				head = first.getCur();
			}
		}
		template<typename T1> void xprint(T1 first, T1 last) {
			while(first != last) {
				cout << first.getCur()->name << ", "<<*first << endl;
				++first;
			}
		}
		diterator<T> begin() {return diterator<T>(head);}
		diterator<T> end() {return diterator<T>(0);}
};


int main ()
{
	DList<int> s;
	int c, age=10, ret=0;
	char name[16];

	c = getchar();

	while(c != 'q') {
		if (c == 'p') {
			cout << "input name : " << endl;
			scanf("%s", name);
			s.xpush(age++, name);
			s.xprint(s.begin(), s.end());
		} else if(c == 'd') {
			cout << "input del name :" << endl;
			scanf("%s", name);
			s.xdelete(s.begin(), s.end(), name);
			s.xprint(s.begin(), s.end());
		} else if(c == 'f') {
			cout << "input find name :" << endl;
			scanf("%s", name);
			ret = s.xfind(s.begin(), s.end(), name);
			cout << name << "'s age : " << ret << endl;
		}
		c=getchar();
	}
	s.xfree(s.begin(), s.end());
	return 0;
}
