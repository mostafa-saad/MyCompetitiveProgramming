#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 50;

int N, V;
char s[MAXN][MAXN];
int v[MAXN][MAXN];
int visine[MAXN * MAXN];

int bio[MAXN][MAXN];

void dfs(int x, int y, int v1, int v2) {
  if (bio[x][y]) return;
  bio[x][y] = 1;

  for (int dx = -1; dx <= 1; ++dx)
    for (int dy = -1; dy <= 1; ++dy)
      if (dx || dy) {
        int nx = x + dx;
        int ny = y + dy;
        if (nx < 0 || nx >= N) continue;
        if (ny < 0 || ny >= N) continue;
        if (v[nx][ny] < v1 || v[nx][ny] > v2) continue;
        dfs(nx, ny, v1, v2);
      }
}

bool f(int v1, int v2) {
  memset(bio, 0, sizeof bio);

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (s[i][j] == 'P') {
        if (v[i][j] < v1 || v[i][j] > v2) return false; 
        dfs(i, j, v1, v2);
      }

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (s[i][j] == 'K' && !bio[i][j])
        return false;

  return true;
}

int main(void) 
{
  scanf("%d", &N);
  for (int i = 0; i < N; ++i)
    scanf("%s", s[i]);

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) {
      scanf("%d", &v[i][j]);
      visine[V++] = v[i][j];
    }

  sort(visine, visine + V);
  V = unique(visine, visine + V) - visine;

  int ret = 1 << 30;
  for (int x1 = 0; x1 < V; ++x1) {
    int lo = x1;
    int hi = V - 1;
    while (lo < hi) {
      int x2 = lo + (hi - lo) / 2;
      if (f(visine[x1], visine[x2]))
        hi = x2;
      else
        lo = x2 + 1;
    }
    if (f(visine[x1], visine[lo]))
      ret = min(ret, visine[lo] - visine[x1]);
  }

  printf("%d\n", ret);
  return 0;
}
