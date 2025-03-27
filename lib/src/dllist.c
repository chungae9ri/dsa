/* There is a skip linked list which is composed of groups of level of node.
   Node has several pointers to point to next node in each level of groups.
   This skip linked list is used for speeding up the search process in linked list.
 */
/* doubly linked list in c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int age;
	char name[16];
	struct node *next;
	struct node *prev;
};

struct node *head = NULL;

void showall()
{
	struct node *pcur = head;

	while(pcur) {
		printf("name : %s, age : %d\n", pcur->name, pcur->age);
		pcur = pcur->next;
	}
}

void xpush(char *str, int age) 
{
	struct node *p = (struct node *) malloc(sizeof(struct node));

	p->age = age;
	strcpy(p->name,str);
	p->next = head;
	p->prev = NULL;
	if(head) head->prev = p;
	head = p;
	showall();
}

void xdelete(char *str) 
{
	struct node *pcur = head;

	while(pcur) {
		if(!strcmp(pcur->name, str)) {
			if(pcur == head) {
				head = pcur->next;
				if(pcur->next) pcur->next->prev = NULL;
			} else {
				pcur->prev->next = pcur->next;
				if(pcur->next) pcur->next->prev = pcur->prev;
			}
			free(pcur);
		}

		pcur = pcur->next;
	}
	showall();
}

void xfree()
{
	struct node *pcur = head;
	struct node *pn;

	while(pcur) {
		pn = pcur->next;
		printf("free %s\n", pcur->name);
		free(pcur);
		pcur = pn;
	}

	head = NULL;
}

int xfind(char *str)
{
	struct node *pcur = head;

	while(pcur) {
		if(!strcmp(pcur->name,str)) {
			return pcur->age;
		}
		pcur = pcur->next;
	}

	return -1;
}

int main()
{
	int c, age=10, ret=0;
	char name[16];

	c=getchar();
	while(c != 'q') {
		if(c == 'p') {
			printf("input name : ");
			scanf("%s", name);
			xpush(name, age++);
		} else if(c == 'd') {
			printf("del name : ");
			scanf("%s", name);
			xdelete(name);
		} else if(c == 'f') {
			printf("find name : ");
			scanf("%s", name);
			ret = xfind(name);
			printf("age is : %d\n", ret);
		}
		c=getchar();
	}
	xfree();
}
