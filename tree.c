/* 
   pretty heuristic in deletion. need to consider corner cases especailly in deletion.  
   insert is for recursive insertion. need to update the left/right pointer, 
   so address of left/right pointer should be delivered.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(A, B) (((A)>(B))?(A):(B))

struct tnode{
	int key; /* key */
	char name[16];
	struct tnode *par, *left, *right;
	int ht;  /* height, bal = r->ht - l->ht */
	int inc;
};

struct tnode *root = NULL;

/* rotate right */
void setht(struct tnode *pn)
{

	if(!pn->left && pn->right) pn->ht = pn->right->ht + 1;
	else if(!pn->right && pn->left) pn->ht = pn->left->ht + 1;
	else if(!pn->right && !pn->left) pn->ht = 0;
	else pn->ht = MAX(pn->right->ht, pn->left->ht) + 1;
}

void insert(struct tnode **pn, struct tnode tn)
{
	struct tnode *cur = *pn, *temp/* for swap */, *temp2;
	int bal = 0;
	if(!cur) {
		cur = (struct tnode*)malloc(sizeof(struct tnode));
		cur->left = NULL;
		cur->right = NULL;
		cur->key = tn.key;
		strcpy(cur->name, tn.name);
		/*cur->bal = 0;*/
		cur->ht = 0;
		cur->inc = 0;
		*pn = cur;
	} else {
		/* height increase when both children are null */
		if(!cur->left && !cur->right) {
			cur->ht += 1;
			cur->inc = 1;
		} else cur->inc = 0;

		if(tn.key < cur->key) {
			insert(&cur->left, tn);
			/* need to update height after insert. this is reverse order */
			if(!cur->left->par) cur->left->par = cur;
			if(cur->left->inc) {
				cur->left->inc = 0;
				setht(cur);
				cur->inc = 1;
			}
		} else {
			insert(&cur->right, tn);
			/* need to update height after insert. this is reverse order */
			if(!cur->right->par) cur->right->par = cur;
			if(cur->right->inc) {
				cur->right->inc = 0;
				setht(cur);
				cur->inc = 1;
			}
		}

		if(!cur->left) bal = cur->right->ht - (-1); /* height of NULL is -1 */
		else if(!cur->right) bal = (-1) - cur->left->ht; /* height of NULL is -1 */
		else bal = cur->right->ht - cur->left->ht;
		/* need to check balance factor after recursive */
		/* if balancing is broken */
		if(bal == 2) {
			/* right-right */
			if(tn.key >= cur->right->key) {
				/* case 1 : rotateleft(a)*/
				/* a                 b
				    \               / \ 
				     b     =>      a   c
				      \
				       c
				 */
				/* reconnect the linked list */
				/* there is swap if b has a left child */
				/* if cur is root */
				if(!cur->par) {
					root = cur->right;
				} else if(cur->par->right == cur) {
					cur->par->right =  cur->right;
				} else if(cur->par->left == cur) {
					cur->par->left = cur->right;
				} 
				temp = cur->right->left;
				cur->right->left = cur;
				cur->right->par = cur->par;
				cur->par = cur->right;
				if(temp) {
					cur->right = temp;
					temp->par = cur;
				} else cur->right = NULL;
				/* update cur(node a) height */
				setht(cur);
				setht(cur->par->right);
				setht(cur->par);

				cur->inc = 0;
				/* update cur->par(node b) height */
				/*cur->par->ht = cur->ht + 1;*/
				/* don't need to update bal since it will be updated in upper recursive code */
			} else { /* right-left */
				/* reconnect the linked list */
				/* there is no swap in this case */
				/* case 2 and case 3 has a same result */
				/* if root */
				if(!cur->par) {
					root = cur->right->left;
				} else if(cur->par->right == cur) {
				/* case 2 : rotateleft'(c)*/
				/*
				      a                 a
				     / \               / \
				    e   b     =>      e   d 
				         \               / \
					  c             b   c
					 /
				        d	
		 		*/
					cur->par->right = cur->right->left;
				} else if(cur->par->left == cur) {
				/* case 3 : rotateleft(b)  => rotateright(c) */
				/*
         	                        a              a                 a
				       / \            / \               / \
				      b   e   =>     c   e     =>      d   e
				       \            /                 / \
				        c          d                 b   c
				       /          /
				      d          b
				 */
					cur->par->left = cur->right->left;
				}
				cur->right->left->par = cur->par;
				temp2 = cur->right;
				if(temp2->left->left) {
					temp = temp2->left->left;
					temp2->left->left = cur;
					cur->right = temp;
				} else {
					temp2->left->left = cur;
					cur->right = NULL;
				}
				cur->par = temp2->left;
				if(temp2->left->right) {
					temp = temp2->left->right;
					cur->par->right = temp2;
					temp2->left = temp;
				} else {
					cur->par->right = temp2;
					temp2->left = NULL;
				}
				temp2->par = cur->par;
				/* update height */
				setht(cur);
				setht(cur->par->right);
				setht(cur->par);
				cur->inc = 0;
			} 
		} else if(bal == -2) {
			/* left - left */
			if(tn.key < cur->left->key) {
				/* case 4 : rotateright(a) */
				/*       a             b
				        /             / \
				       b     =>      c   a
				      /
			 	     c
				 */
				/* reconnect the linked list */
				/* if cur is root */
				if(!cur->par) {
					root = cur->left;
				} else if(cur->par->right == cur) {
					cur->par->right =  cur->left;
				} else if(cur->par->left == cur) {
					cur->par->left = cur->left;
				} 
				temp = cur->left->right;
				cur->left->right = cur;
				cur->left->par = cur->par;
				cur->par = cur->left;
				if(temp) {
					cur->left= temp;
					temp->par = cur;
				} else cur->left = NULL;
				/* update height */
				setht(cur);
				setht(cur->par->left);
				setht(cur->par);
				cur->inc = 0;
				/* don't need to update bal since it will be updated in upper recursive code */
			} else /* left-right */{
				if(!cur->par) {
					root = cur->left->right;
				} else if(cur->par->left == cur) {
				/* case 5 : rotateright'(b) */
				/*     a                 a   
				      / \               / \
				     b   e     =>      d   e
				    /                 / \
				   c                 c   b
				    \
				     d
				 */
					cur->par->left = cur->left->right;
				} else if(cur->par->right == cur) {
				/* case 6 : rotateright(b) => rotateleft(c) */
				/*
				       a                a                  a
				      / \              / \                / \
				     e   b    =>      e   c       =>     e   d
					/                  \                / \
				       c                    d              c   b
				        \                    \
					 d                    b
				 */
					cur->par->right = cur->left->right;
				}
				cur->left->right->par = cur->par;
				temp2 = cur->left;
				if(temp2->right->right) {
					temp = temp2->right->right;
					temp2->right->right = cur;
					cur->left = temp;
				} else {
					temp2->right->right = cur;
					cur->left = NULL;
				}
				cur->par = temp2->right;
				if(temp2->right->left) {
					temp = temp2->right->left;
					cur->par->left = temp2;
					temp2->right = temp;
				} else {
					cur->par->left = temp2;
					temp2->right = NULL;
				}
				/* update height */
				setht(cur);
				setht(cur->par->left);
				setht(cur->par);
			} 
		}
	}
}

