/* 
   pretty heuristic in deletion. need to consider corner cases especailly in deletion.  
   insert is for recursive insertion. need to update the left/right pointer, 
   so address of left/right pointer should be delivered.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* max random number */
#define RNUM 100

#define MAX(A, B) (((A)>(B))?(A):(B))

struct tnode{
	int key; /* key */
	char name[16];
	/* doubly linked list. par is to parent. */
	struct tnode *par, *left, *right;
	int ht;  /* height, bal = r->ht - l->ht */
	int inc;
};

struct tnode *root = NULL;
struct tnode *prev = NULL; 
struct tnode *successor = NULL;

void traverse(struct tnode *pn);

void setht(struct tnode *pn)
{
	if(!pn->left && pn->right) pn->ht = pn->right->ht + 1;
	else if(!pn->right && pn->left) pn->ht = pn->left->ht + 1;
	else if(!pn->right && !pn->left) pn->ht = 0;
	else pn->ht = MAX(pn->right->ht, pn->left->ht) + 1;
}

/* rotate right for zig-zig (A, B, C) */
/*       a             b
        /             / \
       b     =>      c   a
      /
     c
 */
void rr(struct tnode *pn)
{
	struct tnode *cur = pn;
	struct tnode *temp1 = cur->left; /* for left child */

	if(cur->par) {
		if(cur->par->right == cur) {
			cur->par->right = temp1;
			temp1->par= cur->par;
		} else {
			cur->par->left = temp1;
			temp1->par = cur->par;
		}

	} else {
		root = temp1;
		temp1->par = NULL;
	}

	if(temp1->right) {
		cur->left = temp1->right;
		temp1->right->par = cur;
	} else cur->left = NULL;

	temp1->right = cur;
	cur->par = temp1;

	setht(cur);
	setht(temp1);
}

/* rotate left for zag-zag (A, B, C) */
/* a                 b
    \               / \ 
     b     =>      a   c
      \
       c
 */
void rl(struct tnode *pn)
{
	struct tnode *cur = pn;
	struct tnode *temp1 = cur->right; /* for right child */

	if(cur->par) {
		if(cur->par->right == cur) {
			cur->par->right = temp1;
			temp1->par = cur->par;
		} else {
			cur->par->left = temp1;
			temp1->par = cur->par;
		}

	} else {
		root = temp1;
		temp1->par = NULL;
	}

	if(temp1->left) {
		cur->right = temp1->left;
		temp1->left->par = cur;
	} else cur->right = NULL;

	temp1->left = cur;
	cur->par = temp1;

	setht(cur);
	setht(temp1);
}

/* double rotate right and left for zig-zag(A, B, C) */
/*
	a              a                 a
       / \            / \               / \
      b   e   =>     b   e     =>      d   e
       \              \               / \
        c              d             b   c
       /                \
      d                  c
 */
void rrl(struct tnode *pn)
{
	struct tnode *cur = pn;
	struct tnode *temp1 = cur->right;
	struct tnode *temp2 = temp1->left;

	rr(temp1);
	rl(cur);
	/*
	setht(cur);
	setht(temp1);
	setht(temp2);
	*/
}

/* double rotate left and right for zig-zag(A, B, C) */
/*
       a                a                  a
      / \              / \                / \
     e   b    =>      e   b       =>     e   d
	/                /                  / \
       c                d                  c   b
        \              / 
	 d            c
 */
void rlr(struct tnode *pn)
{
	struct tnode *cur = pn;
	struct tnode *temp1 = cur->left;
	struct tnode *temp2 = temp1->right;

	rl(temp1);
	rr(cur);
	/*
	setht(cur);
	setht(temp1);
	setht(temp2);
	*/
}

int calcbal(struct tnode *pn)
{
	int bal; 
	struct tnode *cur = pn;

	if(!cur->left && !cur->right) {
		bal = 0;
	} else if(!cur->left && cur->right) {
		bal = cur->right->ht - (-1); /* height of NULL is -1 */
	} else if(!cur->right && cur->left) {
		bal = (-1) - cur->left->ht; /* height of NULL is -1 */
	} else {
		bal = cur->right->ht - cur->left->ht;
	}
	return bal;
}

void rebalance(struct tnode *pn)
{
	struct tnode *cur = pn;
	struct tnode *temp, *tempright, *templeft;
	int bal = 0;

	bal = calcbal(cur);

	if(bal == 2) {
		temp = cur->right;
		tempright = temp->right;
		templeft = temp->left;
		/* rotation left is enough for rebalance */
		if(tempright && templeft) {
			if(tempright->ht >= templeft->ht) {
				rl(cur);
			} else {
				rrl(cur);
			}
		} else if(tempright && !templeft) {
			rl(cur);
		} else if(templeft && !tempright) {
			rrl(cur);
		} else {
			printf("should not see this 1 \n");
		}
	} else if (bal == -2) {
		temp = cur->left;
		tempright = temp->right;
		templeft = temp->left;

		if(tempright && templeft) {
			if(templeft->ht >= tempright->ht) {
				rr(cur);
			} else {
				rlr(cur);
			}
		} else if(templeft && !tempright) {
			rr(cur);
		} else if(tempright && !templeft) {
			rlr(cur);
		} else {
			printf("should not see this 2 \n");
		}
	} else {
		/* only set the height correctly */
		setht(cur);
	}
}

