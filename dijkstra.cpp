#include <iostream>
#include <stdio.h>

using namespace std;

#define INFINITE	100000
#define ROW		9
#define COL		9
#define SWAP(t, A, B) { t temp = A; A = B; B = temp; }

template<typename T> class hNod{
	public:
		T dist;
		int id;
		int pred;
		hNod(T d=0, int i=0):dist(d),id(i) {}
		~hNod() {}

		hNod<T> & operator=(const hNod<T> &rhs) {
			if(this == &rhs) return *this;

			this->dist = rhs.dist;
			this->id= rhs.id;
			this->pred = rhs.pred;
			return *this;
		}
};

/* priority q(min heap) for find min */
template <typename T> class heap {
	public:
	hNod<T> *ph;
	int last;

	heap(){
		last = 0;
		ph = new hNod<T>[ROW];
	}
	~heap(){
		delete[] ph;
	}

	bool isEmpty() {
		if(!last) return true;
		else return false;
	}

	void xswap(hNod<T> &lhs, hNod<T> &rhs) {
		hNod<T> temp;
		temp = lhs;
		lhs = rhs;
		rhs = temp;
	}

	/* this rearrange should be done on heap arrary. 
	   If the arrary is not a heap, heapify() must be used.
	 */
	void rearrange(int idx) {
		int par, cur = idx, lc, rc;

		par = (int)((cur-1)/2);
		if(par <= 0) par = 0;

		while(ph[par].dist > ph[cur].dist) {
			xswap(ph[par], ph[cur]);
			cur = par;
			par = (int)((cur-1)/2);
			if(par<0) break;
		}

		lc = cur*2+1;
		rc = lc+1;
		while(lc < last) {
			if(ph[cur].dist <= ph[lc].dist && ph[cur].dist <= ph[rc].dist) {
				break;
			} else if(ph[rc].dist < ph[lc].dist) {
				xswap(ph[cur], ph[rc]);
				cur = rc;
				lc = cur*2+1;
				rc = lc + 1;
			} else {
				xswap(ph[cur], ph[lc]);
				cur = lc;
				lc = cur*2+1;
				rc = lc + 1;
			}
		}
	}

	void xinsert(T dist, int pred) {
		int par, cur = last;
		ph[cur].id = last;
		ph[cur].dist = dist;
		ph[cur].pred = pred;
		par = (int)((cur-1)/2);
		if(par<=0) par=0;

		while(ph[par].dist > ph[cur].dist) {
			xswap(ph[par], ph[cur]);
			cur = par;
			par = (int)((cur-1)/2);
		}
		last++;
	}

	hNod<T> xdequeue() {
		int child, cur = 0;
		hNod<T> data = ph[0];
		/* put the last node to the first pos */
		ph[0] = ph[last-1];
		/* move the first node down to correct position */
		child = cur*2 + 1;
		/* no child, that is, if leaf */
		if(child > last-2) {
			last -= 1;
			return data;
		} else {
			/* if there are children */
			while(child <= last-2) {
				/* there are two children */
				if(child+1 <= last-2) {
					if(ph[child].dist < ph[child+1].dist && ph[cur].dist > ph[child].dist) {
						xswap(ph[cur], ph[child]);
					} else if(ph[child+1].dist <= ph[child].dist && ph[cur].dist > ph[child+1].dist) {
						xswap(ph[cur], ph[child+1]);
					} else {
						last -= 1;
						return data;
					}
				} else {
				/* there is only one left child*/
					if(ph[cur].dist > ph[child].dist) {
						xswap(ph[cur], ph[child]);
						last -= 1;
						return data;
					} else {
						last -= 1;
						return data;
					}
				}

				cur = child;
				child = cur*2 + 1;
			}
			last -= 1;
			return data;
		}
	}
};

