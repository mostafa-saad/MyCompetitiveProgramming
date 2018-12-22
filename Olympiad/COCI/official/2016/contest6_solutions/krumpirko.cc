#include <cstdio>
#include <algorithm>
#include <numeric>
#include <cstring>

using namespace std;

const int MAXN = 105;
const int MAXW = 505;
const int inf = 1 << 30;

int n, l;
int a[MAXN];
int c[MAXN];

int dp[MAXN][MAXN][MAXW];
int f (int x, int c, int w) {
  if (w < 0) return inf;
  if (c < 0) return inf;
  if (c == 0 && w == 0) return 0;
  if (x == n) return inf;
  int &ret = dp[x][c][w];
  if (ret != -1) return ret;
  ret = inf;
  return ret = min(f(x+1, c-1, w - a[x]) + ::c[x], f(x+1, c, w));
}

int main (void){
  memset(dp, -1, sizeof dp);
  scanf("%d%d", &n, &l);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < n; ++i) scanf("%d", &c[i]);
  int sumc = accumulate(c, c+n, 0);
  int sumw = accumulate(a, a+n, 0);
  double ans = inf * 1.0 * inf;
  for (int i = 0; i < MAXW; ++i) {
    int c0 = min(f(0, n-l, i), f(0, l, i));
    if (c0 == inf) continue;
    ans = min(ans, c0*1.0 / i * (sumc - c0) / (sumw - i));
  }

  printf("%.3lf\n", ans);

  return 0;
}

