#include <cstdio>
#include <iostream>
#include <cstring>
#include <set>
#include <cassert>
#include <map>
#include <algorithm>

#define val first
#define pos second

using namespace std;
using pii = pair<int, int>;
using llint = long long;

const int MAXN = 100010;
const int MAXLG = 20;
enum {LT, EQ, GT};

struct Tournament {
  map<int, int> a[4 * MAXN];
  int off, from, to, target;

  void init(int n) {
    for (off = 1; off <= n; off *= 2);
  }

  void update(int i, int val) {
    int pos = i;
    i += off;
    a[i][val] = pos;
    for (i /= 2; i > 0; i /= 2) {
      a[i][val] = pos;
    }
  }

  pii query(int i, int lo, int hi) {
    if (lo >= to || from >= hi) return {-1, -1};
    if (lo >= from && hi <= to) {
      auto it = a[i].lower_bound(target);
      if (it == a[i].end()) return {-1, -1};
      return {it->first, it->second};
    }
    pii a = query(2 * i, lo, (lo + hi) / 2);
    pii b = query(2 * i + 1, (lo + hi) / 2, hi);
    if (a.val == -1) return b;
    if (b.val == -1) return a;
    return a < b ? a : b;
  }

  pii Query(int lo, int hi, int _target) {
    from = lo;
    to = hi + 1;
    target = _target;
    return query(1, 0, off);
  }
} t;

int a[MAXN], n, k, m, base, mod;
int dad[2 * MAXN][MAXLG], rnk[2 * MAXN], h[2 * MAXN];
int len[2 * MAXN], last[2 * MAXN], curr_child[2 * MAXN];

int cmp_nodes(int x, int y) {
  if (rnk[dad[x][0]] != rnk[dad[y][0]])
    return rnk[dad[x][0]] < rnk[dad[y][0]] ? LT : GT;
  if (a[last[x]] != a[last[y]])
    return a[last[x]] < a[last[y]] ? LT : GT;
  return EQ;
}

int cmp_vals(string a, string b) {
  if (a < b) return LT;
  if (a > b) return GT;
  return EQ;
}

int cmp_strings(int x, int y) {  
  if (len[x] == len[y])
    return cmp_nodes(x, y);
  
  if (len[x] < len[y]) {
    for (int lg = MAXLG - 1; lg >= 0; --lg)
      if (len[y] - (1 << lg) >= len[x])
  	y = dad[y][lg];
    return cmp_nodes(x, y) == GT ? GT : LT;
  }

  for (int lg = MAXLG - 1; lg >= 0; --lg)
    if (len[x] - (1 << lg) >= len[y])
      x = dad[x][lg];    
  return cmp_nodes(x, y) == LT ? LT : GT;
}

struct cmpf {
  bool operator()(const int& x, const int& y) {
    int t = cmp_strings(x, y);
    if (t == EQ) return x < y;
    return t == LT;
  }
};

int nextChild(int x, int pos) {
  if (pos + 1 < n) {
    auto q = t.Query(pos + 1, n - 1, a[pos]);
    if (q.val != -1 && q.val == a[pos]) return q.pos;
  }
  return t.Query(last[x] + 1, n - 1, a[pos] + 1).pos;
}

set<int, cmpf> s;

void genNextChild(int x) {
  int new_pos = nextChild(x, curr_child[x]);
  if (new_pos == -1)
    return;
  
  curr_child[x] = new_pos;
  
  last[m] = new_pos;
  dad[m][0] = x;
  curr_child[m] = n;
  len[m] = len[x] + 1;
  s.insert(m);
  h[m] = ((llint)h[x] * base + a[new_pos]) % mod;
  ++m;
}

void init(void) {
  scanf("%d %d %d %d",&n,&k,&base,&mod);
  for (int i = 0; i < n; ++i)
    scanf("%d",&a[i]);
  a[n] = -1;
  t.init(n);
  for (int i = n - 1; i >= 0; --i)
    t.update(i, a[i]);
}

void solve(void) {
  s.insert(0);
  last[0] = -1;
  for (int lg = MAXLG - 1; lg >= 0; --lg)
    dad[0][lg] = -1;
  curr_child[0] = n;
  m = 1;
  int prev = -1;
  
  for (int i = 0; i <= k; ++i) {
    assert(!s.empty());
    int x = *s.begin();
    s.erase(s.begin());
    if (prev != -1) {
      if (cmp_strings(x, prev) == EQ)
	rnk[x] = rnk[prev];
      else
	rnk[x] = rnk[prev] + 1;
    }    
    if (i > 0)
      printf("%d %d\n",h[x],len[x]);
    if (dad[x][0] != -1)
      genNextChild(dad[x][0]);
    genNextChild(x);

    prev = x;
  }
}

int main(void) {
  init();
  solve();
  return 0;
}
