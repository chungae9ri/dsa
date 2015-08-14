#include <iostream>
#include <stdio.h>

using namespace std;

#define INFINITE	100000
#define ROW		9
#define COL		9

#if 0
template<typename T> class dijkstra{
	public:
		T wt;
		int idx;
		void getshortestdist(int **graph, int src);
		void 
};

template<typename T> void dijkstra<T>::getshortestdist(int **graph, int src) 
{
	

}
#endif

int findmin(int *pn, int len, int *q)
{
	int i, idx=0;
	int min = INFINITE; 
	for(i=0 ; i < len ; i++) {
		if(q[i] == 1 && pn[i] < min) {
			min = pn[i];
			idx = i;
		}
	}

	return idx;
}

void dijkstra(int graph[][COL], int src, int len)
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
	int i, v=0, u;
	int q[len], d[len], pred[len];

	/* initialize the Q */
	for(i=0 ; i<len ; i++) {
		if(i == src) d[i] = 0;
		else d[i] = INFINITE;
		q[i] = 1; /* 1 for valid node , -1 for removed node */
		pred[i] = -1;
	}

	i=0;
	while(i < len) {
		v = findmin(d, len, q); /* v is min node of Q*/
		q[v] = -1; /* remove v from Q*/
		for(u=0 ; u<len ; u++) {
			/* if not connected, set infinite */
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
	for(i=0 ; i<len; i++)
		printf("node : %d, dist : %d \n", i, d[i]);
	printf("predecessor \n");
	for(i=0 ; i<len; i++)
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
	dijkstra(graph, 0, ROW);

	return 0;
}
