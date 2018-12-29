/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clob4.cpp                                                 *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Rozwiazanie niepoprawne, ktore przeglada wierzcholki      *
 *             w kolejnosci rosnacych poczatkowyc stopni.                *
 *             Zlozonosc O(n+m).                                         *
 *                                                                       *
 *************************************************************************/
#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>

using namespace std;

const int MAXN = 100000;
const int MAXM = 200000;

int vertices[MAXN];
pair<int, int> verticesOrder[MAXN];

struct Edge {
  int a,b;
  bool used;
};
Edge edges[MAXM];

vector<int> neighbours[MAXN];


int main()
{
  int n,m;
  scanf("%d %d", &n, &m );
  for(int i=0; i<n; ++i) {
    vertices[i] = -1;
    verticesOrder[i].first = 0;
    verticesOrder[i].second = i;
  }
  int edgeNum = 0;
  for(int i=0; i<m; ++i) {
    int a,b;
    scanf("%d %d", &a, &b);
    --a, --b;
    neighbours[a].push_back(edgeNum);
    neighbours[b].push_back(edgeNum);
    edges[edgeNum].a = a;
    edges[edgeNum].b = b;
    edges[edgeNum++].used = false;
    verticesOrder[a].first++;
    verticesOrder[b].first++;
  }
  bool isPossible = true;
  // Randomizing search
  for(int i=0; i<n; ++i) {
    random_shuffle(neighbours[i].begin(), neighbours[i].end());
  }
  sort(verticesOrder, verticesOrder+n);

  for(int i=0; i<n; ++i) {
    int v = verticesOrder[i].second;
    for(int j=0; j<(int)neighbours[v].size(); ++j) {
      if( !edges[neighbours[v][j]].used ) {
        int edge = neighbours[v][j];
        assert(edges[edge].a == v || edges[edge].b == v);
        vertices[v] = edges[edge].a == v ? edges[edge].b : edges[edge].a;
        edges[edge].used = true;
        break;
      }
    }
    if( -1 == vertices[v] ) {
      isPossible = false;
      break;
    }
  }
  if( isPossible ) {
    printf("TAK\n");
    for(int i=0; i<n; ++i) {
      printf("%d\n", vertices[i]+1);
    }
  } else {
    printf("NIE\n");
  }
}
