#include <iostream>

using namespace std;

template<typename T> class tnode{
	T d;
	public:
	tnode(int dat):d(dat) {}
	class tnode<T> *left;
	class tnode<T> *right;
};

template<typename T> class tnode<T> *minimaltree(T *p, int s, int e)
/*class tnode<int> *minimaltree(int *p, int s, int e)*/
{
	if(s > e) return NULL;
	int mid = (int)((s+e)/2);
	class tnode<T> *n = new tnode<T>(p[mid]);

	n->left = minimaltree<T>(p, s, mid-1);
	n->right = minimaltree<T>(p, mid+1, e);

	return n;
}


int main()
{
	double arr[10] = {1,2,3,4,5,6,7,8,9,10};
	class tnode<double> *root;

	root = minimaltree<double>(arr, 0, 9);

	return 0;
}
