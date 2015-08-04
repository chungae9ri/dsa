#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

template<typename T> class QNode {
	public:
		T data;
		char name[16];
		QNode *next;
		QNode() {
			cout << "QNode cond" << endl;
		}
		QNode(T d, char *str):data(d) {
			strcpy(name, str);
			cout << "QNode con" << endl;
		}
		~QNode() {
			cout << "QNode des" << endl;
		}
};

template<typename T> class xQueue{
	QNode<T> *head;
	public:
	xQueue():head(0) {}
	~xQueue() {
		QNode<T> *cur = head;
		while(cur) {
			cur=cur->next;
			delete(head);
		}
	}

	void enq(QNode<T> el) {
		QNode<T> *cur = head;
		if(!cur) {
			head = cur = new QNode<T>(el.data, el.name);
			cur->next = NULL;
		} else {
			while(cur->next) {
				cur = cur->next;
			}
			cur->next = new QNode<T>(el.data, el.name);
			cur->next->next = NULL;
		}
	}
	QNode<T>* deq() {
		QNode<T> *cur = head;
		if(!cur) {
			return NULL;
		} else {
			head = cur->next;
			return cur;
		}
	}
};

int main()
{
	xQueue<int> q;
	QNode<int> qn;
	QNode<int> *pqn;
	char name[16];
	int c, age;

	c = getchar();

	while(c != 'q') {
		if(c == 'p') {
			cout << "input name : " << endl;
			scanf("%s", qn.name);
			cout << "input age : " << endl;
			scanf("%d", &qn.data);
			q.enq(qn);
		} else if(c == 'd') {
			pqn = q.deq();
			if(pqn) {
				cout << "dequeue name : " << pqn->name << endl;
				cout << "dequeue age : " << pqn->data << endl;
				delete(pqn);
			}
		}
		c = getchar();
	}
	return 0;
}

