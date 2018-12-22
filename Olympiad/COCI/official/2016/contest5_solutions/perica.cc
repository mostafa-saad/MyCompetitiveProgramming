#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long llint;

const int mod = (1e9) + 7;
const int MAXN = 1 << 17;
const int MAXK = 55;

int comb[MAXN][MAXK];
int a[MAXN];
int n, k;

int main (void) {
  scanf("%d%d", &n, &k);
  comb[0][0] = 1;
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= k; ++j) {
      comb[i][j] = comb[i-1][j];
      if (j > 0) comb[i][j] += comb[i-1][j-1];
      if (comb[i][j] >= mod) comb[i][j] -= mod;
    }

  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  sort(a, a+n);
  llint ans = 0;
  for (int i = 0; i < n; ++i) 
    ans = (ans + a[i] * (llint)comb[i][k-1])%mod;

  printf("%lld\n", ans);

  return 0;
}
