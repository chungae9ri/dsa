#include <iostream>
#include <stdio.h>
using namespace std;

class SR {
	int val;
	int& ref;
	public:
		SR(int &d):ref(d), val(d) {}
		/*SR(int &d):val(d) {}*/
		~SR() {
			cout << "val : " << val << endl;
			cout << "ref : " << ref << endl;
			ref = val;
		}
};

int main()
{
	int j = 5;
	int a[] = {10, 15};
	{
		SR x(j), y(a[0]), z(a[1]);

		j = a[0];
		a[0] = a[1];
		a[1] = j;

		printf("j = %d, a = {%d, %d}\n", j, a[0], a[1]);
	}

	printf("j = %d, a = {%d, %d}\n", j, a[0], a[1]);
}
