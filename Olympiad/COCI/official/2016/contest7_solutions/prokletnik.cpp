#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <stack>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR (i, 0,  n)

using namespace std;

typedef long long llint;
typedef pair<int,int> pii;
const int MAXN = 1001000;
const int offset = 1 << 20;

struct tournament {
  int alive[2 * offset];
  int prop_max[2 * offset];
  int real_max[2 * offset];

  void clear() {
    fill(alive, alive + 2 * offset, -1);
    fill(prop_max, prop_max + 2 * offset, 0);
    fill(real_max, real_max + 2 * offset, 0);
  }

  void set_alive(int x, int lo, int hi, int k, int val) {
    if (k < lo || k >= hi) return;
    if (lo + 1 == hi) {
      alive[x] = val;
      return;
    }
    propagate(x);
    int mid = (lo + hi) / 2;
    set_alive(2 * x, lo, mid, k, val);
    set_alive(2 * x + 1, mid, hi, k, val);
    update(x);
  }

  void set_max(int x, int lo, int hi, int from, int to, int val) {
    if (lo >= to || hi <= from) return;
    if (lo >= from && hi <= to) {
      prop_max[x] = val;
      real_max[x] = max(real_max[x], alive[x] == -1 ? 0 : val - alive[x]);
      return;
    }
    propagate(x);
    int mid = (lo + hi) / 2;
    set_max(2 * x, lo, mid, from, to, val);
    set_max(2 * x + 1, mid, hi, from, to, val);
    update(x);
  }

  int get_max(int x, int lo, int hi, int from, int to) {
    if (lo >= to || hi <= from) return 0;
    if (lo >= from && hi <= to) return real_max[x];
    propagate(x);
    int mid = (lo + hi) / 2;
    return max(get_max(2 * x, lo, mid, from, to),
        get_max(2 * x + 1, mid, hi, from, to));
  }

  void propagate(int x) {
    prop_max[2 * x] = max(prop_max[2 * x], prop_max[x]);
    prop_max[2 * x + 1] = max(prop_max[2 * x + 1], prop_max[x]);
    real_max[2 * x] = max(real_max[2 * x],
        alive[2 * x] == -1 ? 0 : prop_max[2 * x] - alive[2 * x]);
    real_max[2 * x + 1] = max(real_max[2 * x + 1],
        alive[2 * x + 1] == -1 ? 0 : prop_max[2 * x + 1] - alive[2 * x + 1]);
    prop_max[x] = 0;
  }

  void update(int x) {
    alive[x] = alive[2 * x] == -1 ? alive[2 * x + 1] : alive[2 * x];
    real_max[x] = max(real_max[2 * x], real_max[2 * x + 1]);
  }
};

int n, q;
int a[MAXN];
pii b[MAXN];
vector<int> queries[MAXN];
int sol[MAXN];

stack<int> maxs;
stack<int> mins;
tournament tour;

void clear() {
  while (maxs.size()) {
    maxs.pop();
  }
  while (mins.size()) {
    mins.pop();
  }
  tour.clear();
}

void insert(int x) {
  while (maxs.size() && a[x] >= a[maxs.top()]) {
    maxs.pop();
  }
  int from = maxs.size() ? maxs.top() + 1 : 0;
  while (mins.size() && a[x] < a[mins.top()]) {
    tour.set_alive(1, 0, offset, mins.top(), -1);
    mins.pop();
  }

  maxs.push(x);
  mins.push(x);
  tour.set_alive(1, 0, offset, x, x);
  tour.set_max(1, 0, offset, from, x + 1, x + 1);
}

void solve() {
  clear();
  for (int i = 0; i < n; ++i) {
    insert(i);
    for (int j : queries[i]) {
      sol[j] = max(sol[j], tour.get_max(
            1, 0, offset, b[j].first, b[j].second + 1));
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
  }
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    scanf("%d%d", &b[i].first, &b[i].second);
    --b[i].first;
    --b[i].second;
    queries[b[i].second].push_back(i);
  }

  solve();
  for (int i = 0; i < n; ++i) {
    a[i] = -a[i];
  }
  solve();

  for (int i = 0; i < q; ++i) {
    printf("%d\n", sol[i]);
  }
  return 0;
}
