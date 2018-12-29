/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo.c                                                     *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Rozwiazanie wzorcowe, przechodzace dwa razy przy uzyciu   *
 *             BFSa. Zlozonosc O(n+m).                                   *
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

int queue[MAXN];
int queueFirst=0;
int queueLast=0;

inline int queueIsEmpty()
{
  return (queueFirst == queueLast);
}

inline void enqueue(int v) 
{
  queue[queueLast++] = v;
  if( MAXN == queueLast ) {
    queueLast = 0;
  }
  assert(queueLast != queueFirst);
}

inline int dequeue()
{
  assert( queueFirst != queueLast );
  int v = queue[queueFirst++];
  if( MAXN == queueFirst ) {
    queueFirst = 0;
  }
  return v;
}

inline void queueInit()
{
  queueFirst=queueLast=0;
}

void solve2(int v, int adj)
{
  vertices[v].adj = adj;
  queueInit();
  int akt = vertices[v].e;
  while( -1 != akt ) {
    int w = vertEdges[akt].edge;
    if( w != adj ) {
      enqueue(w);
      vertices[w].adj = v;
    }
    akt = vertEdges[akt].next;
  }
  vertices[v].visited = 1;
  while( ! queueIsEmpty() ) {
    int w = dequeue();
    vertices[w].visited = 1;
    int akt = vertices[w].e;
    while( -1 != akt ) {
      int pom = vertEdges[akt].edge;
      if( 0 > vertices[pom].adj ) {
        vertices[pom].adj = w;
        enqueue(pom);  
      }
      akt = vertEdges[akt].next;
    }
  }
}

void solve(int v)
{
  queueInit();
  enqueue(v);
  while( !queueIsEmpty() ) {
    int w = dequeue();
    vertices[w].visited = 1;
    int akt = vertices[w].e;
    while( -1 != akt ) {
      int adj = vertEdges[akt].edge;
      if( adj != vertices[w].prev ) {
        if( -1 == vertices[adj].adj ) {
          vertices[adj].adj = -2;
          enqueue(adj);
          vertices[adj].prev = w;
        } else {
          return solve2(adj,w);
        }
      }
      akt = vertEdges[akt].next;
    }
  }
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
