/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo7.cpp                                                  *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Rozwiazanie wzorcowe, przechodzace dwa razy przy uzyciu   *
 *             DFSa. Zlozonosc O(n+m). Zostalo ono specjalnie zapisane   *
 *             przez mozliwosc przekroczenia glebokosci stosu.           *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

const int MAXN = 100000;
const int MAXM = 200000;

struct Vertex {
  bool visited;
  int adj;
  int prev;
};
struct Vertex vertices[MAXN];

vector<int> vertEdges[MAXN];

void solve2(int v, int adj) {
  vertices[v].adj = adj;
  vertices[v].visited = true;
  for (int i=0; i < (int)vertEdges[v].size(); ++i) {
    int edge = vertEdges[v][i];
    if (edge != adj ) {
      if (0 > vertices[edge].adj) {
        solve2(edge,v);
      }
    }
  }
}

int solve(int v) {
  vertices[v].visited = 1;
  vertices[v].adj = -2;
  int prev = vertices[v].prev;
  for (int i=0; i < (int)vertEdges[v].size(); ++i) {
    int adj = vertEdges[v][i];
    if (adj != prev) {
      if (-1 == vertices[adj].adj) {
        vertices[adj].prev = v;
        if (solve(adj)) {
          return 1;
        }
      } else {
        solve2(adj,v);
        return 1;
      }
    }
  }
  return 0;
}

int main(){
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
    if (!vertices[i].visited) {
      solve(i);
    }
  }
  bool isPossibe = true;
  for (i=0; i<n; ++i) {
    if (0 > vertices[i].adj) {
      isPossibe = false;
      break;
    }
  }
  if (isPossibe) {
    printf("TAK\n");
    for (i=0; i<n; ++i) {
      printf("%d\n", vertices[i].adj + 1);
    }
  } else {
    printf("NIE\n");
  }
}
