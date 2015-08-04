#include <stdio.h>
/* for using strlen() library*/
#include <string.h>

/* max input char length is 16 */
#define MAX_LEN 	16

/* global file pointer. As permute function is called recursively,
   I can't send the file pointer as a parameter.
   This file pointer can be accessed every recursive call. */
FILE *gfp;

/* Function to swap values at two pointers */
void swap (char *x, char *y)
{
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

/* Function to print permutations of string
   This function takes three parameters:
   a : array that stores user input.
   i : Starting index of the string
   n : Ending index of the string. */
void permute(char *a, int i, int n) 
{
	int j; 
	/* if the recursive call reaches the bottom(end),
	   it should save the current string to file(q1out.txt) and
	   it goes back the path.
	 */
	if (i == n) {
		/* add null string to mark the end of string */
		a[n+1] = '\0';
		/*printf("%s\r\n", a);*/
		/* save the string to file */
		fprintf(gfp,"%s\r\n", a);
	} else {
		/* get the swap index */
		for (j = i; j <= n; j++) {
			/* swap current index char with next index char */
			swap((a+i), (a+j));
			/* recursive call to go to next depth */
			permute(a, i+1, n);
			/* need to restore the swapped character for future use */
			swap((a+i), (a+j)); 
		}
	}
}

/* Function to modify user input character.
   If user character has non-alphabet like # ! space and repeated alphabet,
   then this fuction remove them all.
   So if user input a!b bAbc%d, then the output string should be abAcd.
   It also can be less than 3. If user input abaaa, then the output string is ab.
 */
int squeeze(char *in, char *out, int len)
{
	int i, j, cnt=0;

	/* at least one charater should be an alphabet. 
	   find the first alphabet and insert to out[0] */
	for (i=0 ; i<len ; i++) {
		/* if alphabet then inset it to out[0] and break 
		   cnt is used for out array index 
		 */
		if((in[i]>='A' && in[i] <='Z') || (in[i]>='a' && in[i]<= 'z')) {
			out [0] = in[i];
			cnt++;
			break;
		}
	}

	/* traverse in array and check if the char in in-array is already in out array or
	   the in-array char is not alphabet.
	   If it is, then drop that character 
	 */
	for (i=1 ; i<len ; i++) {
		for (j=0 ; j<cnt ; j++) {
			/* check repetition in out array or alphabet */
			if ( (in[i] == out[j]) || (!(in[i]>='A' && in[i] <='Z') && !(in[i]>='a' && in[i]<= 'z'))) {
				break;
			} 
		}
		/* if in char is not in out array, then insert it to out array*/
		if (j == cnt) {
			out[j] = in[i];
			cnt++;
			/* max out array len is 5 */
			if (cnt == 5) break;
		}
	}

	out[cnt] = '\0';
	printf("squeeze out unnecessary char. result :%s, cnt :%d \r\n", out, cnt);

	return cnt;
}

int main()
{
	char in[MAX_LEN], out[6];
	int len = 0;

	/* out file open */
	if (!(gfp = fopen("q1out.txt", "w"))) {
		printf("can't open file q1out.txt\r\n");
		return 0;
	}

	printf("input alphabet... [a-z][A-Z]..\r\n");
	/* get the user input char from stdin */
	fgets(in, sizeof(in), stdin);
	/* length of user input which is used in squeeze() */
	len = strlen(in);
	printf("input len :%d \r\n", len);

	/* remove all unnecessary char */
	len = squeeze(in, out, len);
	/* call the compute function*/
	permute(out, 0, len-1);

	printf("success!! permutation is stored in q1out.txt\r\n");

	/* file close */
	fclose(gfp);
	return 1;
}
