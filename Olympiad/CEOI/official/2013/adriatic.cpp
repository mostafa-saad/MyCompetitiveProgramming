// CEOI 2013 - Task: Adriatic - Solution
// Author: Gustav Matula

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXC 2500
#define MAXN 250005

int N;
int x[MAXN], y[MAXN];

int on[MAXC+2][MAXC+2];
int cnt[MAXC+2][MAXC+2];
int minx[MAXC+2][MAXC+2];
int miny[MAXC+2][MAXC+2];
int maxx[MAXC+2][MAXC+2];
int maxy[MAXC+2][MAXC+2];

int mur[MAXC+2][MAXC+2];
int mdl[MAXC+2][MAXC+2];

int ur(int x, int y) {
  int &ref = mur[x][y];
  if (ref != -1) return ref;
  if (cnt[x][MAXC] - cnt[x][y-1] == 0) return ref =  0;
  return ref = cnt[x][MAXC] - cnt[x][y-1] + ur(min(x, minx[x][y-1]), max(y, maxy[x+1][y]));
}

int dl(int x, int y) {
  int &ref = mdl[x][y];
  if (ref != -1) return ref;
  if (cnt[MAXC][y] - cnt[x-1][y] == 0) return ref =  0;
  return ref = cnt[MAXC][y] - cnt[x-1][y] + dl(max(x, maxx[x][y+1]), min(y, miny[x-1][y]));
}

int main(void)
{
  scanf("%d", &N);

  for (int i = 0; i < N; ++i) {
    scanf("%d%d", x+i, y+i);
    on[x[i]][y[i]] = 1;
  }

  memset(minx, 0x3f, sizeof minx);
  memset(miny, 0x3f, sizeof miny);

  for (int i = 1; i <= MAXC; ++i) {
    for (int j = 1; j <= MAXC; ++j) {
      cnt[i][j] = on[i][j] + cnt[i-1][j] + cnt[i][j-1] - cnt[i-1][j-1];
      minx[i][j] = on[i][j] ? min(i, minx[i-1][j]) : min(minx[i-1][j], minx[i][j-1]);
      miny[i][j] = on[i][j] ? min(j, miny[i][j-1]) : min(miny[i-1][j], miny[i][j-1]);
    }
  }

  for (int i = MAXC; i >= 1; --i) {
    for (int j = MAXC; j >= 1; --j) {
      maxx[i][j] = on[i][j] ? max(i, maxx[i+1][j]) : max(maxx[i+1][j], maxx[i][j+1]);
      maxy[i][j] = on[i][j] ? max(j, maxy[i][j+1]) : max(maxy[i+1][j], maxy[i][j+1]);
    }
  }

  memset(mur, -1, sizeof mur);
  memset(mdl, -1, sizeof mdl);

  for (int i = 0; i < N; ++i) 
    printf("%d\n", cnt[MAXC][MAXC] + ur(x[i], y[i]) + dl(x[i], y[i]) - 3);

  return 0;
}
