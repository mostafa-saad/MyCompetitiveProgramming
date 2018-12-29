/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Koleje (KOL)                                               *}
{*   Plik:    kol.cpp                                                    *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Rozwiazanie wzorcowe.                                      *}
{*                                                                       *}
{*************************************************************************/
#include<stdio.h>

const int N=5000; //max. liczba wierzch.
const int M=1000000; //max. liczba kraw.
const int INF=1000000000; //liczba wieksza niz max koszt N krawedzi

struct edge{
  int to; //wierzch. docelowy
  int wei; //waga krawedzi
  int next; //kolejny wierzcholek na liscie sasiedztwa
};

int n,m; //liczba wierzcholkow i krawedzi
edge edges[2*M]; //lista sasiedztwa
int v[N+1]; //lista sasiedztwa
int stays[N+1]; //czy wierzcholek musi pozostac (1-tak/0-nie)
int st; //ile wierzcholkow ma zostac

int dist[N+1]; //odleglosci od aktualnego drzewa
int heap_pos[N+1]; //pozycja w kopcu
int heap[N+1]; //kopiec
int heap_size; //akt. rozmiar kopca
int prev[N+1]; //skad przyszlismy do danego wierzcholka
int found_obligatory; //ile obowiazkowych wierzcholkow znaleziono
int found_from[N], found_to[N]; //znalezione krawedzie
int found_edges; //liczba znalezionych krawedzi
int sum; //suma wag dodanych krawedzi

/************************** parsowanie wejscia **************************/

void input() {
  int a,b,u;
  int tmp=0; //kolejna wolna poz. na l.sasiedztwa
  scanf("%d %d ", &n, &m);
  for (int i=1; i<=n; i++) {
    v[i]=-1;
  }
  for (int i=0; i<m; i++) {
    scanf("%d %d %d ", &a, &b, &u);
    edges[tmp].to=b;
    edges[tmp].wei=u;
    edges[tmp].next=v[a];
    v[a]=tmp;
    tmp++;
    edges[tmp].to=a;
    edges[tmp].wei=u;
    edges[tmp].next=v[b];
    v[b]=tmp;
    tmp++;
  }
  scanf("%d ", &st); //ile wierzcholkow pozostaje
  for (int i=1; i<=n; i++) stays[i]=0;
  for (int i=0; i<st; i++) {
    scanf("%d ",&a);
    stays[a]=1;
  }
}

/************************* operacje na kopcu ************************/

//zmniejszenie odleglosci, jezeli poprzednia byla wieksza
void decrease_key(int nr, int val, int from) {
//printf("decrease:%d (val:%d, from:%d)\n",nr,val,from);
  if (val >= dist[nr]) return;
  dist[nr]=val;
  prev[nr]=from;
  if (heap_pos[nr]==-1) {
    heap_pos[nr]=heap_size;
    heap[heap_size]=nr;
    heap_size++;
  }
  int tmp = heap_pos[nr];
  while (tmp>0 && val<dist[heap[(tmp-1)/2]]) {
    heap_pos[heap[(tmp-1)/2]]=tmp;
    heap[tmp]=heap[(tmp-1)/2];
    tmp=(tmp-1)/2;
  }
  heap_pos[nr]=tmp;
  heap[tmp]=nr;
}

//usuniecie elementu o najmniejszej odleglosci, zwraca numer wierzcholka
int del_min() {
  int vv = heap[0];
  heap_pos[vv]=-1;
  heap_size--;
  if (heap_size>0) {
    int tmp=0;
    int nr=heap[heap_size];

    bool end=false;
    while (!end) {
      int val=dist[nr];
      int smallest=tmp;
      if (2*tmp+1<heap_size)
         if (dist[heap[2*tmp+1]]<val) {val=dist[heap[2*tmp+1]]; smallest=2*tmp+1;}
      if (2*tmp+2<heap_size)
         if (dist[heap[2*tmp+2]]<val) {val=dist[heap[2*tmp+2]]; smallest=2*tmp+2;}
      if (smallest==tmp) end=true;
      else {
        heap[tmp]=heap[smallest];
        heap_pos[heap[tmp]]=tmp;
        tmp=smallest;
      }
    }
    heap[tmp]=nr;
    heap_pos[nr]=tmp;
  }
  return vv;
}

/********************************************/


//dodaje dany wierzcholek (lub cala sciezke) do drzewa
void add_to_tree(int nr) {
  if (prev[nr]!=-1 && dist[prev[nr]]!=0) add_to_tree(prev[nr]);
//printf("(%d,%d)\n",prev[nr],nr);
  dist[nr]=0;
  //ewentualnie usuwa wierzcholek z kopca
  if (heap_pos[nr]!=-1) {
    decrease_key(nr,-1,prev[nr]);
    del_min();
    dist[nr]=0;
  }
  //dodaje krawedz do listy krawedzi
  if (found_obligatory>0) {
    found_from[found_edges]=prev[nr];
    found_to[found_edges]=nr;
    found_edges++;
  }
  if (stays[nr]==1) found_obligatory++;
  int next_neigh = v[nr];
  while (next_neigh!=-1) {
    decrease_key(edges[next_neigh].to,edges[next_neigh].wei, nr);
    next_neigh=edges[next_neigh].next;
  }
  //..
}

//znajduje kolejne krawedzie do drzewa rozpinajacego
void find_tree() {
  while (found_obligatory<st) {
    int min=del_min();
    if (stays[min]==1) {//to byl wierzcholek 'obowiazkowy'
      sum+=dist[min];
      add_to_tree(min);
    }
    else {//to byl wierzcholek opcjonalny
      int next_neigh = v[min];
      while (next_neigh!=-1) {
        decrease_key(edges[next_neigh].to,dist[min]+edges[next_neigh].wei, min);
        next_neigh=edges[next_neigh].next;
      }
    }
//for (int i=0; i<heap_size; i++) printf("%d-%d ",heap[i],dist[heap[i]]);
//printf(" ***\n");
  }
}

void start() {
  //inicjowanie kopca/odlegolsci itp.
  for (int i=1; i<=n; i++) dist[i]=INF;
  for (int i=1; i<=n; i++) heap_pos[i]=i-1;
  for (int i=0; i<n; i++) heap[i]=i+1;
  heap_size=n;
  found_edges=0;
  found_obligatory=0;
  sum=0;
  int tmp=1;
  while (stays[tmp]==0) tmp++;
  prev[tmp]=-1;
  decrease_key(tmp,0,-1);
  find_tree();
}

int main() {
  input();
  if (st==1) {printf("%d %d\n", 0, 0); return 0;}
  start();
  printf("%d %d\n",sum, found_edges);
  for (int i=0; i<found_edges; i++)
    printf("%d %d\n", found_from[i], found_to[i]);
  return 0;
}
