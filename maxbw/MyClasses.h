#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

/*#define VERTEXNUM	5000	*/
/*#define EDGENUM		6*/

#define RETRYCNT	500
#define WEIGHTRANGE	5000	
#define UNSEEN 		0x1
#define FRINGE		0x10
#define INTREE		0x100
#define WHITE		255
#define GRAY		128
#define BLACK		0
#define INFINITE	1000000

template <typename T> class Vertex ;
template <typename T> class Heap ;
template<typename T> class Graph; 

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

		/* for Kruskal edge path */
		Edge<T> *pMSTNext;

		Edge() {
			next = NULL;
			prev = NULL;
			pMSTNext = NULL;
		} 
		/* edge constructor which sets the begin, end vertices and weight */
		Edge(int vv, int ww, T d):v(vv), w(ww), wt(d) {
			/*cout << "edge const" << endl;*/
			next = NULL;
			prev = NULL;
			pMSTNext = NULL;
		}
		~Edge() {
			/*cout << "edge destroy " << endl;*/
		}

		void setWt(T weight) {
			wt = weight;
		}
		T getWt() {
			return wt;
		}
		bool operator==(const Edge<T>& e) {
			return ((e.v==v)&&(e.w==w)||(e.v==w)&&(e.w==v));
		}

		Edge<T>& operator=(const Edge<T>& e) {
			v = e.v;
			w = e.w;
			wt = e.wt;
			next = e.next;
			prev = e.prev;
			pMSTNext = e.pMSTNext;
			return *this;
		}
		bool operator>=(const Edge<T>& e) {
			return (wt >= e.wt);
		}
		bool operator>(const Edge<T>& e) {
			return (wt > e.wt);
		}
		bool operator<=(const Edge<T>& e) {
			return (wt <= e.wt);
		}
		bool operator<(const Edge<T>& e) {
			return (wt < e.wt);
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
		int EdgeNum;
		int EdgeLimit;
		int rank;
		unsigned char color; /* for DFS search in Kruskal */
		Vertex<T> *parent;
		/* head of linked list of edges belonging to current vertex */
		Edge<T> *Head;

		Vertex() {
			Head = NULL;
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

		/* operator overloading for heap operation */
		bool operator==(const Vertex<T>& v) {
			return (idx == v.idx);
		}
		bool operator>=(const Vertex<T>& v) {
			return (Cap>=v.Cap);
		}

		bool operator<=(const Vertex<T>& v) {
			return (Cap<=v.Cap);
		}

		bool operator<(const Vertex<T>& v) {
			return (Cap<v.Cap);
		}

		bool operator>(const Vertex<T>& v) {
			return (Cap>v.Cap);
		}

		Vertex<T>& operator=(const int idx) {
			this->idx = idx;
			return *this;
		}
		Vertex<T>& operator=(const Vertex<T>& v) {
			this->Cap = v.Cap;
			this->status = v.status;
			this->idx = v.idx;
			this->Dad = v.Dad;
			this->EdgeNum = v.EdgeNum;
			this->rank = v.rank;
			this->color = v.color;
			this->parent = v.parent;

			/* should not do this. fix me */
			/*this->Head = v.Head;*/
			return *this;
		}
		/* vertex init member func. */
		void init(int i, int el) {
			idx = i;
			Head = NULL;
			Cap = 0;
			Dad = -1;
			status = UNSEEN;
			EdgeNum = 0;
			EdgeLimit = el;
			color = WHITE; 
		}

		void makeSet() {
			rank = 0;
			parent = NULL;
		}
		Edge<T>* getHead() {
			return Head;
		}

		int getRank() {
			return rank;
		}
		void setRank(int r) {
			rank = r;
		}

		int getIdx() {
			return idx;
		}

		void setParent(Vertex<T> *pv) {
			parent = pv;
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

		int getEdgeNum() {
			return EdgeNum;
		}
		void setEdgeNum(int en) {
			EdgeNum = en;
		}

		unsigned char getColor() {
			return color;
		}
		void setColor(unsigned char c) {
			color = c;
		}

		/* edit Edge to test the path */
		bool editEdge(int idx, int w, int wt) {
			int i;
			Edge<T> *pe = Head;
			if(idx >= EdgeNum) {
				cout << "incorrect index " << idx << endl;
				return false;
			}
			for(i=0 ; i<idx ; i++) pe = pe->next;

			if(pe) {
				pe->w = w;
				pe->setWt(wt);
				return true;
			} else {
				cout << "error : can't find index : " << idx <<endl;
				return false;
			}
		}

		/* add edge to current vertex */
		int checkEdge(int w) {
			Edge<T> *pe = Head;

			/* current vertex already has enough edges */
			if (EdgeNum == EdgeLimit){
				/*cout << "idx : " << idx << " Edge Num is over : " << EdgeNum << endl;*/
				return 0;
			}
			/* both ends are the same */
			if(idx == w) {
				/*cout << "idx : " << idx << " v==w same edge added " << endl;*/
				return 0;
			}

			while(pe) {
				/* if current edge is already in the edge list, 
				   then donot add and return */
				/*if(pe == e) {*/
				if((pe->w == w))  {
					/*cout <<"idx : " << idx <<  " already there " << pe->v << ", " << w << endl;*/
					return 0;
				}
				pe = pe->next;
			}

			return 1;
		}

		void addEdge(Edge<T> *e) {
			Edge<T> *pe = Head;

			/* add new edge to the first location of the edge list */
			if(pe) {
				e->next = Head;
				Head->prev = e;
				Head = e;
			} else {
				Head = e;
			}
			EdgeNum++;
		}
};

template<typename T> class VertexArr {
	public:
		int vn;
		Vertex<T> *pVertex;
		VertexArr() { }
		~VertexArr() {
			if(pVertex) delete[] pVertex;
			pVertex = NULL;
		}

		void genVertexArr(int vn, int el) {
			int i;
			pVertex = new Vertex<T> [vn];
			for(i=0 ; i<vn; i++) {
				pVertex[i].init(i,el);
			}
		}

		Vertex<T>& getVertex(int idx) {
			return pVertex[idx];
		}

		void connectAll() {
			/*srand(time(NULL));*/
		}

		void makeSet(int i) {
			pVertex[i].makeSet();
		}

		int findSet(Vertex<T>& v) {
			int i, j, size=100;
			int *pStack = (int *)malloc(sizeof(int)*size);
			Vertex<T> *pv = &v;

			i = 0;
			while(pv->parent) {
				pStack[i++] = pv->idx;
				pv = pv->parent;

				if(i>=size) {
					pStack = (int *)realloc(pStack, size*2*sizeof(int));
					size = size*2;
				}
			}

			/* path compression */
			for(j=0 ; j<i ; j++) {
				pVertex[pStack[j]].parent = pv;
			}
			free(pStack);
			return pv->idx;
		}

		void unionSet(int r, int l) {
			if(pVertex[r].getRank() > pVertex[l].getRank()) {
				pVertex[l].setParent(&pVertex[r]);
			} else if(pVertex[r].getRank() < pVertex[l].getRank()) {
				pVertex[r].setParent(&pVertex[l]);
			} else {
				pVertex[l].setParent(&pVertex[r]);
				pVertex[r].setRank(pVertex[r].getRank()+1);
			}
		}
};

template<typename T> class EdgeArr {
	public:
		Heap< Edge<T> > H;

		EdgeArr() { }
		~EdgeArr() { }

		void genEdgeArr(Graph<T>& g) {
			int i, j, alreadyIn=0;
			Edge<T> *pe;
			H.mallocHeap(g.VertexNum);
			for(i=0 ; i<g.VertexNum ; i++) {
				pe = g.Varr.getVertex(i).Head;
				while(pe) {
					for(j=0 ; j<H.getLastIdx(); j++) {
						if(H.ph[j] == *pe)
						break;
					}
					if(j==H.getLastIdx()) {
						H.xInsert(*pe);
					}
					pe = pe->next;
				}
			}
		}

		void genEdgeArr(int len) {
			H.mallocHeap(len);
		}

		void insertEdge(Edge<T>& e) {
			H.xInsert(e);
		}

		Edge<T>& getEdge(int i) {
			return H.ph[i];
		}

		int getSize() {
			return H.getLastIdx();
		}
};


template<typename T> class Graph {
	public : 
		int VertexNum;
		int EdgeNum;
		/*int Source, Target;*/
		VertexArr<T> Varr;
		EdgeArr<T> Earr;
		clock_t start, end;

		Graph() { }
		~Graph() { }
		void initGraph(int vn, int en) {
			VertexNum = vn;
			EdgeNum = en;
		}

		VertexArr<T>& getVertexArr() {
			return Varr;
		}

		void editEdge4Test(int v, int w, int idx, int wt) {
			Edge<T> e;
			if(Varr.getVertex(v).editEdge(idx, w, wt)) {
				if(Varr.getVertex(w).editEdge(idx, v, wt)) {
					e.v = v;
					e.w = w;
					e.setWt(wt);
					Earr.insertEdge(e);
					return;
				} else cout << "edit fail1, vertex " << v << ", " << w << endl;
			} else cout << "edit fail2, vertex " << v << ", " << w << endl;
		}

		void makeTestPath() {
			/* donot use this. only for test purpose */
#if 0
			editEdge4Test(0, 203, 0, WEIGHTRANGE+1);
			editEdge4Test(203, 2043, 0, WEIGHTRANGE+1);
			editEdge4Test(2043, 1837, 0, WEIGHTRANGE+1);
			editEdge4Test(1837, 396, 0, WEIGHTRANGE+1);
			editEdge4Test(396, 4930, 0, WEIGHTRANGE+1);
			editEdge4Test(4930, 1912, 0, WEIGHTRANGE+1);
			editEdge4Test(1912, 882, 0, WEIGHTRANGE+1);
			editEdge4Test(882, 549, 0, WEIGHTRANGE+1);
			editEdge4Test(549, 2943, 0, WEIGHTRANGE+1);
			editEdge4Test(2943, 3367, 0, WEIGHTRANGE+1);
			editEdge4Test(3367, 2939, 0, WEIGHTRANGE+1);
			editEdge4Test(2939, 4102, 0, WEIGHTRANGE+1);
			editEdge4Test(4102, 88, 0, WEIGHTRANGE+1);
			editEdge4Test(88, 2733, 0, WEIGHTRANGE+1);
			editEdge4Test(2733, 1023, 0, WEIGHTRANGE+1);
			editEdge4Test(1023, 923, 0, WEIGHTRANGE+1);
			editEdge4Test(923, 102, 0, WEIGHTRANGE+1);
			editEdge4Test(102, 485, 0, WEIGHTRANGE+1);
			editEdge4Test(485, 775, 0, WEIGHTRANGE+1);
			editEdge4Test(775, 120, 0, WEIGHTRANGE+1);
			editEdge4Test(120, 1, 0, WEIGHTRANGE+1);
			editEdge4Test(1, 4020, 0, WEIGHTRANGE+1);
			editEdge4Test(4020,104, 0, WEIGHTRANGE+1);
			editEdge4Test(104, 4922, 0, WEIGHTRANGE+1);
			editEdge4Test(4922, 738, 0, WEIGHTRANGE+1);
			editEdge4Test(738, 1238, 0, WEIGHTRANGE+1);
			editEdge4Test(1238, 22, 0, WEIGHTRANGE+1);
			editEdge4Test(22, 229, 0, WEIGHTRANGE+1);
			editEdge4Test(229, 3499, 0, WEIGHTRANGE+1);
			editEdge4Test(3499, 12, 0, WEIGHTRANGE+1);
			editEdge4Test(12, 888, 0, WEIGHTRANGE+1);
			editEdge4Test(888, 472, 0, WEIGHTRANGE+1);
			editEdge4Test(472, 2398, 0, WEIGHTRANGE+1);
			editEdge4Test(2398, 402, 0, WEIGHTRANGE+1);
			editEdge4Test(402, 1112, 0, WEIGHTRANGE+1);
			editEdge4Test(1112, 3981, 0, WEIGHTRANGE+1);
			editEdge4Test(3981, 2391, 0, WEIGHTRANGE+1);
			editEdge4Test(2391, 4392, 0, WEIGHTRANGE+1);
			editEdge4Test(4392, 4422, 0, WEIGHTRANGE+1);
			editEdge4Test(4422, 4, 0, WEIGHTRANGE+1);
			editEdge4Test(4, 2299, 0, WEIGHTRANGE+1);
			editEdge4Test(2299, 32, 0, WEIGHTRANGE+1);
			editEdge4Test(32, 390, 0, WEIGHTRANGE+1);
			editEdge4Test(390, 1212, 0, WEIGHTRANGE+1);
			editEdge4Test(1212, 4022, 0, WEIGHTRANGE+1);
			editEdge4Test(4022, 1024, 0, WEIGHTRANGE+1);
#endif
		}

		void genGraph() {
			int i, j, k, wt;
			int retry=0;
			float vtxst, wtst;
			Edge<T> *pe, *pe2;

			cout << "graph generation start " << endl;
			start = clock();
			Varr.genVertexArr(VertexNum, EdgeNum);
			Earr.genEdgeArr(VertexNum);
			srand(time(NULL));
			/* random number(vertex idx) used as 
			   the neighbor of current vertex */
			vtxst = VertexNum*1.0f;
			/* random number(weight of edge) used as 
			   the weight of edge */
			wtst = WEIGHTRANGE*1.0f;

			/* for each VERTEXNUM(5000) do
			   for each EDGENUM do
			   generate edges*/
			for(i=0 ; i<VertexNum; i++) {
				retry = 0;
				for(j=Varr.getVertex(i).getEdgeNum() ; j<EdgeNum; ) {
					/* if retry is over RETRYCNT, we think that 
					   all other vertices have EDGENUM edges excpet current vertex */
					if(retry >= RETRYCNT) break;
					wt = 0;
					/* generate the weight of edge.
					   edge weight is not 0 */
					while(wt == 0) wt = (int)(((float)rand()/(float)RAND_MAX)*wtst); 
					/* generate the idx of neighbor vertex */
					/* if i is target then connect it to the source for making
					   path from source to target */
					k = (int)(((float)rand()/(float)RAND_MAX)*vtxst);
					/*cout << "k : " << k << " wt : " << wt << endl;*/
					pe = new Edge<int>(i, k, wt);
					pe2 = new Edge<int>(k, i, wt);
					/* if edge is successfully added
					   then increase the edge num */
					if(Varr.getVertex(i).checkEdge(k) 
						&& Varr.getVertex(k).checkEdge(i)) {
						/* add same edge to both vertices */
						Varr.getVertex(i).addEdge(pe);
						Varr.getVertex(k).addEdge(pe2);
						Earr.insertEdge(*pe);
						j++;
					} else {
						/* if edge is already there, 
						   then remove malloced mem */
						retry++;
						delete pe;
						delete pe2;
					}
				}
			}
			end = clock();
			cout << "graph generation end" << endl;
			cout << "graph generation takes " << ((double)(end-start)/CLOCKS_PER_SEC) << " sec" << endl;
		}

		bool chkGraph() {
			int i, j;
			Edge<T> *pe;
			/* check if the generated graph is correct or not 
			   for each vertex do
			   check the edge is correct.
			   correct means that there is not same edge. */
			for(i=0 ; i<VertexNum; i++) {
				Edge<int> *pe2;	
				pe = Varr.getVertex(i).Head;
				for(j=0 ; j<Varr.getVertex(i).getEdgeNum(); j++) {
					pe2 = pe->next;
					while(pe2) {
						if((pe->v == pe2->v && pe->w == pe2->w)||(pe->w == pe2->v && pe->v == pe2->w)) {
							cout << "check graph : there is repeated edge " << endl;
							if(pe->getWt() > pe2->getWt()) pe2->setWt(pe->getWt());
							else pe->setWt(pe2->getWt());
							return false;
						}
						pe2 = pe2->next;

					}
					pe = pe->next;
				}
			}
			cout << "check graph : graph is good" << endl;
			return true;
		}

		/* connect all vertices with small weight */
		bool connectAllVertices() {
			int i;
			for(i=0 ; i<VertexNum-2 ; i++) {
				if(!Varr.getVertex(i).editEdge(0, i+1, (int)(WEIGHTRANGE/100)) ||
						!Varr.getVertex(i+1).editEdge(0, i, (int)(WEIGHTRANGE/100))) {
				/*if(!Varr.getVertex(i).editEdge(0, i+1, WEIGHTRANGE+1)) {*/
					cout << "connect all vertices fail !!" << endl;
					return false;
				}
			}
			for(i=0 ; i<VertexNum-2 ; i++) {
				if(Varr.getVertex(i).getHead()->w != i+1)
					return false;
			}
			cout << "all vertices are connected. " << endl;
			return true;
		}
};

/* heap class */
template <typename T> class Heap {
	public:
		/* heap data. data is idx and 
		   it is the name of each vertex */
		T *ph;
		int size, last, localalloc;

		Heap() {};

		Heap(int len) {
			last = 0;
			size = len;
			ph = (T *)malloc(sizeof(T) * size);
			localalloc = 1;
			/*cout << "Heap default constructor is called " << endl;*/
		}

		Heap(T *arr, int len) {
			last = len;
			size = len;
			/* mem allocation for heap */
			ph = arr;
			localalloc = 0;
		}

		~Heap(){
			/*cout << "Heap size : " << size << endl;*/
			/*cout << "Heap last : " << last << endl;*/
			/* free alloced mem */
			if(localalloc) {
				free(ph);
				ph = NULL;
			}
		}

		void mallocHeap(int len) {
			last = 0;
			size = len;
			ph = (T *)malloc(sizeof(T) * size);
			localalloc = 1;
			/*cout << "Heap malloc is called " << endl;*/

		}

		int getSize() {
			return size;
		}
		int getLastIdx() {
			return last;
		}
#if 0 
		Heap(VertexArr<int> &arr) {
			last = 0;
			size = VERTEXNUM;
			/* mem allocation for heap */
			ph = arr.pVertex;
			/* initialize the name of each vertex */
			last = 0;
			localalloc = 0;
			cout << "heap init with vertex array" << endl;
		}
#endif

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
					xSwap(lc, i);
					i = lc;
					lc = 2*i + 1;
					rc = lc + 1;
					if(lc == stop) {
						if(ph[lc] >= ph[i]) 
							xSwap(lc, i);
					}

					if(lc >= stop) break;

				} else if(ph[lc] < ph[rc] && ph[rc] > ph[i]) {
					xSwap(rc, i);
					i = rc;
					lc = 2*i + 1;
					rc = lc + 1;
					if(lc == stop) {
						if(ph[lc] >= ph[i]) 
							xSwap(lc, i);
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
		bool xChkHeap() {
			bool b = true;
			int i, rc, lc;
			/* for each vertex do
			   check if any child is bigger than parent*/
			for(i=0 ; i<(int)(last/2) ; i++) {
				lc = 2*i + 1;
				rc = lc + 1;
				if(rc >= last) rc = lc;
				if(ph[rc] > ph[i] || ph[lc] > ph[i]) {
					b = false;
					cout << "not heap in " << i << endl;
				}
			}
			if(b) {
				cout << "correct max heap." << endl;
				return true;
			} else {
				cout << " not correct max heap." << endl;
				return false;
			}
		}

		/* swap func */

		void xSwap(int i, int j) {
			T temp;
			temp = ph[i];
			ph[i] = ph[j];
			ph[j] = temp;
		}

		/* heap insert. add current vertex to
		   the last location and move up to correct location*/
		void xInsert(T & dat) {
			int par, cur;

			/* if heap size grows over the alloced mem, 
			   then realloc the heap mem*/
			if(last>=size) {
				ph = (T *)realloc(ph, size*2*sizeof(T));
				size = size*2;
			}

			if(!ph) {
				cout << "realloc fail " << endl;
				return;
			}

			cur = last;

			/* add current vertex to the last location */
			ph[cur] = dat;
			par = (int)((cur-1)/2);
			if(par<=0) par=0;

			/* move up the current vertex to the proper location*/
			while(ph[par] < ph[cur]) {
				xSwap(par, cur);
				cur = par;
				par = (int)((cur-1)/2);
			}
			last++;
		}

		/* get the first item(maximum) in the heap and
		   move the last item to the first location and
		   move it down to correct loaction */
		T& xMaximum() {
			int child, cur = 0;
			xSwap(0, last-1);
			last -= 1;
			xMovedown(0, last-1);

			return ph[last];
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
				xSwap(par, cur);
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
					xSwap(cur, rc);
					cur = rc;
					lc = cur*2+1;
					rc = lc + 1;
				} else {
					xSwap(cur, lc);
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
			xSwap(idx, last-1);
			last -= 1;
			rearrange(idx);
		}
};


template<typename T> class Dijkstra {
	public: 
		bool isAllConnected;
		Vertex<T> refv;
		Graph<T> g;
		clock_t start, end;
		int Source, Target;

		Dijkstra(Graph<T>& gref) {
			g = gref;
		}
		Dijkstra(int vn, int en) {
			g.initGraph(vn, en);
			g.genGraph();
			isAllConnected = g.connectAllVertices();
		}

		void makeTestPath() {
			g.makeTestPath();
		}

		void findMaxBWPathHeap(int s, int t) {
			int i, v, w, max = 0, min, cap, wt;
			Source = s;
			Target = t;
			Edge<T> *pe;
			Heap< Vertex<T> > H(g.VertexNum);

			if(!isAllConnected) {
				cout << "Not all vertices are connected" << endl;
				return;
			}

			start = clock();

			for(i=0 ; i<g.VertexNum ; i++) {
				g.getVertexArr().getVertex(i).setStatus(UNSEEN);
				g.getVertexArr().getVertex(i).setCap(0);
				g.getVertexArr().getVertex(i).setDad(-1);
			}

			/* set source INTREE */
			g.getVertexArr().getVertex(Source).setStatus(INTREE);
			/* set source neighbor as FRINGE */
			pe = g.getVertexArr().getVertex(Source).getHead();
			while(pe) {
				g.getVertexArr().getVertex(pe->w).setStatus(FRINGE);
				g.getVertexArr().getVertex(pe->w).setDad(Source);
				g.getVertexArr().getVertex(pe->w).setCap(pe->getWt());
				H.xInsert(g.getVertexArr().getVertex(pe->w));
				pe = pe->next;
			}

			while(g.getVertexArr().getVertex(Target).getStatus() != INTREE) {
				refv = H.xMaximum();
				v = refv.getIdx();
				/* temp for debugging purpose */
				max = g.getVertexArr().getVertex(v).getCap();
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
						H.xInsert(g.getVertexArr().getVertex(pe->w));
						/*if(!H.xChkHeap()) return;*/

					} else if(g.getVertexArr().getVertex(pe->w).getStatus() == FRINGE) {
						cap = g.getVertexArr().getVertex(v).getCap();
						wt = pe->getWt();
						min = cap>wt ? wt : cap;
						if(g.getVertexArr().getVertex(pe->w).getCap() < min) {
							g.getVertexArr().getVertex(pe->w).setDad(v);
							g.getVertexArr().getVertex(pe->w).setCap(min);
							/* find the heap location of updated vertex*/
							for(i=0 ; i<H.getLastIdx() ; i++) {
								if(H.ph[i] == g.getVertexArr().getVertex(pe->w))
									break;
							}
							H.ph[i] = g.getVertexArr().getVertex(pe->w);
							H.rearrange(i);
							/*if(!H.xChkHeap()) return;*/
						}
					}
					pe = pe->next;
				}
			}

			end = clock();

			/*cout << "dijkstra w/ heap takes " << ((double)(end-start)/CLOCKS_PER_SEC) << endl;*/
			cout << "dijkstra with heap takes " << ((double)(end-start)/CLOCKS_PER_SEC) << " sec" << endl;

			i = g.getVertexArr().getVertex(Target).getDad();
			cout << "target : " << Target << " cap : " << g.getVertexArr().getVertex(Target).getCap() << endl;
			while(i != Source) {
				cout << "-> Dad : " << i << endl;
				i = g.getVertexArr().getVertex(i).getDad();
			}
			cout << "-> source : " << Source << endl;

			if(checkPath()) cout << "check Path : correct path !!" << endl;
			else cout << "check Path : not correct !!" << endl;
		}

		bool checkPath() {
			int v, w ;
			Edge<T> *pe;
			v = g.getVertexArr().getVertex(Target).getDad();
			w = Target;
			while(v != Source) {
				pe = g.getVertexArr().getVertex(v).Head;
				while(pe != NULL) {
					if((pe->v == v && pe->w == w) || (pe->v == w && pe->w==v))
						break;
					pe = pe->next;
				}
				if(pe == NULL) return false;
				w = v;
				v = g.getVertexArr().getVertex(v).getDad();
			}

			pe = g.getVertexArr().getVertex(v).Head;
			while(pe != NULL) {
				if((pe->v == v && pe->w == w) || (pe->v == w && pe->w==v))
					break;
				pe = pe->next;
			}
			if(pe == NULL) return false;

			return true;
		}

		void findMaxBWPath(int s, int t) {
			int i, v, w, max = 0, min, cap, wt;
			Source = s;
			Target = t;
			Edge<T> *pe;

			if(!isAllConnected) {
				cout << "Not all vertices are connected" << endl;
				return;
			}

			start = clock();

			for(i=0 ; i<g.VertexNum ; i++) {
				g.getVertexArr().getVertex(i).setStatus(UNSEEN);
				g.getVertexArr().getVertex(i).setCap(0);
				g.getVertexArr().getVertex(i).setDad(-1);
			}

			/* set source INTREE */
			g.getVertexArr().getVertex(Source).setStatus(INTREE);
			/* set source neight as FRINGE */
			pe = g.getVertexArr().getVertex(Source).getHead();
			while(pe) {
				g.getVertexArr().getVertex(pe->w).setStatus(FRINGE);
				g.getVertexArr().getVertex(pe->w).setDad(Source);
				g.getVertexArr().getVertex(pe->w).setCap(pe->getWt());
				pe = pe->next;
			}

			while(g.getVertexArr().getVertex(Target).getStatus() != INTREE) {
				max = 0; 
				v = -1;
				/* pick the vertex with largest BW in FRINGE */
				for(i=0 ; i<g.VertexNum ; i++) {
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
					} else if(g.getVertexArr().getVertex(pe->w).getStatus() == FRINGE) {
						cap = g.getVertexArr().getVertex(v).getCap();
						wt = pe->getWt();
						min = cap>wt ? wt : cap;
						if(g.getVertexArr().getVertex(pe->w).getCap() < min) {
							g.getVertexArr().getVertex(pe->w).setDad(v);
							g.getVertexArr().getVertex(pe->w).setCap(min);
						}
					}
					pe = pe->next;
				}
			}

			end = clock();
			cout << "dijkstra w/o heap takes " << ((double)(end-start)/CLOCKS_PER_SEC) << " sec" << endl;

			i = g.getVertexArr().getVertex(Target).getDad();
			cout << "target : " << Target << " cap : " << g.getVertexArr().getVertex(Target).getCap() << endl;
			while(i != Source) {
				cout << "-> Dad : " << i << endl;
				i = g.getVertexArr().getVertex(i).getDad();
			}
			cout << "-> source : " << Source << endl;
			if(checkPath()) cout << "check Path : correct path !!" << endl;
			else cout << "check Path : not correct !!" << endl;
		}
};

