/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo3.c                                                    *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Alternatywne rozwiazanie wzorcowe. Zachlannie przegladamy *
 *             wierzcholki wkolejnosci nierosnacych stopni i             *
 *             przyporzadkowujemy im dowolne krawedzie. Zlozonosc O(n+m).*
 *                                                                       *
 *************************************************************************/
*/
#include <stdio.h>
#include <assert.h>

#define MAXN  100000
#define MAXM  200000
struct Edge {
  int a,b;
  int isUsed;
};

struct Edge edges[MAXM];

int degrees[MAXM];

struct Vertex {
  int degree;
  int prev;
  int next;
  int adj;
  int e;
};
struct Vertex vertices[MAXN];

struct VertEdge {
  int edge;
  int next;
};
struct VertEdge vertEdges[MAXM*2];
int vertEdgesNum = 0;

inline void dodaj(int degree, int v) 
{
    int prev = degrees[degree];
    vertices[v].next = prev;
    vertices[v].prev = -1;
    if( -1 != prev ) {
      vertices[prev].prev = v;
    }
    degrees[degree] = v;
}

inline void usun(int v)
{
  int prev = vertices[v].prev;
  int next = vertices[v].next;
  if( -1 != prev ) vertices[prev].next = next;
  if( -1 != next ) vertices[next].prev = prev;
}

inline int findFree(int v)
{
  int akt = vertices[v].e;
  while( -1 != akt ) {
    if( edges[vertEdges[akt].edge].isUsed ) {
      akt = vertEdges[akt].next;
    } else {
      return vertEdges[akt].edge;
    }
  }
  assert( ! "Powinnismy byli znalezc wolna krawedz" );
  return -1;
}

int main()
{
  int n,m,i;
  scanf("%d %d", &n, &m);
  for(i=0; i<n; ++i) {
    vertices[i].e = -1;
    vertices[i].adj = -1;
  }
  for(i=0; i<m; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    --a; --b;
    edges[i].a = a;
    edges[i].b = b;
    ++vertices[a].degree;
    ++vertices[b].degree;

    struct VertEdge *ve = vertEdges+vertEdgesNum;
    ve->next = vertices[a].e;
    ve->edge = i;
    vertices[a].e = vertEdgesNum;
    ++vertEdgesNum;
    
    ve = vertEdges+vertEdgesNum;
    ve->next = vertices[b].e;
    ve->edge = i;
    vertices[b].e = vertEdgesNum;
    ++vertEdgesNum;
  }
  for(i=0; i<m; ++i) {
    degrees[i] = -1;
  }
  int mindeg = m;
  int isPossibe = 1;
  for(i=0; i<n; ++i) {
    int degree = vertices[i].degree;
    if( degree < mindeg ) mindeg = degree;
    dodaj(degree,i);
  }
  for(i=0; i<n; ++i) {
    if( -1 != degrees[0] ) {
      isPossibe = 0;
      break;
    }
    assert(mindeg < n);
    int v = degrees[mindeg];
    degrees[mindeg] = vertices[degrees[mindeg]].next;
    usun(v);
    int k=findFree(v);
    assert(k >= 0);
    int adj = edges[k].a == v ? edges[k].b : edges[k].a;
    vertices[v].adj = adj;
    if( -1 == vertices[adj].adj ) {
      usun(adj);
      if (degrees[vertices[adj].degree] == adj) {
        degrees[vertices[adj].degree] = vertices[adj].next;
      }
      if( --vertices[adj].degree < mindeg ) mindeg = vertices[adj].degree;
      dodaj(vertices[adj].degree, adj);
    }
    edges[k].isUsed = 1;
    while (mindeg < n && -1 == degrees[mindeg]) {
      ++mindeg;
    }
  }
  if( isPossibe ) {
    printf("TAK\n");
    for(i=0; i<n; ++i) {
      printf("%d\n", vertices[i].adj + 1);
    }
  } else {
    printf("NIE\n");
  }
  return 0;
}
