/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Kolej (KOL)                                   *
 *   Plik:                 kol.cpp                                       *
 *   Autor:                Michal Pilipczuk                              *
 *   Opis:                 Rozwiazanie wzorcowe.                         *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n log n)                                    *
 *                                                                       *
 *************************************************************************/

/* ==================== include'y and makra ================ */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;
    
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)

inline int RI(){int x; scanf("%d",&x); return x;}

/* ========================== list.h ======================= */
/*   kopia interesujacych elementow naglowka kernela list.h  */
/*   dla zaineteresowanych: znajduje sie w /include/linux/   */
/* ========================================================= */

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

/* dodaje element wskazywany przez *nw za element wskazywany przez *head */
inline void list_add(struct list_head *nw, struct list_head *head)
{
	__list_add(nw, head, head->next);
}

inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

/* usuwa element wskazywany przez *entry */
inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}

/* sprawdza, czy lista jest pusta */
inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}
                
/* wyjmuje strukture w ktorej siedzi skladnik listy */
#define list_entry(ptr, type, member) ({\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
                (type *)( (char *)__mptr - (char *)(&((type *)0)->member) );})

/* iteruje po elementach listy */
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); \
        	pos = pos->next)

/* ========================== zmienne globalne ======================== */

const int MAX  = 	100100;		/* wielkosc tablic do trzymania danych */
const int zz   =	132000;		/* offset drzewa licznikowego */
const int minf =	-1;

int n;					/* n z zadania */

int A[MAX];				/* a_n z zadania, <0.5MB */
int B[MAX];				/* b_n z opracowania, <0.5MB */
int R[MAX];				/* odwrocona permutacja a_n, <0.5MB */
int colors[MAX];			/* do skladowania wyniku, <0.5MB */

/* struktura wierzcholka drzewa licznikowego */	
struct Node{
    int mx;				/* maksimum w poddrzewie */
    struct list_head listeners;		/* lista Listenerow w poddrzewie */
};											
/* 12 bajtow */

/* struktura sluchajaca trzymana na listach w wezlach drzewa licznikowego */
struct Listener{
    int h;				/* wysokosc elementu sluchajacego */
    struct list_head node_list;		/* nanizanie na liste w drzewie licznikowym */
    struct list_head listen_list;	/* nanizanie na liste elementu sluchajacego */
};											
/* 20 bajtow */

struct Node tree[2*zz];			/* drzewo, <2MB */
struct list_head listen_nodes[MAX];	/* listy elementow sluchajacych, <2MB */

/* Dynamiczna pamiec: 
< 20 (wysokosc drzewa) * 2 (dwie strony listenerow) * 100000 (n) * 20 (wielkosc listenera) =
= 80*10^6 = 80MB */

/* W sumie pamieci: <80MB+4MB+2MB=86MB */

/* ====================== budowanie rozwiazania ========================= */

/* dodaje Listenera dla elementu na pozycji k do wezla o numerze node, o wysokosci value */
inline void addListener(int k, int node, int value){
    struct Listener* l = (struct Listener*) malloc(sizeof(struct Listener));
    INIT_LIST_HEAD(&l->node_list);
    INIT_LIST_HEAD(&l->listen_list);
    list_add(&l->node_list,&tree[node].listeners);
    list_add(&l->listen_list,&listen_nodes[k]);
    l->h=value;
}

/* dodaje wartosc A[k] do kubelka o numerze k */
/* aktualizuje maksimum oraz dodaje Listenerow */
inline void addToBucket(int k){
    int a=A[k];
    int b=B[k];
    int l=k+zz;
    int left=k+zz-1;
    int right=b+zz+1;
    
    /* aktualizacja maksimum */
    tree[l].mx=a;
    l>>=1;
    while (l>0){
	tree[l].mx = max(tree[l<<1].mx,tree[(l<<1)+1].mx);
	l>>=1;
    }
    
    /* dodawanie listenerow */
    INIT_LIST_HEAD(&listen_nodes[k]);
    while ((left>>1) != (right>>1)){
	if (!(left&1))
	    addListener(k,left^1,a);
	if (right&1)
	    addListener(k,right^1,a);
	left>>=1;
	right>>=1;
    }
}

/* usuwa wartosc A[k] z kubelka o numerze k */
/* aktualizuje maksimum i usuwa listenerow */
inline void deleteFromBucket(int k){
    int l=k+zz;
    struct list_head* it;
    struct Listener* listener;
    
    /* aktualizacja maksimum */
    tree[l].mx=minf;
    l>>=1;
    while (l>0){
	tree[l].mx = max(tree[l<<1].mx,tree[(l<<1)+1].mx);
	l>>=1;
    }
    
    /* usuwanie listenerow z wezlow */
    list_for_each(it,&listen_nodes[k]){
	listener = list_entry(it,struct Listener,listen_list);
	list_del(&listener->node_list);
    }
    
    /* zwalnianie listenerow */
    while (listen_nodes[k].next!=&listen_nodes[k]){
	listener = list_entry(listen_nodes[k].next,struct Listener,listen_list);
	listen_nodes[k].next = listen_nodes[k].next->next;
	free(listener);
    }
}

/* zwraca dowolna krawedz z k do przodu jako element do ktorego prowadzi lub minf, jesli nie ma */
int getForwardEdge(int k){
    int b=B[k];
    int h=A[k];
    int left=k+zz-1;
    int right=b+zz+1;
    while ((left>>1) != (right>>1)){
	if ((!(left&1)) && (tree[left^1].mx>h))
	    return R[tree[left^1].mx];
	if (((right&1)) && (tree[right^1].mx>h))
	    return R[tree[right^1].mx];
	left>>=1;
	right>>=1;
    }
    return minf;
}

/* zwraca dowolna krawedz z k do tylu jako element do ktorego prowadzi lub minf, jesli nie ma */
int getBackwardEdge(int k){
    int my_h=A[k];
    int l=k+zz;
    struct Listener* listener;
    while (l>0){
	if (!list_empty(&tree[l].listeners)){
	    listener = list_entry(tree[l].listeners.prev,struct Listener,node_list);
	    if (listener->h < my_h) return R[listener->h];
	}
	l>>=1;
    }
    return minf;
}

/* czyta wejscie */
inline void buildA(){
    n=RI();
    REP(i,n) A[i]=RI()-1;
}

/* buduje R */
inline void buildR(){
    REP(i,n) R[A[i]]=i;
}

/* buduje B */
inline void buildB(){
    int m=minf;
    REP(i,n)
	B[R[i]]=(m=max(m,R[i]));
}

/* buduje drzewo licznikowe */
inline void buildTree(){
    REP(t,MAX) colors[t]=-1;
    REP(t,2*zz){
	tree[t].mx=minf;
	INIT_LIST_HEAD(&tree[t].listeners);
    }
    REP(i,n)
	addToBucket(R[i]);
}

/* dfs kolorujacy */
void dfs(int v, int c){
    colors[v]=c;
    deleteFromBucket(v);
    int e;
    while ((e=getForwardEdge(v))>=0)
	dfs(e,c^1);
    while ((e=getBackwardEdge(v))>=0)
	dfs(e,c^1);
}

/* buduje przykladowe rozwiazanie */
inline void buildSolution(){
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
    buildB();
    buildTree();
    buildSolution();
    buildAnswer();
    return 0;
}
