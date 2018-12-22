#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long llint;
typedef pair <int, int> pii;

const int MAXN = 21;

int n, k;
int a[MAXN][MAXN];
int dp[1 << MAXN];

int solve(int mask) {
  if (__builtin_popcount(mask) == k) return 0;
  int &ret = dp[mask];
  if (ret != -1) return ret;
  ret = 1 << 30;
  for (int i = 0; i < n; ++i) {
    if (!(mask & (1 << i)) ) continue;
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      if (!(mask & (1 << j))) continue;
      ret = min(ret, solve(mask ^ (1 << i)) + a[i][j]);
    }
  }
  return ret;
}

int main (void){
  memset(dp, -1, sizeof dp);
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) 
    for (int j = 0; j < n; ++j)
      scanf("%d", &a[i][j]);
  printf("%d\n", solve((1 << n) - 1));
  return 0;
}

