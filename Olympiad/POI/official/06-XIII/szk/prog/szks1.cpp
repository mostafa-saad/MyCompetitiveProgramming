/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZK (Szko³y)                                   *
 *   Plik:                szks1.cpp                                      *
 *   Autor:               Pawe³ Parys                                    *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,l,h) for (int a=(l); a<=(h); ++a)

using namespace std;

#define SIZE 200    // maximal number of schools
#define GSIZE (2*SIZE+2)  // maximal number of vertices in graph
#define MAX_EDGE (SIZE+1)  // maximal number of edges from 1 vertex
#define EDGES (SIZE*(SIZE+2))  // maximal number of edges
#define INF 1000000000

int ON, cur[SIZE], low[SIZE], high[SIZE], score[SIZE];

int e0[EDGES], e1[EDGES], edir[EDGES], ecost[EDGES], ecounter;
int edges[GSIZE][MAX_EDGE], esize[GSIZE];
int GN, START, STOP;

void add_edge(int v0, int v1, int c)
{
  edges[v0][esize[v0]++] = ecounter;
  edges[v1][esize[v1]++] = ecounter;
  e0[ecounter] = v0;
  e1[ecounter] = v1;
  edir[ecounter] = 1;
  ecost[ecounter] = c;
  ecounter++;
}

void construct_graph()
// vertices 0 .. ON-1 - schools
// vertices ON .. 2*ON-1 - numbers
// vertex 2*ON - initial vertex, connected with all schools
// vertex 2*ON+1 - last vertex, connected with all numbers
{
  GN = 2*ON+2;
  START = 2*ON;
  STOP = 2*ON+1;
  ecounter = 0;
  REP(a, GN)
    esize[a] = 0;
  REP(a, ON)
  {
    add_edge(START, a, 0);
    add_edge(a+ON, STOP, 0);
    FOR(b, low[a], high[a])
      add_edge(a, b+ON, abs(cur[a]-b)*score[a]);
  }
}

int dist[GSIZE], back[GSIZE];

bool find_path()
{
  REP(a, GN)
    dist[a] = INF;
  dist[START] = 0;
  REP(xxx, GN-1)
  {
    REP(en, ecounter)
    {
      int v0 = e0[en], v1 = e1[en], c = edir[en]*ecost[en];
      if (edir[en]<0)
        swap(v0, v1);
      c += dist[v0];
      if (c<dist[v1])
      {
        dist[v1] = c;
        back[v1] = en;
      }
    }
  }
  return dist[STOP]<INF;
}

void extend()
{
  int v = STOP;
  while (v!=START)
  {
    int en = back[v];
    v ^= e0[en]^e1[en];
    edir[en] = -edir[en];
  }
}

int main()
{
  scanf("%d", &ON);
  REP(a,ON)
  {
    scanf("%d%d%d%d", cur+a, low+a, high+a, score+a);
    --cur[a]; --low[a]; --high[a];
  }
  construct_graph();
  REP(a, ON)
  {
    if (!find_path())
    {
      printf("NIE\n");
      return 0;
    }
    extend();
  }
  int k = 0;
  REP(a, ecounter)
    if (edir[a]<0)
      k += ecost[a];
  printf("%d\n", k);
}
