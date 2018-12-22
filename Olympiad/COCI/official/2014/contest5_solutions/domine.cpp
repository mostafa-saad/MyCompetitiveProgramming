#include <cstdio>
#include <cassert>
#include <algorithm>

typedef long long llint;
typedef int mask_t;

const llint oo = 0x3f3f3f3f;
const int maxn = 1001;
const int maxk = 1001;

const int NS = 11;
const mask_t slucajevi[NS] = {0x00, 0x11, 0x22, 0x44, 0x03,
                              0x06, 0x17, 0x47, 0x33, 0x55, 0x66};
const int slucajevi_cost[NS] = {0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2};

int N, K;
int map[3][maxn];
llint dp[2][8][maxk];

void load() {
  scanf("%d%d", &N, &K);
  for (int j = 0; j < N; ++j)
    for (int i = 0; i < 3; ++i)
      scanf("%d", &map[i][j]);
}

llint get(mask_t slucaj, int n) {
  llint ret = 0;
  for (int i = 0; i < 2; ++i, slucaj >>= 4) {
    if (n - i < 0 && slucaj) {
      return -oo;
    }
    for (int j = 0; j < 3; ++j) {
      ret += (slucaj & (1 << j)) ? map[j][n - i] : 0;
    }
  }
  return ret;
}

llint solve() {
  int read = 0;
  for (int k = 1; k <= K; ++k) {
    for (mask_t right = 0; right < 8; ++right) {
      dp[read][right][k] = -oo;
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int k = 0; k <= K; ++k) {
      // init
      for (mask_t right = 0; right < 8; ++right) {
        dp[!read][right][k] = -oo;
      }

      for (int ns = 0; ns < NS; ++ns) {
        int cost = slucajevi_cost[ns];
        mask_t slucaj = slucajevi[ns];
        mask_t left_busy = (slucaj >> 4) & 0xf;
        mask_t right_busy = slucaj & 0xf;
        if (k - cost < 0) continue;

        for (mask_t right = 0; right < 8; ++right) {
          if (right & right_busy) continue;
          llint &ref = dp[!read][right][k];
          ref = std::max(ref, dp[read][left_busy][k - cost] + get(slucaj, i));
        }
      }
    }
    read = !read;
  }
  return dp[read][0][K];
}

int main() {
  load();
  printf("%lld\n", solve());
  return 0;
}