void insertn(struct tnode n)
{
	struct tnode *cur;
	struct tnode *par;
	struct tnode *pn = (struct tnode *)malloc(sizeof(struct tnode));
	pn->key = n.key;
	strcpy(pn->name, n.name);
	pn->left = NULL;
	pn->right = NULL;

	if(!root) {
		root = pn;
		return;
	}
	cur = root;
	while(cur != NULL) {
		if(pn->key < cur->key) {
			par = cur;
			cur = cur->left;
		} else if(pn->key > cur->key){
			par = cur;
			cur = cur->right;
		} else { /* already there */
			free(pn);
			return;
		}
	}
	if(pn->key < par->key) par->left = pn;
	else par->right = pn;
}



struct tnode *findpredecessor(struct tnode *pn)
{
	struct tnode *cur;

	if(!pn) return NULL;
	
	cur = pn->left;
	if(!cur) return NULL;

	/* specially in this example, the node with biggest key of left children is the predecessor */
	while(cur->right) {
		cur = cur->right;
	}


	return cur;
}

struct tnode *findsuccessor(struct tnode *pn)
{
	struct tnode *cur;
	if(!pn) return NULL;
	
	cur = pn->right;
	if(!cur) return NULL;
	while(cur->left) {
		cur = cur->left;
	}
	return cur;
}