template<typename T> class Kruskal {
	public:
		bool isHeapSortDone;
		bool isAllConnected;
		int Source, Target;
		Graph<T> g;
		/*EdgeArr<T> Earr;*/
		Edge<T> *pMSTHead;
		Edge<T> *pMaxEdgeArr;
		clock_t start, end;

		Kruskal(Graph<T>& gref) {
			g = gref;
		}

		Kruskal(int vn, int en) {
			pMSTHead = NULL;
			g.initGraph(vn, en);
			g.genGraph();
			isAllConnected = g.connectAllVertices();
			pMaxEdgeArr = (Edge<T> *)malloc(sizeof(Edge<T>)*g.Earr.getSize());
			isHeapSortDone = false;
		}
		~Kruskal() {
			free(pMaxEdgeArr);
		}

		void makeTestPath() {
			g.makeTestPath();
		}

		void findMaxBWPath(int s, int t) {
			int i, r, l;
			int v, w;
			int s1, s2;

			if(!isAllConnected) {
				cout << "Not all vertices are connected" << endl;
				return;
			}
			Source = s;
			Target = t;
			Edge<T> e;
			Edge<T> *pe;
			/* should not use this. this takes O(n*m*m) */
			/* genEdgeArr generate max heap */
			/*
			start = clock();
			Earr.genEdgeArr(g);
			end = clock();

			cout << "kruskal making edge list takes " << ((double)(end-start)/CLOCKS_PER_SEC) << " sec" << endl;
			 */

			if(!isHeapSortDone) {
				isHeapSortDone = true;
				start = clock();
				/* heap sort*/
				for(i=g.Earr.getSize()-1 ; i>0 ; i--) {
					g.Earr.H.xSwap(0, i);
					g.Earr.H.xMovedown(0, i-1);
				}

				/* reorder the heap sort with non-increasing order*/
				for(i=0 ; i<g.Earr.getSize() ; i++) {
					pMaxEdgeArr[i] = g.Earr.H.ph[g.Earr.getSize()-1-i];
				}
				end = clock();

				cout << "kruskal heap sorting edge list takes " << ((double)(end-start)/CLOCKS_PER_SEC) << " sec" << endl;
				/* check heap sort */
				for(i=0 ; i<g.Earr.getSize()-1; i++) {
					if(pMaxEdgeArr[i] < pMaxEdgeArr[i+1]) {
						cout << "Max heap sort fail !!" << endl;
						break;
					}
				}
			}


			for(i=0 ; i<g.VertexNum ; i++) {
				g.Varr.getVertex(i).makeSet();
				g.Varr.getVertex(i).setColor(WHITE);
				g.Varr.getVertex(i).setDad(-1);
				g.Varr.getVertex(i).setCap(0);
			}
			for(i=0 ; i<g.Earr.getSize() ; i++) {
				g.Earr.getEdge(i).pMSTNext = NULL;
			}
			pMSTHead = NULL;

			start = clock();
			/* build MST */
			for(i=0 ; i<g.Earr.getSize() ; i++) {
				/*e = g.Earr.getEdge(i);*/
				pe = &pMaxEdgeArr[i];
				v = pe->v;
				w = pe->w;
				s1 = g.Varr.findSet(g.Varr.getVertex(v));
				s2 = g.Varr.findSet(g.Varr.getVertex(w));
				if(s1 != s2) {
					pe->pMSTNext = pMSTHead;
					pMSTHead = pe;
					g.Varr.unionSet(s1, s2);
					/*cout << "v : " << v << ", w: " << w << endl;*/
				}
				if(g.Varr.findSet(g.Varr.getVertex(Source)) 
					== g.Varr.findSet(g.Varr.getVertex(Target))) {
					/*cout << "found !! " << endl;*/
					break;
				}
			}
			end = clock();
			cout << "kruskal building MST takes " << ((double)(end-start)/CLOCKS_PER_SEC) << " sec" << endl;

			start = clock();
			DFS(Source);
			end = clock();
			cout << "kruskal finding path in MST takes " << ((double)(end-start)/CLOCKS_PER_SEC) << " sec" << endl;

			i = g.getVertexArr().getVertex(Target).getDad();
			cout << "target : " << Target << " cap : " << g.getVertexArr().getVertex(Target).getCap() << endl;
			while(i != Source) {
				cout << "-> Dad : " << i << endl;
				i = g.getVertexArr().getVertex(i).getDad();
			}
			cout << "-> source : " << Source << endl;

			/*
			pe = pMSTHead;
			while(pe) {
				cout << "v : " << pe->v << ", w: " << pe->w << endl;
				pe = pe->pMSTNext;
			}
			*/
		}

		void DFS(int v) {
			int cap, wt, min;
			Edge<T> *pe;

			if(v == Source) g.getVertexArr().getVertex(Source).setCap(INFINITE);
			if(v == Target) return;

			pe = pMSTHead;
			g.getVertexArr().getVertex(v).setColor(GRAY);

			while(pe) { 
				/* if edge has a current vertex v */
				if(pe->v == v ) {
					if(g.Varr.getVertex(pe->w).getColor() == WHITE) {
						cap = g.getVertexArr().getVertex(v).getCap();
						wt = pe->getWt();
						min = cap>wt ? wt : cap;
						g.getVertexArr().getVertex(pe->w).setCap(min);
						DFS(pe->w);
						g.Varr.getVertex(pe->w).setDad(v);
						if(pe->w == Target) break;
					}
				} else if(pe->w == v) {
					if(g.Varr.getVertex(pe->v).getColor() == WHITE) {
						cap = g.getVertexArr().getVertex(v).getCap();
						wt = pe->getWt();
						min = cap>wt ? wt : cap;
						g.getVertexArr().getVertex(pe->v).setCap(min);
						DFS(pe->v);
						g.Varr.getVertex(pe->v).setDad(v);
						if(pe->v == Target) break;
					}
				}
				pe = pe->pMSTNext;
			}
			g.Varr.getVertex(v).setColor(BLACK);
		}
};

