#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>

typedef long long llint;
typedef int mask_t;

const llint oo = 0x3f3f3f3f3f3f3f3fll;
const int maxn = 1001;
const int maxk = 1001;

const int NS = 11;
const mask_t slucajevi[NS] = {0x00, 0x11, 0x22, 0x44, 0x03, 0x06, 0x17, 0x47,
  0x33, 0x66, 0x55};
const int slucajevi_cost[NS] = {0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2};

int map[3][maxn];
llint dp[maxn][maxk][8];

llint _get(int col, mask_t one) {
  llint sol = 0;
  if (col < 0 && one) return -oo;
  sol += (one & 1) * map[0][col]; one >>= 1;
  sol += (one & 1) * map[1][col]; one >>= 1;
  sol += (one & 1) * map[2][col]; one >>= 1;
  return sol;
}

llint get(int n, mask_t slucaj) {
  return _get(n - 1, slucaj) + _get(n - 2, slucaj >> 4);
}

llint solve(int n, int k, mask_t last) {
  if (n == 0) return k == 0 ? 0 : -oo;
  if (!k) return 0;
  if (k < 0) return -oo;

  llint &ret = dp[n][k][last];
  if (ret != oo) return ret;
  ret = -oo;
  for (int ns = 0; ns < NS; ++ns) {
    mask_t right = slucajevi[ns] & 0xf;
    mask_t left = (slucajevi[ns] >> 4) & 0xf;
    int cost = slucajevi_cost[ns];
    if (last & right) continue;
    ret = std::max(ret, get(n, slucajevi[ns]) + solve(n - 1, k - cost, left));
  }
  return ret;
}

int main() {
  int N, K;
  scanf("%d%d", &N, &K);
  for (int j = 0; j < N; ++j)
    for (int i = 0; i < 3; ++i)
      scanf("%d", &map[i][j]);
  memset(dp, 0x3f, sizeof dp);
  printf("%lld\n", solve(N, K, 0));
  return 0;
}
