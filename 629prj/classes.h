#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

#define VERTEXNUM	5000	
#define EDGENUM		6
#define WEIGHTRANGE	100	
#define UNSEEN 		0x1
#define FRINGE		0x10
#define INTREE		0x100

template <typename T> class Vertex ;

/* class edge of Graph */
template <typename T> class Edge {
	public:
		/* wt is for weight of edge */
		T wt;
		/* v, w are the vertices of the edge*/
		int v, w;
		/* doubly linked list of edges of current vertex */
		Edge<T> *next;
		Edge<T> *prev;

		/* operator overloading */
		int operator==(const Edge<int> *pe) {
			if((pe->v == this->v && pe->w == this->w) 
		        	||(pe->w == this->v && pe->v == this->w))
				return 1;
			else return 0;
		}

		Edge() {
		}

		void setWt(T weight) {
			wt = weight;
		}
		T getWt() {
			return wt;
		}

		/* edge constructor which sets the begin, end vertices and weight */
		Edge(int vv, int ww, T d):v(vv), w(ww), wt(d) {
			next = NULL;
			prev = NULL;
		}
		~Edge() {
		}
};

/* vertex class */
template <typename T> class Vertex {
	public:
		/* vertex weight */
		T Cap;
		/* vertex idx. idx is one of 1, 2,..., n */
		int idx;
		int status;
		int Dad;
		/* head of linked list of edges belonging to current vertex */
		Edge<T> *Head;

		Vertex() {
		}

		/* destructor of vertex*/
		~Vertex () {
			Edge<T> *pe;
			pe = Head;
			/* vertex destructor need to free the linked 
			   list of edges belonging to current vertex */
			while(pe) {
				Head = pe->next;
				delete pe;
				pe = Head;
			}
		}

		/* vertex init member func. */
		void init(int i) {
			idx = i;
			Head = NULL;
			Cap = 0;
			Dad = -1;
			status = UNSEEN;
		}

		Edge<T>* getHead() {
			return Head;
		}

		int getIdx() {
			return idx;
		}

		void setStatus(int stat) {
			status = stat;
		}
		int getStatus() {
			return status;
		}
		void setDad(int d) {
			Dad = d;
		}
		int getDad() {
			return Dad;
		}

		void setCap(T wt) {
			Cap = wt;
		}
		T getCap() {
			return Cap;
		}

		/* add edge to current vertex */
		int addEdge(Edge<T> *e) {
			Edge<T> *pe = Head;

			while(pe) {
				/* if current edge is already in the edge list, 
				   then donot add and return */
				/*if(pe == e) {*/
				if((pe->v == e->v && pe->w == e->w) || (pe->w == e->v && pe->v == e->w)) {
					/*cout << "already there " << e->v << ", " << e->w << endl;*/
					return 0;
				}
				pe = pe->next;
			}

			/* add new edge to the first location of the edge list */
			if(Head) {
				e->next = Head;
				Head->prev = e;
				Head = e;
			} else {
				Head = e;
			}
			return 1;
		}
};

template<typename T> class VertexArr {
	public:
		Vertex<T> *pVertex;
		VertexArr() {
			int i;
			pVertex = new Vertex<T> [VERTEXNUM];
			for(i=0 ; i<VERTEXNUM ; i++) {
				pVertex[i].init(i);
			}
		}
		~VertexArr() {
			if(pVertex) delete[] pVertex;
		}

		Vertex<T>& getVertex(int idx) {
			return pVertex[idx];
		}
};

