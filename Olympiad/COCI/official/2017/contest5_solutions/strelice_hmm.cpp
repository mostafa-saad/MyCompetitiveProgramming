#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR (i, 0, n)
#define _ << " _ " <<
#define TRACE(x) cerr << #x << " = " << x << endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
//#define debug
//#define TRACE(x)

using namespace std;
using pii = pair<int, int>;

typedef long long llint;

const int MAXN = 1010;
const int MAXS = MAXN * MAXN;
const int MAXK = 55;

bool bio[MAXS];
int F[MAXS][MAXK], G[MAXN][MAXK];
int recf[MAXS][MAXK], recg[MAXN][MAXK];
vector<int> e[MAXS], id[MAXS];
int edg, n, m, K;
char a[MAXN][MAXN];
vector<pii> fr, ans;

int f(int x, int i, int k) {
  if (i == 0 && k == 1) return 1;
  if (i == (int)e[x].size()) return (k == 0) ? 1 : 0;
  if (F[id[x][i]][k] != -1) return F[id[x][i]][k];

  int ret = 0;
  for (int l = 1; l <= k && !ret; ++l)
    if (f(x, i + 1, k - l) && f(e[x][i], 0, l)) {
      recf[id[x][i]][k] = l;
      ret = 1;
    }

  return F[id[x][i]][k] = ret;
}

void reconf(int x, int i, int k) {
  if (i == 0 && k == 1) {
    ans.push_back({x / m, x % m});
    return;
  }
  if (i == (int)e[x].size()) return;
  int l = recf[id[x][i]][k];
  reconf(x, i + 1, k - l);
  reconf(e[x][i], 0, l);
}

int g(int i, int k) {
  if (i == n) return (k <= (int)fr.size()) ? 1 : 0;
  if (e[i * m + m - 1].empty()) return g(i + 1, k);
  if (G[i][k] != -1) return G[i][k];

  int ret = 0;
  for (int l = 1; l <= k && !ret; ++l)
    if (f(i * m + m - 1, 0, l) && g(i + 1, k - l)) {
      recg[i][k] = l;
      ret = 1;
    }
  
  return G[i][k] = ret;
}

void recong(int i, int k) {
  if (i == n) {
    for (int j = 0; j < k; ++j)
      ans.push_back(fr[j]);
  } else if (e[i * m + m - 1].empty()) {
    recong(i + 1, k);
  } else {
    int l = recg[i][k];
    reconf(i * m + m - 1, 0, l);
    recong(i + 1, k - l);
  }
}

void dfs(int x) {
  bio[x] = true;
  for (int y : e[x])
    dfs(y);
}

int main(void) {
  memset(F, -1, sizeof(F));
  memset(G, -1, sizeof(G));
  scanf("%d %d %d",&n,&m,&K);
  for (int i = 0; i < n; ++i)
    scanf("%s",a[i]);

  for (int i = 0; i < n; ++i) {
    int r = i, c = 0;
    while (true) {
      if (bio[r * m + c]) break;
      bio[r * m + c] = true;

      int nr = r, nc = c;
      if (a[r][c] == 'L') --nc;
      if (a[r][c] == 'R') ++nc;
      if (a[r][c] == 'U') --nr;
      if (a[r][c] == 'D') ++nr;

      id[nr * m + nc].push_back(edg++);
      e[nr * m + nc].push_back(r * m + c);

      r = nr;
      c = nc;
      if (c == m - 1) break;
    }
  }

  memset(bio, false, sizeof(bio));
  for (int i = 0; i < n; ++i)
    dfs(i * m + m - 1);
  
  for (int r = 0; r < n; ++r)
    for (int c = 0; c < m; ++c)
      if (!bio[r * m + c])
	fr.push_back({r, c});

  if (g(0, K)) {
    recong(0, K);
    for (auto x : ans)
      printf("%d %d\n",x.first+1,x.second+1);
  } else 
    printf("-1\n");
  
  return 0;
}
