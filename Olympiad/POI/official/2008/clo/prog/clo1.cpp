/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo1.cpp                                                  *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Rozwiazanie wzorcowe, przechodzace dwa razy przy uzyciu   *
 *             BFSa. Zlozonosc O(n+m).                                   *
 *                                                                       *
 *************************************************************************/
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <deque>

using namespace std;

#define MAXN  100000
#define MAXM  200000

struct Vertex {
  int visited;
  int adj;
  int prev;
};
struct Vertex vertices[MAXN];

vector<int> vertEdges[MAXN];

deque<int> queue;

inline int queueIsEmpty() {
  return queue.empty();
}

inline void enqueue(int v) {
  queue.push_back(v);
}

inline int dequeue() {
  int v = queue.front();
  queue.pop_front();
  return v;
}

inline void queueInit() {
  queue.clear();
}

void solve2(int v, int adj) {
  vertices[v].adj = adj;
  queueInit();
  int rozm = vertEdges[v].size();
  for (int i = 0; i < rozm; ++i) {
    int w = vertEdges[v][i];
    if( w != adj ) {
      enqueue(w);
      vertices[w].adj = v;
    }
  }
  vertices[v].visited = 1;
  while (!queueIsEmpty()) {
    int w = dequeue();
    vertices[w].visited = 1;
    int rozm = vertEdges[w].size();
    for (int i = 0; i < rozm; ++i) {
      int pom = vertEdges[w][i];
      if (0 > vertices[pom].adj) {
        enqueue(pom);  
        vertices[pom].adj = w;
      }
    }
  }
}

void solve(int v) {
  queueInit();
  enqueue(v);
  while( !queueIsEmpty() ) {
    int w = dequeue();
    vertices[w].visited = 1;
    vector<int> &adj = vertEdges[w];
    int rozm = adj.size();
    for (int i = 0; i < rozm; ++i) {
      int akt = adj[i];
      if (akt != vertices[w].prev) {
        if( -1 == vertices[akt].adj ) {
          vertices[akt].adj = -2;
          enqueue(akt);
          vertices[akt].prev = w;
        } else {
          return solve2(akt, w);
        }
      }  
    }
  }
}

int main() {
  int n,m,i;
  scanf("%d %d", &n, &m);
  for(i=0; i<n; ++i) {
    vertices[i].adj = -1;
    vertices[i].visited = 0;
    vertices[i].prev = -1;
  }
  for(i=0; i<m; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    --a; --b;

    vertEdges[a].push_back(b);
    vertEdges[b].push_back(a);
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
