#include <algorithm>
#include <cstdio>

using namespace std;

#define MAX 200

const int oo = 1000000;

int n, m;
int g[MAX][MAX];

char done[MAX][MAX];
int dist[MAX][MAX];

int main(void) {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) 
    for (int j = 0; j < n; ++j) 
      g[i][j] = i == j ? 0 : oo;
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[--u][--v] = 1;
  }
  for (int k = 0; k < n; ++k) 
    for (int i = 0; i < n; ++i) 
      for (int j = 0; j < n; ++j) 
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
  
  for (int i = 0; i < n; ++i) 
    for (int j = 0; j < n; ++j) {
      dist[i][j] = oo;
      done[i][j] = 0;
    }
  
  dist[1][1] = 1;
  for (;;) {
    int a = -1, b = -1;
    for (int i = 0; i < n; ++i) 
      for (int j = 0; j < n; ++j) {
        if (done[i][j]) continue;
        if (a == -1 || dist[i][j] < dist[a][b]) { a = i; b = j; }
      }
    if (a == 0 && b == 0) {
      break;
    }
    done[a][b] = 1;
    for (int c = 0; c < n; ++c)
      for (int d = 0; d < n; ++d) {
        if (c == a || c == b || d == a || d == b) continue;
        dist[c][d] = min(dist[c][d], dist[a][b] + g[b][c] + g[c][d] + g[d][a] - 1);
      }
  }
  printf("%d\n", dist[0][0]);
  return 0;
}
