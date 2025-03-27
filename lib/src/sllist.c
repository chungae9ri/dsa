/* single linked list imple with C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int age;
	char name[16];
	struct node *next;
};

static struct node *head = NULL;

/* print all */

void printall()
{
	struct node *pcur = head;

	while (pcur != NULL) {
		printf("name : %s, age : %d \n", pcur->name, pcur->age);
		pcur = pcur->next;
	}
}

/*insert*/
void xpush(char *str, int age)
{
	struct node *p = (struct node*)malloc(sizeof(struct node));

	strcpy(p->name, str);
	p->age = age;
	p->next = head;
	head = p;
	printall();
}

/*delete*/
void xdelete(char *str)
{
	struct node *pcur = head;
	struct node *pv = NULL;

	if (!pcur) return;

	while(pcur) {
		if (!strcmp(pcur->name, str)) {
			if (!pv) {
				head = pcur->next;
				free (pcur);
			} else {
				pv->next = pcur->next;
				free(pcur);
			}
			break;
		}

		pv = pcur;
		pcur = pcur->next;
	}

	printall();
}

int xfind(char *str)
{
	struct node *p = head;
	while (p != NULL) {
		if (!strcmp(p->name, str)) {
			return p->age;
		}
		p=p->next;
	}
	return -1;
}

/*xfree*/
void xfree()
{
	struct node *pcur = head;
	struct node *pn;
	if(pcur != NULL)
		pn = pcur->next;

	while (pcur != NULL) {
		printf("free : %s \n", pcur->name);
		free(pcur);
		pcur = NULL;
		if (pn != NULL) {
			pcur = pn;
			pn = pcur->next;
		} 
	}
}

int main()
{
	char str[16];
	int i, age=10, ret=0;

	while (i=getchar()) {
		if (i=='q') break;
		if (i=='p') {
			printf("input name: \n");
			scanf("%s",str);
			xpush(str, age++);
		} else if (i=='f') {
			printf("search name : \n");
			scanf("%s", str);
			ret = xfind(str);
			printf("ret : %d \n", ret);
		} else if (i=='d') {
			printf("xdelete name : \n");
			scanf("%s", str);
			xdelete(str);
		}
	}

	xfree();

	return 0;
}
