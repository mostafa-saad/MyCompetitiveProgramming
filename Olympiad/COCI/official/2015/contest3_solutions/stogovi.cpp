#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)

const int MAXN = 300100;
const int LG = 20;

int L[MAXN][LG];
int d[MAXN];
int x[MAXN];

int lca(int u, int v) {
  if (d[u] < d[v]) swap(u, v);
  for (int j = LG-1; j >= 0; --j)
    if (d[u]-(1<<j) >= d[v]) u = L[u][j];
  if (u == v) return u;
  for (int j = LG-1; j >= 0; --j)
    if (L[u][j] != L[v][j]) u = L[u][j], v = L[v][j];
  return L[u][0];
}

int main(void) {
  int n;
  scanf("%d", &n);
  
  L[0][0] = -1, d[0] = 0, x[0] = 0;
  
  FOR(i, 1, n+1) {
    char s[10];
    int v;
    scanf("%s %d", s, &v);
 
    v = x[v];
    
    if (s[0] == 'a') {
      x[i] = i;
      d[i] = d[v] + 1;
      L[i][0] = v;
      FOR(j, 1, LG)
        if (L[i][j-1] != -1) L[i][j] = L[ L[i][j-1] ][j-1]; else
          L[i][j] = L[i][j];
    }
    
    if (s[0] == 'b') {
      assert(v > 0);
      printf("%d\n", v);
      x[i] = L[v][0];
    }
    
    if (s[0] == 'c') {
      int w;
      scanf("%d", &w);
      w = x[w];
      x[i] = v;
      printf("%d\n", d[lca(v, w)]);
    }
  }
  return 0;
}
