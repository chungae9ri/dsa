#include <stdio.h>
/* for RAND_MAX */
#include <stdlib.h>
/* for using random number generator */
#include <time.h>

/* max random number */
#define RNUM	20

/* sort function */
void fsort(float *in, int len)
{
	int i, j;
	float temp;

	/* find out minimum value from input and put it to the leftmost index */
	for(i=0 ; i<len ; i++) 
		for(j=i ; j<len ; j++) {
			/* ascending order */
			if (in[i] >= in[j]) {
				temp = in[i];
				in[i] = in[j];
				in[j] = temp;
			}
		}
}

int main()
{
	int i, num;
	FILE *infp, *outfp;
	float rn, stretch = 4095.0f, *pin;

	/* input file open */
	if (!(infp = fopen("q2input.txt", "w"))) { 
		printf("can't open input file\r\n");
		return 0;
	}

	/* write the number to input file */
	fprintf(infp, "%d\r\n", RNUM);
	/* generate seed */
	srand(time(NULL));
	/* generate random number and write to input file */
	for (i=0 ; i<RNUM ; i++) {
		rn = (float)rand()/(float)RAND_MAX*stretch;
		fprintf(infp, "%f\r\n",rn);
	}

	/* input file close */
	fclose(infp);

	/* open input file */
	if (!(infp = fopen("q2input.txt", "r"))) { 
		printf("can't open input file\r\n");
		return 0;
	}

	/* open output file which will store the sorted number */
	if (!(outfp = fopen("q2output.txt", "w"))) {
		printf("can't open output file \r\n");
		fclose(infp);
		return 0;
	}

	/* get the number of input */
	fscanf(infp, "%d", &num);
	/* memory allocation */
	pin = (float *)malloc(sizeof(float) * num);

	/* get the input random number */
	for (i=0 ; i<num ; i++) {
		fscanf(infp, "%f", &pin[i]);
	}

	/* sort the input numbers in ascending order */
	fsort(pin, num);
	/* write number to output file*/
	fprintf(outfp, "%d\r\n", num);
	/* write it to output file*/
	for(i=0 ; i<num ; i++) {
		fprintf(outfp, "%f\r\n", pin[i]);
	}

	/* memory free and file close */
	free(pin);
	fclose(infp);
	fclose(outfp);

	return 1;
}
