#include <stdio.h>

#if 0
int getbit(int n, int i)
{
	int mask;
	mask = 1 << i;
	return (n & mask) != 0;
}

int ftow(int n)
{
	int i, k, b = 0, sum = 0, max = 0;
	int num[32] = {0,};

	for(i=0, k=0 ; i<32 ; i++) {
		b = getbit(n, i);
		if(b) num[k]++;
		else k++;
	}

	for(i=0 ; i<k-1 ; i++) {
		sum = num[i] + num[i+1];
		if(sum > max) {
			max = sum;
		}
	}

	return max+1;
}

int main()
{
	int num = 0;
	num = ftow(192838);

	printf("num : %d \n", num);
	return 0;
}
#endif

#if 0
int main()
{
	int i, j, k;
	int a = 29, b = 15;

	i = j = k = 0;
	while(a>0) {
		i = a & 1;
		j = b & 1;
		if(i != j) k++;
		a = a>>1;
		b = b>>1;
	}

	printf("flip bit number is : %d \n", k);
	return 0;
}
#endif

int main()
{
	int e, o,em, om,r, a=29;
	e = a >> 1;
	o = a << 1;
	em = 0xaaaaaaaa;
	om = 0x55555555;
	r = (e & em) | (o & om);

	printf("0x%x bit swapped ret : 0x%x \n", a, r);
	return 0;
	
}








