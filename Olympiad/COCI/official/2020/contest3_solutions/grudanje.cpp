#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 1e5 + 10;

char s[MAXN];

int n, q;
int l[MAXN], r[MAXN], p[MAXN], pp[MAXN], pref[26][MAXN];

bool check(int x) {
  for (int i = 0; i < 26; ++i) pref[i][0] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 26; ++j)
      pref[j][i + 1] = pref[j][i];
    if (pp[i] > x)
      pref[s[i] - 'a'][i + 1] += 1;
  }
  bool ok = true;
  for (int i = 0; i < q && ok; ++i)
    for (int j = 0; j < 26 && ok; ++j)
      ok &= (pref[j][r[i]] - pref[j][l[i] - 1]) <= 1;
  return ok;
}

int main(void) {
  scanf("%s", s);
  n = strlen(s);

  scanf("%d", &q);
  for (int i = 0; i < q; ++i)
    scanf("%d%d", &l[i], &r[i]);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &p[i]); --p[i];
    pp[p[i]] = i + 1;
  }

  int lo = 0, hi = n;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (check(mid)) hi = mid; else lo = mid + 1;
  }

  printf("%d\n", lo);
  return 0;
}
