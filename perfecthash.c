#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXLEN 130  /* length n */
#define INFINITE 100000;

struct tdata {
	int key;
	char name[16];
};

struct xi {
	int ai;
	int bi;
	int mi;
	int mi2;
	struct tdata *pd;
};

int prime[168] = {
	2,	3,	5,	7,	11,	13,	17,	19,	23,
	29,	31,	37,	41,	43,	47,	53,	59,	61,	67,
	71,	73,	79,	83,	89,	97,	101,	103,	107,	109,
	113,	127,	131,	137,	139,	149,	151,	157,	163,	167,
	173,	179,	181,	191,	193,	197,	199,	211,	223,	227,
	229,	233,	239,	241,	251,	257,	263,	269,	271,	277,
	281,	283,	293,	307,	311,	313,	317,	331,	337,	347,
	349,	353,	359,	367,	373,	379,	383,	389,	397,	401,
	409,	419,	421,	431,	433,	439,	443,	449,	457,	461,
	463,	467,	479,	487,	491,	499,	503,	509,	521,	523,
	541,	547,	557,	563,	569,	571,	577,	587,	593,	599,
	601,	607,	613,	617,	619,	631,	641,	643,	647,	653,
	659,	661,	673,	677,	683,	691,	701,	709,	719,	727,
	733,	739,	743,	751,	757,	761,	769,	773,	787,	797,
	809,	811,	821,	823,	827,	829,	839,	853,	857,	859,
	863,	877,	881,	883,	887,	907,	911,	919,	929,	937,
	941,	947,	953,	967,	971,	977,	983,	991,	997,	
};

int pickrn(int p)
{
	float stretch = (float)(p-1);
	return (int)((float)(rand())/(float)RAND_MAX * stretch);
}

void perfecthash(struct tdata *pd)
{
	int i, j, k, a, b, max=0;
	int perfect;
	int p, sumxi2 = INFINITE;
	int tempxi[MAXLEN][MAXLEN];

	struct xi *pxi = (struct xi *)malloc(sizeof(struct xi)*MAXLEN);

	for(i=0 ; i<MAXLEN ; i++) {
		if(pd[i].key > max) max = pd[i].key;
	}

	for(i=0 ; i<168 ; i++) {
		if(prime[i] > max) {
			p = prime[i];
			break;
		}
	}
	if(i == 168) {
		printf("no prime number exist\n");
		return;
	}

	// 1st stage hashing
	while(sumxi2 > 4*MAXLEN) {
		a = pickrn(p);
		if(!a) a++;
		b = pickrn(p);

		for(i=0 ; i<MAXLEN ; i++) {
			pxi[i].mi = 0;
			pxi[i].mi2 = 0;
		}

		for(i=0 ; i<MAXLEN ; i++) {
			j = ((a*(pd[i].key) + b) % p) % MAXLEN;
			tempxi[j][pxi[j].mi] = i;
			pxi[j].mi++;
		}

		sumxi2 = 0;

		for(i=0 ; i<MAXLEN ; i++) {
			pxi[i].mi2 = pxi[i].mi*pxi[i].mi;
			sumxi2 += pxi[i].mi2;
		}
	}

	// rehashing - 2nd stage hashing
	for(i=0 ; i<MAXLEN ; i++) {
		perfect = 0;
		if(pxi[i].mi == 0) continue;
		pxi[i].pd = (struct tdata *)malloc(sizeof(struct tdata)*pxi[i].mi2);
		if(pxi[i].mi2 == 1) {
			pxi[i].pd[0].key = pd[tempxi[i][0]].key;
			strcpy(pxi[i].pd[0].name, pd[tempxi[i][0]].name);
			continue;
		}
		while(!perfect) {
			for(j=0 ; j<pxi[i].mi2 ; j++) {
				pxi[i].pd[j].key = -1;
			}
			pxi[i].ai = pickrn(p);
			if(!pxi[i].ai) pxi[i].ai++;
			pxi[i].bi = pickrn(p);
			for(j=0 ; j<pxi[i].mi ; j++) {
				k = ((pxi[i].ai*(pd[tempxi[i][j]].key) + pxi[i].bi) % p) % pxi[i].mi2;
				if(pxi[i].pd[k].key != -1) {
					perfect = 0;
					break;
				} else {
					pxi[i].pd[k].key = pd[tempxi[i][j]].key;
					strcpy(pxi[i].pd[k].name, pd[tempxi[i][j]].name);
				}
			}

			if(j == pxi[i].mi) perfect = 1;
		}
	}

	printf("a : %d, b : %d \n", a, b);
	for(i=0 ; i<MAXLEN ; i++) {
		printf("m%d : %d, a%d : %d, b%d : %d\n", i, pxi[i].mi, i, pxi[i].ai, i, pxi[i].bi);
	}

	for(i=0 ; i<MAXLEN ; i++) {
		if(pxi[i].pd) free(pxi[i].pd);
	}

	free(pxi);
}

int main()
{
	int i, j, temp;
	struct tdata *pin = (struct tdata *)malloc(sizeof(struct tdata)*MAXLEN);
	float stretch = 512.f;

	srand(time(NULL));
	i=0;
	while(i < MAXLEN) {
		temp = (int)((float)(rand())/(float)RAND_MAX*stretch);
		for(j=0 ; j<i ; j++) {
			if(pin[j].key == temp) break;
		}
		if(j == i) {
			pin[i].key = temp;
			sprintf(pin[i].name, "%d", i);
			i++;
		}
	}

	perfecthash(pin);

	return 0;
}
