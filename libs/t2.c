#include <stdio.h>

void testrecur(int n)
{
	if(n==0) {
		return;
	}
	printf("before n : %d \n", n);
	n--;
	testrecur(n);
	printf("after 1 n : %d \n", n);
	testrecur(n);
	printf("after 4 n : %d \n", n);

}

int main()
{
	testrecur(5);

	return 0;
}
