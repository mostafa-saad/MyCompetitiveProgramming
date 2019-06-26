// O(RS)
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;

const int MAXN = 2020;

vector<pair<int, int>> v[MAXN];

bool bio[MAXN][MAXN];
char a[MAXN][MAXN];

int opt[MAXN][MAXN];
int f[MAXN][MAXN];
int g[MAXN][MAXN];
int cnt[MAXN];
int n, m;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void dfs(int i, int j, int &l, int &r, int &s) {
  if (bio[i][j]) return;
  bio[i][j] = true;
  
  l = min(l, j);
  r = max(r, j);
  s += a[i][j] - '0';

  REP(k, 4) {
    int ni = i + dx[k];
    int nj = j + dy[k];
    if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
    if (a[ni][nj] != '.') dfs(ni, nj, l, r, s);
  }
}

int main(void) {
  int t = 1;
  while (t--) {
    scanf("%d %d", &n, &m);
    REP(i, n) scanf("%s", a[i]);

    REP(i, n) REP(j, m) bio[i][j] = false;
    REP(j, m) v[j].clear();

    REP(i, n) REP(j, m)
      if (!bio[i][j] && a[i][j] != '.') {
        int l = j, r = j, s = 0;
        dfs(i, j, l, r, s);
        v[l].push_back({r, s});
      }
    
    REP(j, m) cnt[j] = 0;
    for (int j = m-1; j >= 0; --j) {
      for (auto &p: v[j])
        FOR(i, j, p.first+1) cnt[i] += p.second;
      FOR(i, j, m) g[j][i] = cnt[i];
    }

    REP(i, m+1) {
      f[0][i] = 0;
      opt[0][i] = m-1;
    }

    for (int k = 1; k <= m; ++k) {
      int best = 0;
      for (int i = 0; i < m; ++i) {
        int lo = i == 0 ? 0 : max(i, opt[k][i-1]);
        int hi = opt[k-1][i];

        f[k][i] = -1;
        for (int j = lo; j <= hi; ++j) {
          int nf = f[k-1][j+1] + g[i][j];
          if (nf > f[k][i]) f[k][i] = nf, opt[k][i] = j;
        }

        best = max(best, f[k][i]);
      }
      printf("%d\n", best);
    }
  }
  return 0;
}
