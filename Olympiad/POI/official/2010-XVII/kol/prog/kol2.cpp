/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Kolej (KOL)                                   *
 *   Plik:                 kol2.cpp                                      *
 *   Autor:                Bartosz Walczak                               *
 *	 Implementacja         Michal Pilipczuk                              *   
 *   Opis:                 Autorskie rozwiazanie wzorcowe.               *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *                                                                       *
 *************************************************************************/


/* ==================== include'y and makra ================ */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;
    
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define PB push_back

inline int RI(){int x; scanf("%d",&x); return x;}

/* ========================== zmienne globalne ======================== */

const int MAX  = 	100100;		/* wielkosc tablic do trzymania danych */
const int minf =	-1;

int n;					/* n z zadania */

int A[MAX];				/* a_n z zadania */
int M[MAX];				/* M z opracowania */
int R[MAX];				/* odwrocona permutacja a_n */
int colors[MAX];			/* do skladowania wyniku */

/* struktura wierzcholka drzewa lewicowego */	
struct Tree{
    int value;				/* maksimum w poddrzewie */
    int rank;				/* ranga wierzcholka */
    struct Tree* left;			/* lewy syn */
    struct Tree* right;			/* prawy syn */
};											
/* 12 bajtow */

stack<struct Tree*> heap;		/* stos spojnych skladowych */
vector<vector<int> > edges;		/* krawedzie lasu rozpinajacego */

/* ======================== drzewa lewicowe ============================= */

struct Tree* singleton(int v){
    struct Tree* ret=(struct Tree*)malloc(sizeof(struct Tree));
    ret->value=v;
    ret->rank=1;
    ret->left=NULL;
    ret->right=NULL;
    return ret;
}

inline int getMin(struct Tree* t){
    return t->value;
}

inline int getRank(struct Tree* t){
    if (t==NULL) return 0;
    return t->rank;
}

struct Tree* join(struct Tree* l,struct Tree* r){
    int nxt;
    struct Tree* hd;
    struct Tree* sc;
    if (r==NULL && l==NULL) return NULL;
    if (r==NULL) nxt=0; else
    if (l==NULL) nxt=1; else 
    nxt=((l->value<r->value)?0:1);
    hd=l; sc=r;
    if (nxt==1) swap(hd,sc);
    hd->right=join(hd->right,sc);
    if (getRank(hd->left)<getRank(hd->right)) swap(hd->left,hd->right);
    hd->rank=1+getRank(hd->right);
    return hd;
}

struct Tree* delMin(struct Tree* t){
    struct Tree* ret = join(t->left,t->right);
    free(t);
    return ret;
}

inline void delTree(struct Tree* t){
    if (t==NULL) return;
    delTree(t->left);
    delTree(t->right);
    free(t);
}

/* ====================== budowanie rozwiazania ========================= */

/* czyta wejscie */
inline void buildA(){
    n=RI();
    REP(i,n) A[i]=RI()-1;
}

/* buduje R */
inline void buildR(){
    REP(i,n) R[A[i]]=i;
}

/* buduje M */
inline void buildM(){
    int m=n;
    FORD(i,n-1,0){
	M[i]=m;
	if (m>A[i]) m=A[i];
    }
}

/* dfs kolorujacy */
void dfs(int t,int c){
    colors[t]=c;
    REP(s,edges[t].size()) if (colors[edges[t][s]]<0) dfs(edges[t][s],c^1);
}

/* buduje przykladowe rozwiazanie */
inline void buildSolution(){
    struct Tree* nxt;
    struct Tree* tmp;
    int d,e,f;
    edges=vector<vector<int> >(n,vector<int>());
    REP(k,n){
	d=A[k];
	e=M[k];
	nxt=singleton(d);
	while (!heap.empty()){
	    tmp = heap.top();
	    f=getMin(tmp);
	    if (f<d){
		edges[k].PB(R[f]);
		edges[R[f]].PB(k);
		nxt=join(nxt,tmp);
		heap.pop();
	    } else break;
	}
	heap.push(nxt);
	while (!heap.empty()){
	    tmp = heap.top();
	    heap.pop();
	    while ((tmp!=NULL) && getMin(tmp)<e) tmp=delMin(tmp);
	    if (tmp!=NULL) { heap.push(tmp); break; }
	}
    }
    REP(t,n) colors[t]=-1;
    REP(t,n) if (colors[t]<0) dfs(t,0);
}

/* ========================== sprawdzanie rozwiazania ==================== */

int c=0;		/* jaki jest kolejny element do zdjecia */
stack<int> st[2];	/* stosy do zdejmowania */

/* zdejmuje ze stosow tyle, ile mozna */
void flush(){
    int flag;
    for(;;){
        flag = 1;
        REP(t,2) if (st[t].top()==c){
	    c++;
	    st[t].pop();
	    flag = 0;
	}
	if (flag) break;
    }
}

/* sprawdza, czy zbudowane rozwiazanie jest poprawne */
bool checkSolution(){
    REP(i,2) st[i].push(n+2);
    REP(i,n){
	st[colors[i]].push(A[i]);
	flush();
    }
    return (c>=n);
}

/* buduje i wypisuje odpowiedz na wyjscie */
inline void buildAnswer(){
    if (checkSolution()){
	printf("TAK\n");
	REP(i,n) printf("%s%d",(i)?" ":"",colors[i]+1);
	printf("\n");
    } else 
	printf("NIE\n");
}

int main(){
    buildA();
    buildR();
    buildM();
    buildSolution();
    buildAnswer();
    return 0;
}
