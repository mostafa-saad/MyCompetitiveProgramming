/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo6.c                                                    *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Rozwiazanie wzorcowe, przechodzace dwa razy przy uzyciu   *
 *             DFSa. Zlozonosc O(n+m). Zostalo ono specjalnie zapisane   *
 *             przez mozliwosc przekroczenia glebokosci stosu            *
 *                                                                       *
 *************************************************************************/
#include <stdio.h>
#include <assert.h>

#define MAXN  100000
#define MAXM  200000

struct Vertex {
  int visited;
  int adj;
  int prev;
  int e;
};
struct Vertex vertices[MAXN];

struct VertEdge {
  int edge;
  int next;
};
struct VertEdge vertEdges[MAXM*2];
int vertEdgesNum = 0;

void solve2(int v, int adj)
{
  vertices[v].adj = adj;
  vertices[v].visited = 1;
  int akt = vertices[v].e;
  while( -1 != akt ) {
    int edge = vertEdges[akt].edge;
    if( edge != adj ) {
      if( 0 > vertices[edge].adj ) {
        solve2(edge,v);
      }
    }
    akt = vertEdges[akt].next;
  }
}

int solve(int v)
{
  vertices[v].visited = 1;
  vertices[v].adj = -2;
  int akt = vertices[v].e;
  int prev = vertices[v].prev;
  while( -1 != akt ) {
    int adj = vertEdges[akt].edge;
    if( adj != prev ) {
      if( -1 == vertices[adj].adj ) {
        vertices[adj].prev = v;
        if( solve(adj) ) {
          return 1;
        }
      } else {
        solve2(adj,v);
        return 1;
      }
    }
    akt = vertEdges[akt].next;
  }
  return 0;
}

int main()
{
  int n,m,i;
  scanf("%d %d", &n, &m);
  for(i=0; i<n; ++i) {
    vertices[i].e = -1;
    vertices[i].adj = -1;
    vertices[i].visited = 0;
    vertices[i].prev = -1;
  }
  for(i=0; i<m; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    --a; --b;

    struct VertEdge *ve = vertEdges+vertEdgesNum;
    ve->next = vertices[a].e;
    ve->edge = b;
    vertices[a].e = vertEdgesNum;
    ++vertEdgesNum;
 
    ve = vertEdges+vertEdgesNum;
    ve->next = vertices[b].e;
    ve->edge = a;
    vertices[b].e = vertEdgesNum;
    ++vertEdgesNum;
  }
  for(i=0; i<n; ++i) {
    if( ! vertices[i].visited ) {
      solve(i);
    }
  }
  int isPossibe = 1;
  for(i=0; i<n; ++i) {
    if( 0 > vertices[i].adj ) {
      isPossibe = 0;
      break;
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