template<typename T> class Graph {
	public : 
		VertexArr<T> Varr;

		Graph() {
			/*pVarr = new VertexArr();*/
		}
		~Graph() {
			/*delete pVarr;*/
		}

		VertexArr<T>& getVertexArr() {
			return Varr;
		}

		void genGraph(int s, int t) {
			int i, j, k, wt;
			float vtxst, wtst;
			Edge<T> *pe;

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
					/* generate the weight of edge.
					   edge weight is not 0 */
					while(wt == 0) wt = (int)(((float)rand()/(float)RAND_MAX)*wtst); 
					/* generate the idx of neighbor vertex */
					/* if i is target then connect it to the source for making
					   path from source to target */
					if(i == t && j == 0) {
						k = s;
					} else {
						k = (int)(((float)rand()/(float)RAND_MAX)*vtxst);
					}
					pe = new Edge<int>(i, k, wt);
					/* if edge is successfully added
					   then increase the edge num */
					if(Varr.getVertex(i).addEdge(pe)) {
						j++;
					} else {
						/* if edge is already there, 
						   then remove malloced mem */
						delete pe;
					}
				}
			}

		}

		bool chkGraph(int s, int t) {
			int i, j;
			Edge<T> *pe;
			/* check if the generated graph is correct or not 
			   for each vertex do
			   check the edge is correct.
			   correct means that there is not same edge. */
			for(i=0 ; i<VERTEXNUM ; i++) {
				pe = Varr.getVertex(i).Head;
				Edge<int> *pe2;	
				for(j=0 ; j<EDGENUM ; j++) {
					/* check the graph has a path connecting source and target */
					if(i == t && j == EDGENUM-1) {
						if(pe->w != s) {
							cout << "there is not a path connecting source and target" << endl;
							return false;
						}
					}
					pe2 = pe->next;
					while(pe2) {
						if((pe->v == pe2->v && pe->w == pe2->w)||(pe->w == pe2->v && pe->v == pe2->w)) {
							cout << "there is repeated edge " << endl;
							return false;
						}
						pe2 = pe2->next;

					}
					pe = pe->next;
				}

				/* edge number is not correct */
				if(j != EDGENUM) 
					return false;
			}
			return true;
		}
};

/* heap class */
template <typename T> class heap {
	public:
		/* heap data. data is idx and 
		   it is the name of each vertex */
		T *ph;
		int arrlen, last;

		heap() {
			last = 0;
			arrlen = VERTEXNUM;
			/* mem allocation for heap */
			ph = (T *)malloc(sizeof(T) * arrlen);
			/* initialize the name of each vertex */
			for(int i=0 ; i<VERTEXNUM; i++) 
				ph[i] = i+1;
			last = VERTEXNUM;
		}
		~heap(){
			cout << "arrlen : " << arrlen << endl;
			/* free alloced mem */
			free(ph);
		}

		/* display heap */
		void xDisplay() {
			for(int i=0 ; i<last; i++) {
				cout << ph[i] << endl;
			}
		}

		/* move down current vertex until the stop location */
		void xMovedown(int idx, int stop ) {
			int i, lc, rc;
			if(idx == stop) return; 
			/* left child */
			lc = 2*idx+1;
			/* right child */
			rc = lc+1;
			i = idx;
			if(rc > stop) rc = lc;
			/* while left child is bigger or 
			   right child is bigger than current vertex do
			   swap and move down */
			while(ph[i] < ph[lc] || ph[i] < ph[rc]) {
				if(ph[lc] >= ph[rc] && ph[lc] > ph[i]) {
					xSwap(ph[lc], ph[i]);
					i = lc;
					lc = 2*i + 1;
					rc = lc + 1;
					if(lc == stop) {
						if(ph[lc] >= ph[i]) 
							xSwap(ph[lc], ph[i]);
					}

					if(lc >= stop) break;

				} else if(ph[lc] < ph[rc] && ph[rc] > ph[i]) {
					xSwap(ph[rc], ph[i]);
					i = rc;
					lc = 2*i + 1;
					rc = lc + 1;
					if(lc == stop) {
						if(ph[lc] >= ph[i]) 
							xSwap(ph[lc], ph[i]);
					}

					if(lc >= stop) break;
				}
			}
		}

		/* make a heap from an arbitrary array */
		void xHeapify() {
			int i, j, lc, rc;
			int lastpar = (int)(last/2);
			for(i=lastpar ; i>=0 ; i--) {
				xMovedown(i, last-1);
			}
		}

		/* check heap is correct or not */
		void xChkHeap() {
			bool b = true;
			int rc, lc;
			/* for each vertex do
			   check if any child is bigger than parent*/
			for(int i=0 ; i<(int)(last/2) ; i++) {
				lc = 2*i + 1;
				rc = lc + 1;
				if(rc >= last) rc = lc;
				if(ph[rc] > ph[i] || ph[lc] > ph[i]) {
					b = false;
					cout << "not heap in " << i << endl;
				}
			}
			if(b) cout << "correct max heap." << endl;
			else cout << " not correct max heap." << endl;
		}

		/* swap func */
		void xSwap(T &lhs, T &rhs) {
			T temp;
			temp = lhs;
			lhs = rhs;
			rhs = temp;
		}

		/* heap insert. add current vertex to
		   the last location and move up to correct location*/
		void xInsert(T dat) {
			int par, cur;

			/* if heap size grows over the alloced mem, 
			   then realloc the heap mem*/
			if(last>=arrlen) {
				ph = (T *)realloc(ph, arrlen*2*sizeof(T));
				arrlen = arrlen*2;
			}

			cur = last;

			/* add current vertex to the last location */
			ph[cur] = dat;
			par = (int)((cur-1)/2);
			if(par<=0) par=0;

			/* move up the current vertex to the proper location*/
			while(ph[par] < ph[cur]) {
				xSwap(ph[par], ph[cur]);
				cur = par;
				par = (int)((cur-1)/2);
			}
			last++;
		}

		/* get the first item(maximum) in the heap and
		   move the last item to the first location and
		   move it down to correct loaction */
		T xMaximum() {
			int child, cur = 0;
			T data = ph[0];
			xSwap(ph[0], ph[last-1]);
			last -= 1;
			xMovedown(0, last-1);

			return data;
		}

		/* rearrange the current idx.
		   it can move up or move down
		 */
		void rearrange(int idx) {
			int par, cur = idx, lc, rc;

			par = (int)((cur-1)/2);
			if(par <= 0) par = 0;

			/* if current is larger than parent, 
			   then it should move up */
			while(ph[par] < ph[cur]) {
				xSwap(ph[par], ph[cur]);
				cur = par;
				par = (int)((cur-1)/2);
				if(par<0) break;
			}

			/* current need to move down */
			lc = cur*2+1;
			rc = lc+1;
			while(lc < last) {
				if(rc == last) rc = lc;
				if(ph[cur] > ph[lc] && ph[cur] > ph[rc]) {
					break;
				} else if(ph[rc] > ph[lc]) {
					xSwap(ph[cur], ph[rc]);
					cur = rc;
					lc = cur*2+1;
					rc = lc + 1;
				} else {
					xSwap(ph[cur], ph[lc]);
					cur = lc;
					lc = cur*2+1;
					rc = lc + 1;
				}
			}
		}

		/* delete item in heap.
		   move last item to the deleted item's location
		   and rearrange it */
		void xDelete(int idx) {
			xSwap(ph[idx], ph[last-1]);
			last -= 1;
			rearrange(idx);
		}
};

