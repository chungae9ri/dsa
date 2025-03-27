#include <stdio.h>
#include <stdlib.h>

struct tdata {
	int k;
	char name[16];
	struct tdata *next; /* not used, but useful if used */
};

struct tnode {
	int sk, mk, lk;
	struct tnode *sn, *mn, *ln;
	struct tdata *sd, *md, *ld;
};

int getmaxkey(struct tnode *pn)
{
	if(pn->lk != 0) return pn->lk;
	else return pn->mk;
}

struct tnode *newtnode()
{
	struct tnode *pn = (struct tnode *)malloc(sizeof(struct tnode));
	pn->sk = pn->mk = pn->lk = 0;
	pn->sn = pn->mn = pn->ln = NULL;
	pn->sd = pn->md = pn->ld = NULL;
	return pn;
}
struct tdata *newtdata(int k) 
{
	struct tdata *pd = (struct tdata *)malloc(sizeof(struct tdata));
	pd->k = k;
	pd->next = NULL;

	return pd;
}

int findpos(struct tnode *pn, int k)
{
	if(k < pn->sk) return 0;
	else if(pn->mk == 0 ||(pn->sk <= k && k < pn->mk)) return 1;
	else if(pn->lk == 0 ||(pn->mk <= k && k < pn->lk)) return 2;
	else return 3;
}

void addson(struct tnode **ppv, int a, struct tnode **ppbro)
{
	int pos;
	struct tnode *tn, *b;
	struct tdata *td;
	struct tnode *pv = *ppv;
	struct tnode *pbro = *ppbro;

	*ppbro = (struct tnode *)NULL;

	if(pv->sd) {
		if(!pv->ld) {
			td = (struct tdata *)newtdata(a);
			pos = findpos(pv, a);

			if(pos == 0) {
				pv->ld = pv->md;
				pv->lk = pv->mk;
				pv->md = pv->sd;
				pv->mk = pv->sk;
				pv->sd = td;
				pv->sk = td->k;
			} else if(pos == 1) {
				pv->ld = pv->md;
				pv->lk = pv->mk;
				pv->md = td;
				pv->mk = td->k;
			} else {
				pv->ld = td;
				pv->lk = td->k;
			}
		} else {
			tn = (struct tnode *)newtnode();
			td = (struct tdata *)newtdata(a);
			pos = findpos(pv, a);

			if(pos == 0) {
				tn->md = pv->ld;
				tn->mk = pv->lk;
				tn->sd = pv->md;
				tn->sk = pv->mk;
				pv->md = pv->sd;
				pv->mk = pv->sk;
				pv->sd = td;
				pv->sk = td->k;
				pv->ld = NULL;
				pv->lk = 0;
				*ppbro = tn;
			} else if(pos == 1) {
				tn->md = pv->ld;
				tn->mk = pv->lk;
				tn->sd = pv->md;
				tn->sk = pv->mk;
				pv->md = td;
				pv->mk = td->k;
				pv->ld = NULL;
				pv->lk = 0;
				*ppbro = tn;
			} else if(pos == 2) {
				tn->md = pv->ld;
				tn->mk = pv->lk;
				tn->sd = td;
				tn->sk = td->k;
				pv->ld = NULL;
				pv->lk = 0;
				*ppbro = tn;
			} else {
				tn->md = td;
				tn->mk = td->k;
				tn->sd = pv->ld;
				tn->sk = pv->lk;
				pv->ln = NULL;
				pv->ld = NULL;
				pv->lk = 0;
				*ppbro = tn;
			}
		}
		return;
	}

	pos = findpos(pv, a);

	if(pos == 0) addson(&pv->sn, a, &b);
	else if(pos == 1 || !pv->ln) addson(&pv->mn, a, &b);
	else addson(&pv->ln, a, &b); 

	if(b) {
		/* already ordered sequence among pv->sn, pv->mn, pv->ln and b */
		if(!pv->ln) {
			if(pos == 0) {
				pv->ln = pv->mn;
				pv->lk = pv->mk;
				pv->mn = b;
				pv->mk = b->mk;
				pv->sk = pv->sn->mk;
			} else {
				pv->ln = b;
				pv->lk = b->mk;
				pv->mk = pv->mn->mk;
			} 
		} else {
			pbro = (struct tnode *)newtnode();
			if(pos == 0) {
				pbro->mn = pv->ln;
				pbro->mk = getmaxkey(pbro->mn);
				pbro->sn = pv->mn;
				pbro->sk = getmaxkey(pbro->sn);
				pv->sk = getmaxkey(pv->sn);
				pv->mn = b;
				pv->mk = getmaxkey(pv->mn);
			} else if(pos == 1) {
				pbro->mn = pv->ln;
				pbro->mk = getmaxkey(pbro->mn);
				pbro->sn = b;
				pbro->sk = getmaxkey(pbro->sn);
				pv->sk = getmaxkey(pv->sn);
				pv->mk = getmaxkey(pv->mn);
			} else {
				pbro->mn = b;
				pbro->mk = getmaxkey(pbro->mn);
				pbro->sn = pv->ln;
				pbro->sk = getmaxkey(pbro->sn);
			}
			pv->ln = NULL;
			pv->lk = 0;
			*ppbro = pbro;
		}
	} else {
		if(pos == 0) pv->sk = getmaxkey(pv->sn);
		else if(pos == 1 || !pv->ln) pv->mk = getmaxkey(pv->mn);
		else pv->lk = getmaxkey(pv->ln);
	}
}

void xinsert(struct tnode **pprt, int a)
{
	struct tnode *b, *nprt;
	struct tnode *prt = *pprt;
	struct tdata *pd;

	if(prt == NULL) { /* first insert */
		prt = (struct tnode *)newtnode();
		/*head = (struct tdata *)malloc(sizeof(struct tdata));*/
		pd = (struct tdata *)newtdata(a);
		prt->sk = a;
		prt->sd = pd;
		*pprt = prt;
		return;
	} else {
		/*b = (struct tnode *)newtnode();*/
		addson(&prt, a, &b);
	}

	if(b) {
		nprt = (struct tnode *)newtnode();
		nprt->sn = *pprt;
		if(prt->lk) nprt->sk = prt->mn->lk;
		else nprt->sk = prt->mk;
		nprt->mn = b;
		if(b->lk) nprt->mk = b->lk;
		else nprt->mk = b->mk;

		*pprt = nprt;
	}
}

int main()
{
	struct tnode *root;

	xinsert(&root, 50);
	xinsert(&root, 60);
	xinsert(&root, 70);
	xinsert(&root, 40);
	xinsert(&root, 30);
	xinsert(&root, 20);
	xinsert(&root, 10);
	xinsert(&root, 80);
	xinsert(&root, 100);
	xinsert(&root, 110);
	xinsert(&root, 120);
	xinsert(&root, 105);
	xinsert(&root, 106);
	xinsert(&root, 108);
	xinsert(&root, 109);

	int c, key;
	c = getchar();
	while(c != 'q') {
		if(c == 'i') {
			printf("input new key \n");
			scanf("%d", &key);
			xinsert(&root, key);
		}
		c = getchar();
	}
}
