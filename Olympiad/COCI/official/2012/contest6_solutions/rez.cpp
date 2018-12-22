#include <cstdio>

const int maxd = 5000;

int N, K;

#define BP(x) (1 + (x) * ((x)+1) / 2)
#define mid ((lo + hi)>>1)

int solve(int target) {
  int lo = 0, hi = 1500;
  while (hi - lo)
    (BP(mid) >= target) ?
      (hi = mid) :
      (lo = mid + 1);
  return lo;
}

int main() {
  scanf("%d", &K);
  N = solve(K);
  printf("%d\n", N);
  for (int j = 0; j < N; ++j)
    printf("%d %d %d %d\n", maxd - j - 1, -5000, -5000, -maxd + j + 2);
  return 0;
}