template<typename T> class Dijkstra {
	public: 
		Graph<T> g;
		int s, t;
		Vertex<T> *ShortestPath;

		Dijkstra(int ss, int tt):s(ss),t(tt) {
			g.genGraph(ss, tt);
		}

		bool chkGraph(int s, int t) {
			return g.chkGraph(s, t);
		}

		void setSrcTarget(int s, int t) {
			this.s = s;
			this.t = t;
		}

		void findShortestPath() {
			int i, v, w, max = 0, min, cap, wt;
			Edge<T> *pe;

			for(i=0 ; i<VERTEXNUM ; i++) {
				g.getVertexArr().getVertex(i).setStatus(UNSEEN);
			}

			/* set source INTREE */
			g.getVertexArr().getVertex(s).setStatus(INTREE);
			/* set source neight as FRINGE */
			pe = g.getVertexArr().getVertex(s).getHead();
			while(pe) {
				g.getVertexArr().getVertex(pe->w).setStatus(FRINGE);
				g.getVertexArr().getVertex(pe->w).setDad(s);
				g.getVertexArr().getVertex(pe->w).setCap(pe->getWt());
				pe = pe->next;
			}

			while(g.getVertexArr().getVertex(t).getStatus() != INTREE) {
				max = 0; 
				v = -1;
				/* pick the vertex with largest BW in FRINGE */
				for(i=0 ; i<VERTEXNUM ; i++) {
					if(g.getVertexArr().getVertex(i).getStatus() == FRINGE) {
						if(g.getVertexArr().getVertex(i).getCap() > max) {
							max = g.getVertexArr().getVertex(i).getCap();
							v = i;
						}
					}
				}
				/* add it to INTREE */
				g.getVertexArr().getVertex(v).setStatus(INTREE);
				pe = g.getVertexArr().getVertex(v).getHead();
				while(pe) {
					if(g.getVertexArr().getVertex(pe->w).getStatus() == UNSEEN) {
						g.getVertexArr().getVertex(pe->w).setStatus(FRINGE);
						g.getVertexArr().getVertex(pe->w).setDad(v);
						cap = g.getVertexArr().getVertex(v).getCap();
						wt = pe->getWt();
						min = cap>wt ? wt : cap;
						g.getVertexArr().getVertex(pe->w).setCap(min);
					}
					pe = pe->next;
				}
			}

			i = g.getVertexArr().getVertex(t).getDad();
			cout << "target : " << t << endl;
			while(i != s) {
				cout << "-> Dad : " << i << endl;
				i = g.getVertexArr().getVertex(i).getDad();
			}
			cout << "-> source : " << s << endl;
		}
};
