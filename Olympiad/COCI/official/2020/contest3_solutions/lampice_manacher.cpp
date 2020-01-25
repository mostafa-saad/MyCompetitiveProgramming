#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

using namespace std;

const int MAXN = 5e4 + 10;

char S[MAXN], T[2 * MAXN];

int n, t_len;
int P[2*MAXN];

inline void preprocess() {
  T[t_len++] = '!';
  for (int i = 0; i < n; ++i) {
    T[t_len++] = '#';
    T[t_len++] = S[i];
  }
  T[t_len++] = '#';
  T[t_len++] = '@';
}

int main(void) {
  scanf("%d", &n);
  scanf("%s", S);

  preprocess();

  int mid = 0, hi = 0, sol = 0;
  for (int i = 1; i < t_len - 1; ++i) {
      int _i = mid - (i - mid);
      if (hi > i)
          P[i] = min(hi - i, P[_i]);

      while (T[i + P[i] + 1] == T[i - P[i] - 1])
          ++P[i];

      if (i + P[i] > hi) {
          mid = i;
          hi = i + P[i];
      }
      sol = max(sol, P[i]);
  }

  printf("%d\n", sol);
  return 0;
}

