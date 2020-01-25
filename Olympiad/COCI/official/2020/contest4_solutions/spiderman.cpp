#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 3e5 + 10;
const int MAXH = 1e6 + 10;

int n, k;
int h[MAXN], sol[MAXH];

map<int, int> cnt;

int main(void) {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
    cnt[h[i]]++;
  }

  for (const auto &p : cnt) {
    if (p.first <= k) continue;
    for (int j = k; j < MAXH; j += p.first)
      sol[j] += p.second;
    if (k == 0) sol[p.first]--;
  }

  for (int i = 0; i < n; ++i)
    printf("%d ", sol[h[i]]);
  printf("\n");
  return 0;
}
