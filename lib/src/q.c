#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct qnode{
	int age;
	char name[16];
	struct qnode *next;
};

struct qnode *head = NULL;

void enq(struct qnode el)
{
	struct qnode *n = (struct qnode *)malloc(sizeof(struct qnode));
	struct qnode *cur;
	n->age = el.age;
	strcpy(n->name, el.name);
	n->next = NULL;
	/* put behind */
	if(!head) {
		head = n;
	} else {
		cur = head;
		while(cur->next) {
			cur = cur->next;
		}
		cur->next = n;
	}
}

struct qnode *deq()
{
	struct qnode *cur;
	if(!head) {
		return NULL;
	} else {
		cur = head;
		if(head->next) {
			head = cur->next;
		} else head = NULL;

		return cur;
	}
}

void xfree()
{
	struct qnode *cur=head;
	while(cur) {
		cur = cur->next;
		free(head);
		head = cur;
	}
}

int main()
{
	int c, age;
	char name[16];
	struct qnode el;
	struct qnode *pel;

	c = getchar();
	while(c != 'q') {
		if(c=='p') {
			printf("input name : ");
			scanf("%s", el.name);
			printf("input age : ");
			scanf("%d", &el.age);
			enq(el);
		} else if(c=='d') {
			pel = deq();
			printf("dequeue name : %s\n", pel->name);
			printf("dequeue age : %d\n", pel->age);
			free(pel);
		}
		c=getchar();
	}
	xfree();
	return 0;
}