void dijkstraheap(int graph[][COL], int src)
{
	/*
	   build min-heap(priority Q)
	   while Q != empty
	   	v = minimum node of Q
		remove v from Q
		for u belonging to Adj(v) (BFS and relaxation)
			if d[u] > d[v] + w(v, u)
				d[u] = d[v] + w(v, u)
				predecessor(u) = v
	 */
	int u, i;
	hNod<int> v;
	heap<int> hip;
	/* initialize the Q */
	for(int i=0 ; i<ROW ; i++) {
		if(i == src) hip.xinsert(0, -1);
		else hip.xinsert(INFINITE, -1);
	}

	while(!hip.isEmpty()) {
		v = hip.xdequeue();
		printf("node : %d, dist : %d, pred : %d \n", v.id, v.dist, v.pred);
		for(u=0 ; u<ROW ; u++) {
			/* if v and u are not connected, set distance infinite */
			if(graph[v.id][u] == 0) graph[v.id][u] = INFINITE;
			/* find out the location of u(neighbor) in the heap */
			for(i=0 ; i<hip.last ; i++) {
				if(u == hip.ph[i].id) break;
			}
			/* if v == u */
			if (i == hip.last) continue; 
			if(hip.ph[i].dist > v.dist + graph[v.id][u]) {
				hip.ph[i].dist = v.dist + graph[v.id][u];
				hip.ph[i].pred = v.id;
				/* need to rearrange the heap */
				hip.rearrange(i);
			}
		}
	}
} 
int findmin(int *pn, int *q)
{
	int i, idx=0;
	int min = INFINITE; 
	for(i=0 ; i < ROW ; i++) {
		if(q[i] == 1 && pn[i] < min) {
			min = pn[i];
			idx = i;
		}
	}

	return idx;
}

void dijkstra(int graph[][COL], int src)
{
	/*
	   initialize q, distance, predecessor
	   while Q != empty
	   	v = minimum node of Q
		remove v from Q
		for u belonging to Adj(v) (BFS and relaxation)
			if d[u] > d[v] + w(v, u)
				d[u] = d[v] + w(v, u)
				predecessor(u) = v
	 */
	int i, v=0, u;
	int q[ROW], pred[ROW], d[ROW];

	/* initialize the Q */
	for(i=0 ; i<ROW ; i++) {
		if(i == src) d[i] = 0;
		else d[i] = INFINITE;
		q[i] = 1; /* 1 for valid node , -1 for removed node */
		pred[i] = -1;
	}

	i=0;
	while(i < ROW) {
		v = findmin(d, q); /* v is min node of Q*/
		q[v] = -1; /* remove v from Q*/
		for(u=0 ; u<ROW ; u++) {
			/* if v and u are not connected, set distance infinite */
			if(graph[v][u] == 0) graph[v][u] = INFINITE;
			/*if d[u] > d[v] + w(v, u)*/
			if(d[u] > d[v] + graph[v][u]) {
				d[u] = d[v] + graph[v][u]; 
				pred[u] = v;
			}
		}
		i++;
	}
	printf("shortest path \n");
	for(i=0 ; i<ROW; i++)
		printf("node : %d, dist : %d \n", i, d[i]);
	printf("predecessor \n");
	for(i=0 ; i<ROW; i++)
		printf("%d <- %d\n", pred[i], i);
	printf("\n");
}

int main()
{
	/* Let us create the example graph */
	int graph[ROW][COL] = {
		{0, 4, 0, 0, 0, 0, 0, 8, 0},
		{4, 0, 8, 0, 0, 0, 0, 11, 0},
		{0, 8, 0, 7, 0, 4, 0, 0, 2},
		{0, 0, 7, 0, 9, 14, 0, 0, 0},
		{0, 0, 0, 9, 0, 10, 0, 0, 0},
		{0, 0, 4, 0, 10, 0, 2, 0, 0},
		{0, 0, 0, 14, 0, 2, 0, 1, 6},
		{8, 11, 0, 0, 0, 0, 1, 0, 7},
		{0, 0, 2, 0, 0, 0, 6, 7, 0}
	};
	dijkstra(graph, 0);
	dijkstraheap(graph, 0);

	return 0;
}
