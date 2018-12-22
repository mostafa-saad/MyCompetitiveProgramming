#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

#define LOG(x) cerr << #x << " = " << (x) << "\n"

typedef long long llint;
typedef pair<int,int> pii;
const int MAXN = 1010;

int n, m;
int a[MAXN][MAXN], b[MAXN][MAXN];
int cnt[MAXN], done[MAXN];
pii where_a[MAXN*MAXN], where_b[MAXN*MAXN];
vector<pii> same[MAXN];
vector<int> edges[MAXN];

void load(int a[MAXN][MAXN]) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      scanf("%d", &a[i][j]);
}

llint solve_same_shelf(vector<pii> &a) {
  llint ret = 0;
  vector<int> lis;

  sort(a.begin(), a.end());
  for (pii x : a) {
    auto it = lower_bound(lis.begin(), lis.end(), x.second);
    if (it == lis.end()) {
      lis.push_back(x.second);
    } else {
      *it = x.second;
    }
  }

  if (lis.size() == a.size()) return 0;
  if ((int)a.size() == m) ret = 1;
  ret += (int)a.size() - (int)lis.size();
  return ret;
}

int dfs(int x) {
  int ret = (cnt[x] == m);
  done[x] = 1;

  for (int y : edges[x]) {
    if (done[y]) continue;
    ret &= dfs(y);
  }
  return ret;
}

llint solve() {
  int empty_cell = 0;
  int everything_ok = 1;

  memset(where_a, -1, sizeof where_a);
  memset(where_b, -1, sizeof where_b);

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      empty_cell |= !a[i][j];
      everything_ok &= (a[i][j] == b[i][j]);
      where_a[a[i][j]] = { i, j };
      where_b[b[i][j]] = { i, j };
      cnt[i] += (a[i][j] > 0);
    }

  if (everything_ok) return 0;
  if (empty_cell == 0) return -1;

  llint ans = 0;

  for (int i = 1; i < MAXN*MAXN; ++i) {
    if (where_a[i].first == -1) continue;
    if (where_a[i].first == where_b[i].first) {
      same[where_a[i].first].push_back({where_a[i].second, where_b[i].second});
    } else {
      edges[where_a[i].first].push_back(where_b[i].first);
      edges[where_b[i].first].push_back(where_a[i].first);
      ++ans;
    }
  }

  for (int i = 0; i < n; ++i)
    ans += solve_same_shelf(same[i]);

  for (int i = 0; i < n; ++i)
    if (done[i] == 0 && edges[i].size() != 0)
      ans += dfs(i);

  return ans;
}

int main() {
  scanf("%d%d", &n, &m);
  load(a); load(b);
  printf("%lld\n", solve());
  return 0;
}
