#include <iostream>
#include <stddef.h>

using namespace std;

struct node{
	int a;
	int b;
	char c[10];
	struct node *next;
	struct node *prev;
};

int main()
{
	int base, offset;
	struct node *root;

	cout << offsetof(struct node, c) << endl;

	base = root;
	/*offset = (size_t)(&((struct node *)0)->c);*/
	cout << "offset is " << offset << endl;

	return 0;
}
