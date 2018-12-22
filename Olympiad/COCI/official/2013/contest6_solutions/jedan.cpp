#include <cstdio>
#include <cstring>
#include <cstdlib>

const int maxn = 10010;
const int mod = 1000000007;

int n;
int h[maxn];
int dp[2][maxn];
int write = 0, size = 0;

void load() {
  scanf("%d", &n);
  for (int j = 0; j < n; ++j)
    scanf("%d", h + j);
}

void next() {
  write = !write;
  memset(dp[write], 0, sizeof dp[write]);
  ++size;
}

int solve() {
  next();
  // size = 1;
  dp[write][0] = 1;
  next();
  while (size < n) {
    int up = size;
    if (size > n/2) up = n - size + 1;

    for (int j = 0; j < up; ++j) {
      if (h[size-1] == -1 || j == h[size-1])
        dp[write][j] =
          ((long long) (j ? dp[!write][j-1] : 0) + dp[!write][j] + dp[!write][j+1])
          % mod;
    }
    next();
  }
  return (dp[!write][0] + dp[!write][1]) % mod;
}

int main() {
  load();
  if (n == 1 || h[0] > 0 || h[n-1] > 0) {
    printf("%d\n", h[0] < 1);
  } else {
    h[0] = h[n-1] = 0;
    printf("%d\n", solve());
  }
  return 0;
}
