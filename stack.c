/* Array type stack. Not dynamically alloc/free */
#include <stdio.h>
#include <stdlib.h>

#define MAX 5
struct sdata {
	int i;
	char name[16];
};

struct sdata *sp = NULL;
struct sdata *sbase = NULL;
int size = MAX;

int push(struct sdata ele)
{
	int ret = 0;
	int offset = 0;

	/* full increasing stack */
	if(sp) {
		offset = (sp-sbase)/sizeof(struct sdata);
		if(offset == size) {
			printf("overflow, realloc\n");
			size += MAX;
			if(!(sbase = realloc(sbase, size))) {
				printf("realloc fail\n");
				ret = -1;
				return ret;
			}
			sp = sbase + offset;
		} 
		sp++;
		sp->i = ele.i;
		strcpy(sp->name, ele.name);
	} else {
		sp = sbase;
		sp->i = ele.i;
		strcpy(sp->name, ele.name);
	}

	return ret;
}

struct sdata pop()
{
	struct sdata temp;
	temp = *(sp);
	if(sp == sbase) sp = NULL;
	else --sp;
	return temp;
}

int isempty()
{
	if(!sp) return 1;
	else return 0;
}

int main()
{
	int c;
	struct sdata temp;
	sbase = (struct sdata *)malloc(sizeof(struct sdata) * size);
	if(!sbase){
		printf("malloc fail\n");
		return -1;
	}
	c=getchar();
	while(c != 'q') {
		if(c == 'p') {
			printf("push data i :");
			scanf("%d", &temp.i);
			printf("push data name :");
			scanf("%s", temp.name);
			push(temp);
		} else if(c == 'o') {
			if(!isempty()){
				temp = pop();
				printf("pop data : %d, %s\n", temp.i, temp.name);
			} else printf("stack empty\n");
		} else if(c == 'e') {
			if(isempty() || !sp) printf("empty\n");
			else printf("not empty\n");
		}
		c = getchar();
	}
	free(sbase);
	return 0;
}
