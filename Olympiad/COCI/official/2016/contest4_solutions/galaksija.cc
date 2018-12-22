#include <cstdio>
#include <cassert>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100005;
typedef pair <int, int> pii;
typedef long long llint;

llint curr;
llint ans[MAXN];

int n;
int a[MAXN], b[MAXN], z[MAXN];
int p[MAXN];

int path[MAXN];
int dad[MAXN];
int sz[MAXN];
map <int, vector<int>> M[MAXN];

void join (int a, int b, int c) {
  if (sz[dad[a]] < sz[dad[b]]) swap(a, b);

  int da = dad[a];
  int db = dad[b];

  for (auto it: M[db]) 
    for (auto x: it.second) 
      curr += M[da][path[a] ^ c ^ path[b] ^ path[x]].size();

  int old = path[b];
  for (auto it: M[db]) {
    for (auto x: it.second) {
      path[x] = path[x] ^ old ^ c ^ path[a];
      dad[x] = da;
      M[da][path[x]].push_back(x);
    }
  }

  sz[da] += sz[db];

  M[db].clear();
  sz[db] = 0;
}

int main (void) {
  scanf("%d", &n);
  for (int i = 0; i < n-1; ++i) {
    scanf("%d%d%d", &a[i], &b[i], &z[i]);
    --a[i]; --b[i];
  }

  for (int i = 0; i < n-1; ++i) scanf("%d", &p[i]);
  for (int i = 0; i < n-1; ++i) --p[i];

  for (int i = 0; i < n; ++i) {
    M[i][0].push_back(i);
    dad[i] = i;
    sz[i] = 1;
  }

  for (int i = n-2; i >= 0; --i) {
    join(a[p[i]], b[p[i]], z[p[i]]);
    ans[i] = curr;
  }

  ans[n-1] = 0;
  for (int i = 0; i < n; ++i)
    printf("%lld\n", ans[i]);

  return 0;
}