void setht_successor(struct tnode *pn)
{
	struct tnode *cur = pn;

	if(!cur) {
		return;
	} else {
		setht_successor(cur->left);
		setht(cur);
	}
}
 
void rebalance_successor(struct tnode *pn)
{
	struct tnode *cur = pn;
	if(!cur) {
		return;
	} else {
		rebalance_successor(cur->left);
		rebalance(cur);
	}
}


void xinsert(struct tnode **pn, struct tnode tn)
{
	struct tnode *cur = *pn, *temp/* for swap */, *temp2, *temp3;
	int bal = 0;
	if(!cur) {
		cur = (struct tnode*)malloc(sizeof(struct tnode));
		cur->left = NULL;
		cur->right = NULL;
		cur->par = NULL;
		cur->key = tn.key;
		strcpy(cur->name, tn.name);
		/*cur->bal = 0;*/
		cur->ht = 0;
		cur->inc = 0;
		*pn = cur;
		return;
	} else {
		/* don't insert the same key */
		if(tn.key == cur->key) {
			/*printf("already there key : %d \n", tn.key);*/
			return;
		}

		/* height increase when both children are null */
		if(!cur->left && !cur->right) {
			cur->ht += 1;
			cur->inc = 1;
		} else cur->inc = 0;

		if(tn.key < cur->key) {
			xinsert(&cur->left, tn);
			/* need to update height after insert. this is reverse order */
			if(!cur->left->par) cur->left->par = cur;
			if(cur->left->inc) {
				cur->left->inc = 0;
				setht(cur);
				cur->inc = 1;
			}
		} else {
			xinsert(&cur->right, tn);
			/* need to update height after insert. this is reverse order */
			if(!cur->right->par) cur->right->par = cur;
			if(cur->right->inc) {
				cur->right->inc = 0;
				setht(cur);
				cur->inc = 1;
			}
		} 

		bal = calcbal(cur);

		/* need to check balance factor after recursive */
		/* if balancing is broken */
		if(bal == 2) {
			if(tn.key >= cur->right->key) {
				/* case 1 : right-right */
				rl(cur);
				cur->inc = 0;
			} else { 
				/* case 2 : right-left */
				rrl(cur);
				cur->inc = 0;
			} 
		} else if(bal == -2) {
			if(tn.key < cur->left->key) {
				/* case 3: left - left */
				rr(cur);
				cur->inc = 0;
			} else {
				/* case 4: left-right */
				rlr(cur);
				cur->inc = 0;
			} 
		}
	}
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

void xdelete(struct tnode **pn, struct tnode tn)
{
	int bal = 0;
	struct tnode *cur = *pn;
	/*struct tnode *successor;*/
	struct tnode *temp;

	if(!cur) {
		return;
	} else {
		if(cur->key == tn.key) {
			/* case 1 : if cur is leaf*/
			if(!cur->left && !cur->right) {
				if(!cur->par) {/* there is only a root node */
					free(cur);
					/*prev = cur;*/
					cur = NULL;
					root = NULL;
				} else if(cur->par->left == cur) {
					cur->par->left = NULL;
					free(cur);
					/*prev = cur;*/
					cur = NULL;
				} else if(cur->par->right == cur) {
					cur->par->right = NULL;
					free(cur);
					/*prev = cur;*/
					cur = NULL;
				} 
				/* case 2 : if cur has only one child */
			} else if(cur->right && !cur->left) {
				if(cur->par) {
					if(cur->par->left == cur) {
						cur->par->left = cur->right;
						cur->right->par = cur->par;
					} else {
						cur->par->right = cur->right;
						cur->right->par = cur->par;
					}
				} else {/* corner case when par is null, i.e. cur is root. */
					root = cur->right;
					cur->right->par = NULL;
				}
				free(cur);
				/*prev = cur;*/
				cur = NULL;
				/* case 2 : if cur has only one child */
			} else if(cur->left && !cur->right) {
				if(cur->par) {
					if(cur->par->left == cur) {
						cur->par->left = cur->left;
						cur->left->par = cur->par;
					} else {
						cur->par->right = cur->left;
						cur->left->par = cur->par;
					}
				} else {/* corner case when par is null, i.e. cur is root. */
					root = cur->left;
					cur->left->par = NULL;
				}
				free(cur);
				/*prev = cur;*/
				cur = NULL;
				/* case 3 : if cur has two children, replace it with successor */
			} else {
				successor = findsuccessor(cur);
				if(successor) {
					/* if successor is not right child of cur */
					if(successor->par != cur) {
						successor->par->left = successor->right;
						if(successor->right) successor->right->par = successor->par;
						successor->left = cur->left;
						if(cur->left) cur->left->par = successor;
						successor->right = cur->right;
						if(cur->right) cur->right->par = successor;
						/* if cur is not root */
						if(cur->par) {
							if(cur->par->right == cur) {
								cur->par->right = successor;
								successor->par = cur->par;
							} else {
								cur->par->left = successor;
								successor->par = cur->par;
							}
							/* if cur is root */
						} else {
							root = successor;
							successor->par = NULL;
						}
						free(cur);
						/*prev = cur;*/
						cur = NULL;
						/* recalc successor & right child's height. */
						setht_successor(successor->right);
						setht(successor);
						/* successor and successor->right's balancing should be checked */
						rebalance_successor(successor->right);
						rebalance(successor);
					} else {
						/* if successor is right child of cur */
						successor->left = cur->left;
						if(cur->left) cur->left->par = successor;
						/* if cur is not root */
						if(cur->par) {
							if(cur->par->right == cur) {
								cur->par->right = successor;
								successor->par = cur->par;
							} else {
								cur->par->left = successor;
								successor->par = cur->par;
							}
							/* if cur is root */
						} else {
							root = successor;
							successor->par = NULL;
						}

						free(cur);
						/*prev = cur;*/
						cur = NULL;
						/* recalc only successor(right child) height. 
						   right child is a successor. */
						setht(successor);
						/* successor's balancing should be checked */
						rebalance(successor);
					}
				}
			}
		} else if(tn.key < cur->key) {
			xdelete(&cur->left, tn);
			setht(cur);
		} else {
			xdelete(&cur->right, tn);
			setht(cur);
		}

		if(cur) {
			bal = calcbal(cur);
			if(bal == 2 || bal == -2) {
				rebalance(cur);
				/* rebalance one time is not enough in some cases. 
				   need to rebalance again.
				 */
				if(cur == cur->par->left) {
					rebalance(cur->par->right);
				} else {
					rebalance(cur->par->left);
				}
				rebalance(cur->par);
			}
		}
	}
}

/* simple but not used for rebalancing */
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
		printf("delete tree : %s, key : %d\n", pn->name, pn->key);
		free(pn);
		pn = NULL;
		deletetree(temp);
	}
}

