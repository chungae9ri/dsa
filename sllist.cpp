/* generalized single linked list with c++ */

#include <iostream>

using namespace std;

template <typename T> class Node {
	public:
	T data;
	char name[16];
	Node *next;
	Node(T d=0, Node *n=0 ):data(d),next(n){cout << "con" << endl;}
	~Node(){cout << "decon" << endl;}
};

template <typename T> class siterator {
	Node<T> *pv;
	Node<T> *cur;
	public:
	/*siterator(Node<T> *p1=0, Node<T> *p2=0):cur(p1),pv(p2){}*/
	siterator(Node<T> *p1):cur(p1){}
	~siterator(){}
	siterator& operator++() {
		pv = cur;
		cur = cur->next;
		return *this;
	}

	Node<T> *getCur() {
		return cur;
	}
	Node<T> *getPv() {
		return pv;
	}

	T& operator*() {
		return cur->data;
	}

	bool operator==(const siterator &it) {
		return cur == it.cur;
	}
	bool operator!=(const siterator &it) {
		return cur != it.cur;
	}
};

template <typename T> class SList {
	Node<T> *head;
	public:
	SList():head(0){}
	void xpush(const T& data) {
		head = new Node<T>(data, head);
	}

	template<typename T1> T1 xfind(T1 first, T1 last, T dat) {
		while(first != last && *first != dat) {
			++first;
		}
		return first;
	}

	template<typename T1> void xdelete(T1 first, T1 last, T dat) {
		while(first != last && *first != dat) {
			++first;
		}

		if(first != last) {
			/*if (*first == head->data) head = first.getCur()->next;*/
			if (first.getCur() == head) head = first.getCur()->next;
			else /*if(first.pv)*/ 
				first.getPv()->next = first.getCur()->next;

			delete(first.getCur());
		}
	}

	template<typename T1> void xfree(T1 first, T1 last) {
		while(first != last) {
			++first;
			delete(head);
			head = first.getCur();
		}
	}
	/* return temporal object */ 
	siterator<T> begin() {return siterator<T>(head);} 
	/* return temporal object */ 
	siterator<T> end() {return siterator<T>(0);}
};

int main()
{
	SList<double> s;
	for (int i=0 ; i<5 ; i++)
		s.xpush(i*1.5);

	siterator<double> p1 = s.xfind(s.begin(), s.end(), 5);
	if (p1 == s.end())
		cout << "not found" << endl;
	else {
		cout << "found" << endl;
	}

	s.xdelete(s.begin(), s.end(), 4);

	siterator<double> p2 = s.begin();

	while (p2!=s.end()) {
		cout << *p2 << endl;
		++p2;
	}

	s.xfree(s.begin(), s.end());

	return 0;
}
