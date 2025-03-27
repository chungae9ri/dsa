#include <iostream>
#include <stdlib.h>

using namespace std;

#define MAX	100

template <typename T> class Stack {
	private:	
		T* data[MAX];
		int idx;
	public: 
		Stack() {
			idx = 0;
		}
		~Stack() {
			for(int i=0 ; i<idx ; i++)
				free(data[i]);
		}
		
		void push(T* d) {
			data[idx++] = d;
		}

		T* pop() {
			return data[--idx];
		}
		bool isEmpty() {
			return idx == 0 ? true : false;
		}

};

template <typename T> struct tnode {
	T data;
	char visited;
	struct tnode<T> *left;
	struct tnode<T> *right;
};

struct tnode<int> *newNode(int dat) 
{
	struct tnode<int> *nn = (struct tnode<int>*) malloc(sizeof(struct tnode<int>));
	nn->data = dat;
	nn->left = NULL;
	nn->right = NULL;
	nn->visited = 0;
	return nn;
}

void traversewithoutrecursion(struct tnode<int> *pn)
{
	struct tnode<int> *cur = pn;
	Stack<struct tnode<int> > s;

	if(cur) s.push(cur);

	while(!s.isEmpty()) {
		while(cur->left && cur->left->visited == 0) {
			cur = cur->left;
			s.push(cur);
		}
		cur = s.pop();
		cur->visited = 1;
		cout << "data : " << cur->data << endl;

		if(cur->right) {
			cur = cur->right;
			s.push(cur);
		}
	}
}

int main()
{
	struct tnode<int> *root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->left->left = newNode(6);
	root->left->left->left->right = newNode(7);
	root->right->right = newNode(5);
	root->right->right->right = newNode(8);
	root->right->right->right->left = newNode(9);
	root->right->right->right->left->left = newNode(10);
	traversewithoutrecursion(root);
	return 0;
}
