#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cassert>

#include <map>

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR (i, 0, (n))
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

using namespace std;

typedef long long llint;

const int MAXN = 1e6;

int n;
int a[MAXN], d[MAXN];
map<int, int> M;

inline int sgn(int x) {
  return x != 0 ? x / abs(x) : 0;
}

int main(void) {
  scanf("%d", &n);

  REP (i, n) scanf("%d", a+i);
  FOR (i, 1, n) {
    d[i] = sgn(a[i]-a[i-1]);
    d[i] += d[i-1];
  }

  int cnt = 0;
  REP (i, n) {
    if (d[i] == 0) {
      cnt += a[i] == a[0];
      continue;
    }
    if ((a[i]-a[0])%d[i] != 0) continue;
    ++M[(a[i]-a[0])/d[i]];
  }

  int k = 0, ans = 0;
  for (auto p: M)
    if (p.first >= 0 && p.second >= ans) {
      k = p.first;
      ans = p.second;
    }

  printf("%d\n%d\n", ans+cnt, k);

	return 0;
}
