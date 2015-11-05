#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "classes.h"

using namespace std;

int main()
{
	int i, j, k, wt;
	float vtxst, wtst;
	Vertex<int> *pVertex;
	Edge<int> *pe;

	/* alloc vertex array */
	pVertex = new Vertex<int> [VERTEXNUM];
	/* init vertex idx from 0 to 4999 */
	for(i=0 ; i<VERTEXNUM ; i++) {
		pVertex[i].init(i);
	}

	srand(time(NULL));

	/* random number(vertex idx) used as 
	   the neighbor of current vertex */
	vtxst = VERTEXNUM*1.0f;
	/* random number(weight of edge) used as 
	   the weight of edge */
	wtst = WEIGHTRANGE*1.0f;

	/* for each VERTEXNUM(5000) do
	   for each EDGENUM do
	   generate edges*/
	for(i=0 ; i<VERTEXNUM ; i++) {
		for(j=0 ; j<EDGENUM ; ) {
			wt = 0;
			/* generate the idx of neighbor vertex */
			k = (int)(((float)rand()/(float)RAND_MAX)*vtxst);
			/* generate the weight of edge.
			   edge weight is not 0 */
			while(wt == 0) wt = (int)(((float)rand()/(float)RAND_MAX)*wtst); 
			pe = new Edge<int>(i, k, wt);
			/* if edge is successfully added
			   then increase the edge num */
			if(pVertex[i].addEdge(pe)) {
				j++;
			} else {
				/* if edge is already there, 
				   then remove malloced mem */
				delete pe;
			}
		}
	}


	/* check if the generated graph is correct or not 
	   for each vertex do
	   check the edge is correct.
	   correct means that there is not same edge. */
	for(i=0 ; i<VERTEXNUM ; i++) {
		pe = pVertex[i].Head;
		Edge<int> *pe2;	
		for(j=0 ; j<EDGENUM ; j++) {
			pe2 = pe->next;
			while(pe2) {
				if((pe->v == pe2->v && pe->w == pe2->w)||(pe->w == pe2->v && pe->v == pe2->w)) {
					cout << "fail !! "<< endl;
				}
				pe2 = pe2->next;

			}
			pe = pe->next;
		}

		if(j != EDGENUM) cout << "not correct edge num : " << j << endl;
	}

	delete[] pVertex;
	return 0;
}
