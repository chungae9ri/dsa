#include <iostream>

using namespace std;

int main()
{
	int a[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

	int **pa = a;

	printf("%d \n", a[1][1]);
	printf("%d \n", pa[1][1]);

	return 0;
}

