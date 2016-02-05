#include <stdio.h>

void PrintSubsets() 
{ 
	int source[3] = {1,2,3}; 
	int currentSubset = 7; 
	int tmp; 
	int i;
	while(currentSubset) 
	{ 
		printf("("); 
		tmp = currentSubset; 
		for(i = 0; i<3; i++) 
		{ 
			if (tmp & 1) 
				printf("%d ", source[i]); 
			tmp >>= 1; 
		} 
		printf(")\n"); 
		currentSubset--; 
	} 
}
void subset()
{
	int i;
	int tmp;
	int source[4] = {1, 2, 3,4};
	int maxnum = 15;

	while(maxnum) {
		tmp = maxnum;
		for(i=0 ; i<4 ; i++) { 
			if(tmp & 1<<i) printf("%d", source[i]);
		}
		printf("\n");
		maxnum -= 1;
	}
}

int main()
{
	PrintSubsets();
	subset();
	return 0;
}


