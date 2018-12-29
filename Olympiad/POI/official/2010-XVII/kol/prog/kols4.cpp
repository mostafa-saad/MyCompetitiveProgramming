/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kolej (KOL)                                               *
 *   Plik:     kols4.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie powolne; dwukolorowanie grafu                 *
 *   Zlozonosc czasowa: O(m log n)                                       *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;
    
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)

inline int RI(){int x; scanf("%d",&x); return x;}

struct list_head {
	struct list_head *next, *prev;
};

inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

inline void __list_add(struct list_head *nw,
		       struct list_head *prev,
    		       struct list_head *next)
{
	next->prev = nw;
	nw->next = next;
	nw->prev = prev;
	prev->next = nw;
}

inline void list_add(struct list_head *nw, struct list_head *head)
{
	__list_add(nw, head, head->next);
}
                
#define list_entry(ptr, type, member) ({\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
                (type *)( (char *)__mptr - (char *)(&((type *)0)->member) );})

#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); \
        	pos = pos->next)
#define list_rev_for_each(pos, head) \
	for (pos = (head)->prev; pos != (head); \
        	pos = pos->prev)

const int MAX  = 	100100;
const int zz   =	132000;
const int minf =	-1;

int n;

int A[MAX];
int B[MAX];
int R[MAX];
int color[MAX];

struct Node{
    struct list_head forward;
    struct list_head backward;
};

struct Listener{
    int h;
    struct list_head list;
};

struct Node tree[2*zz];

inline void addListener(int value, struct list_head* head){
    struct Listener* l = (struct Listener*) malloc(sizeof(struct Listener));
    INIT_LIST_HEAD(&l->list);
    list_add(&l->list, head);
    l->h=value;
}

inline void addToBucket(int k){
    int a=A[k];
    int b=B[k];
    int l=k+zz;
    int left=k+zz-1;
    int right=b+zz+1;
    
    while (l>0){
	addListener(a,&tree[l].forward);
	l>>=1;
    }
    
    while ((left>>1) != (right>>1)){
	if (!(left&1))
	    addListener(a,&tree[left^1].backward);
	if (right&1)
	    addListener(a,&tree[right^1].backward);
	left>>=1;
	right>>=1;
    }
}

inline void buildTree(){
    REP(t,MAX) color[t]=-1;
    REP(t,2*zz){
	INIT_LIST_HEAD(&tree[t].forward);
	INIT_LIST_HEAD(&tree[t].backward);
    }
    REP(i,n)
	addToBucket(R[i]);
}

inline void destroyTree(){
    struct Listener* lst;
    REP(t,2*zz){
	while (tree[t].forward.next != &tree[t].forward){
	    lst=list_entry(tree[t].forward.next,struct Listener,list);
	    tree[t].forward.next=tree[t].forward.next->next;
	    free(lst);
	}
	while (tree[t].backward.next != &tree[t].backward){
	    lst=list_entry(tree[t].backward.next,struct Listener,list);
	    tree[t].backward.next=tree[t].backward.next->next;
	    free(lst);
	}
    }
}

int queue[3*MAX];
int qbegin,qend;

inline void doEdge(int c, int h){
    int nxt=R[h];
    if (color[nxt]<0){
        queue[qend++]=nxt;
        color[nxt]=c^1;
    } else if (color[nxt]!=(c^1)){
        printf("NIE\n");
        destroyTree();
        exit(0);
    }
}

inline void doVertex(int k){
    int c=color[k];
    int a=A[k];
    int b=B[k];
    int l=k+zz;
    int left=k+zz-1;
    int right=b+zz+1;
    struct list_head* it;
    struct Listener* ls;
    
    while (l>0){
	list_rev_for_each(it,&tree[l].backward){
	    ls=list_entry(it,struct Listener,list);
	    if (ls->h < a)
		doEdge(c,ls->h);
	}
	l>>=1;
    }
    
    while ((left>>1) != (right>>1)){
	if (!(left&1))
	    list_for_each(it,&tree[left^1].forward){
	        ls=list_entry(it,struct Listener,list);
		if (ls->h > a)
		    doEdge(c,ls->h);
		else break;
	    }
	if (right&1)
	    list_for_each(it,&tree[right^1].forward){
	        ls=list_entry(it,struct Listener,list);
		if (ls->h > a)
		    doEdge(c,ls->h);
		else break;
	    }
	left>>=1;
	right>>=1;
    }
}

inline void bfs(int p){
    qbegin=0;
    qend=1;
    queue[0]=p;
    color[p]=0;
    while (qend>qbegin)
	doVertex(queue[qbegin++]);
}

inline void buildA(){
    n=RI();
    REP(i,n) A[i]=RI()-1;
}

inline void buildR(){
    REP(i,n) R[A[i]]=i;
}

inline void buildB(){
    int m=minf;
    REP(i,n)
	B[R[i]]=(m=max(m,R[i]));
}


inline void buildSolution(){
    REP(t,n) if (color[t]<0) bfs(t);
}

inline void buildAnswer(){
    printf("TAK\n");
    REP(i,n) printf("%s%d",(i)?" ":"",color[i]+1);
    printf("\n");
}

int main(){
    buildA();
    buildR();
    buildB();
    buildTree();
    buildSolution();
    buildAnswer();
    destroyTree();
    return 0;
}
