#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 3e5 + 10;
const int MAXH = 1e6 + 10;

int n, k, gtk;
int h[MAXN], cnt[MAXH];

int main(void) {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
    cnt[h[i]]++;
    gtk += h[i] > k;
  }

  for (int i = 0; i < n; ++i) {
    int ret = 0;
    if (h[i] < k) {
      printf("0 ");
      continue;
    }
    if (h[i] == k) {
      printf("%d ", gtk);
      continue;
    }
    for (int j = 1; j * j <= h[i] - k; ++j) {
      if ((h[i] - k) % j != 0) continue;
      if (h[i] % j == k) ret += cnt[j];
      if (j * j != h[i] - k && h[i] % ((h[i] - k) / j) == k)
        ret += cnt[(h[i] - k) / j];
    }
    if (k == 0) --ret;
    printf("%d ", ret);
  }

  printf("\n");

  return 0;
}