void remove(struct tnode n)
{
	
}

void delmerge(struct tnode n)
{
	struct tnode *cur = root;
	struct tnode *par = NULL;
	struct tnode *temp = NULL;

	while(cur) {
		if(cur->key < n.key){
			par = cur;
			cur = cur->right;
		} else if(cur->key > n.key) {
			par = cur;
			cur = cur->left;
		} else { /* found */
			/* case 1 : if cur is leaf*/
			if(!cur->left && !cur->right) {
				if(!par) {/* there is only a root node */
					free(cur);
					root = NULL;
				} else if(par->left == cur) {
					par->left = NULL;
					free(cur);
				} else if(par->right == cur) {
					par->right = NULL;
					free(cur);
				} 
			/* case 2 : if cur has only one child */
			} else if(!cur->left) {
				if(par) {
					if(par->left == cur) par->left = cur->right;
					else par->right = cur->right;
				} else {/* corner case when par is null, i.e. cur is root. */
					root = cur->right;
				}
				free(cur);
			} else if(!cur->right) {
				if(par) {
					if(par->left == cur) par->left = cur->left;
					else par->right = cur->right;
				} else {/* corner case when par is null, i.e. cur is root. */
					root = cur->left;
				}
				free(cur);
			/* case 3 : if cur has two children, merge subtrees. 
			 */
			} else {
				temp = findpredecessor(cur);
				temp->right= cur->right;
				if(par) {
					if(par->left == cur) par->left = cur->left;
					else if(par->right == cur) par->right = cur->left;
				} else { /* corner case when par is null, i.e. cur is root. */
					if(temp != cur->left) temp->left = cur->left;
					root = temp;
				}
				free(cur);
			}
			break;
		}
	}
}

struct tnode *search(struct tnode n)
{
	struct tnode *cur = root;

	while(cur) {
		if(cur->key < n.key) {
			cur = cur->right;
		} else if(cur->key > n.key) {
			cur = cur->left;
		} else {
			break;
		}
	}

	return cur;
}

void deletetree(struct tnode *pn)
{
	struct tnode *temp;
	if(!pn) return;
	else {
		deletetree(pn->left);
		temp = pn->right;
		free(pn);
		deletetree(temp);
	}
}

void traverse(struct tnode *pn)
{
	if(!pn) return;
	else {
		traverse(pn->left);
		printf("cur is %s, key : %d\n", pn->name, pn->key);
		traverse(pn->right);
	}
}

int main()
{
	int i, c, key;
	char name[16];
	struct tnode tn;
	struct tnode *pn;
	tn.name[0] = 'a'-1;

	for(i=0 ; i<26 ; i++) {
		tn.name[0] += 1; 
		tn.name[1] = '\0';
		tn.key = i+1;
		//insertn(tn);
		insert(&root, tn);
	}
	c = getchar();
	while(c != 'q') {
		if(c == 'p') {
			printf("input name :");
			scanf("%s", tn.name);
			printf("input key : ");
			scanf("%d", &tn.key);
			/*insertn(tn);*/
			insert(&root, tn);
		} else if(c == 'd') {
			printf("remove key : ");
			scanf("%d", &tn.key);
			delmerge(tn);
		} else if(c == 's') {
			printf("search key : ");
			scanf("%d", &tn.key);
			pn = search(tn);
			if(pn) printf("search name : %s\n",pn->name);
			else printf("key %d is not in tree\n", tn.key);
		}
		c = getchar();
	}
	traverse(root);
	deletetree(root);
	return 0;
}
