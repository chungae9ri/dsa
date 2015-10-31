#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main()
{
#if 1

	int i, j, k, l, rem;
	int *m;
	int T1[10] = {1,39, 41, 45, 50, 55, 56, 57, 80,83};
	int T2[6] ={3, 30, 38, 44, 48, 60};

	m = (int *)malloc(16*sizeof(int));

	i = j = k= 0;

	while(i<10 && j<6)  {
		while(T1[i] < T2[j]) {
			m[k++] = T1[i++];
		}
		while(T1[i] > T2[j]) {
			m[k++] = T2[j++];
		}
	}

	if(j==6 && i < 10) { 
		rem = 10-i;
		for(l=0 ; l< rem ; l++)
			m[k++] = T1[i++];
	} else if(j < 6 && i == 10) {
		rem  = 6-j;
		for(l=0 ; l<rem ; l++) 
			m[k++] = T2[j++];
	}

#else
	int i, j,k;
	int *m;
	int T1[10] = {1,39, 41, 45, 50, 55, 56, 57, 80,83};
	int T2[6] ={3, 30, 38, 44, 48, 60};

	m = (int *)malloc(16*sizeof(int));

	for(i=0, j=0, k=0 ; i<16 ; i++) {
		if(k >= 6) {
			m[i] = T1[j];
			j++;
		} else if(T1[j] < T2[k]) {
			m[i] = T1[j];
			j++;
		} else {
			m[i] = T2[k];
			k++;
		}
	}
#endif

	for(i=0 ; i<16 ; i++) {
		printf("m[%d] : %d\n", i, m[i]);
	}

	return 1;
}