void traverse(struct tnode *pn)
{
	int ht;
	int bal = 0;
	struct tnode *cur = pn;
	if(!cur) return;
	else {
		traverse(cur->left);
		if(!cur->left && cur->right) {
			ht = cur->right->ht + 1;
			bal = cur->right->ht - (-1);
		}
		else if(!cur->right && cur->left) {
			ht = cur->left->ht + 1;
			bal = (-1) - cur->left->ht;
		}
		else if(!cur->right && !cur->left) {
			ht = 0;
			bal = 0;
		}
		else {
			ht = MAX(cur->right->ht, cur->left->ht) + 1;
			bal = cur->right->ht - cur->left->ht;
		}

		if(cur->ht != ht) {
			printf("ht is inconsistent\n");
			printf("cur is %s, key : %d\n", cur->name, cur->key);
		}
		if(bal >=2 || bal <= -2) {
			printf("before bal is : %d \n", bal);
			printf("cur is %s, key : %d\n", cur->name, cur->key);
		}
		traverse(cur->right);
	}
}

int main()
{
	int i, c, key;
	char name[16];
	struct tnode tn;
	float rn, stretch = 100000;
#if 0
	tn.name[0] = 'a'-1;
	for(i=0 ; i<100 ; i++) {
		sprintf(tn.name, "%d", i);
		tn.key = i+1;
		//xinsertn(tn);
		xinsert(&root, tn);
	}

#endif
#if 0
	c = getchar();
	while(c != 'q') {
		if(c == 'i') {
			printf("insert name : \n");
			scanf("%s", tn.name);
			printf("insert key : \n");
			scanf("%d", &tn.key);
			xinsert(&root, tn);
		} else if(c == 'd') {
			printf("delete key : \n");
			scanf("%d", &tn.key);
			xdelete(&root, tn);
		}
		c = getchar();
		traverse(root);
	}
#endif
#if 1
	srand(time(NULL));
	
	do {
		/*deletetree(root);*/
		for(i=0 ; i<100000; i++) {
			/* insert node */
			rn = (float)((float)rand()/(float)RAND_MAX*stretch);
			tn.key = (int)rn;
			sprintf(tn.name, "%d", i);
			xinsert(&root, tn);
		}
		for(i=0 ; i<100000; i++) {
			/* delete node */
	/*printf("delete node \n");*/
			rn = (float)((float)rand()/(float)RAND_MAX*stretch);
			tn.key = (int)rn;
			xdelete(&root, tn);
		}
		traverse(root);
		printf("press enter to continue test \n");
		c = getchar();
	} while(c != 'q');
#endif
	/*traverse(root);*/
	deletetree(root);
	return 0;
}
