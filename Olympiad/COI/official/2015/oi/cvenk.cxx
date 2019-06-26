// Autor: Gustav Matula

#include <cstdio>
#include <cassert>
#include <cstring>

#include <algorithm>
#include <iostream>

using namespace std;
typedef long long llint;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

const int MAXK = 100005;

void fix(int &x, int &y, int &k, int t) {
  if (x) t = min(t, x & -x);
  if (y) t = min(t, y & -y);
  if (!y || (x && (x & -x) < (y & -y)))
    x -= t;
  else
    y -= t;
  k -= t;
}

void kth_ancestor(int &x, int &y, int k) {
  while (k) fix(x, y, k, k);
}

llint dist(int x1, int y1, int x2, int y2) {
  llint ret = 0;
  llint delta = x1 + y1 - x2 - y2;
  if (delta < 0) kth_ancestor(x2, y2, -delta), ret -= delta;
  if (delta > 0) kth_ancestor(x1, y1, +delta), ret += delta;

  int d;
  while (x1 != x2 || y1 != y2) {
    int t = 1 << 30;
    for (int x : {x1, y1, x2, y2}) if (x) t = min(t, x & -x);
    fix(x1, y1, d, t);
    fix(x2, y2, d, t);
    ret += 2 * t;
  }

  return ret;
}

bool is_ancestor(int x1, int y1, int x2, int y2) {
  if (x1 + y1 > x2 + y2) return false;
  kth_ancestor(x2, y2, x2 + y2 - x1 - y1);
  return x2 == x1 && y2 == y1;
}

int K;
int x[MAXK], y[MAXK];

int count_descendants(int xx, int yy) {
  int ret = 0;
  REP(i, K) ret += is_ancestor(xx, yy, x[i], y[i]);
  return ret;
}

llint try_to_solve(int xx, int yy) {
  if (2 * count_descendants(xx, yy) < K) {
    int lg = 0; while (1LL << (lg + 1) <= xx + yy) ++lg;
    for (int i = lg; i >= 0; --i) {
      if ((1 << i) > xx + yy) continue;
      int xxx = xx, yyy = yy;
      kth_ancestor(xxx, yyy, 1 << i);
      if (2 * count_descendants(xxx, yyy) < K)
	xx = xxx, yy = yyy;
    }
    kth_ancestor(xx, yy, 1);
  }

  if (((xx + 1) & yy) == 0 && 2 * count_descendants(xx + 1, yy) >= K)
    return -1;
  if ((xx & (yy + 1)) == 0 && 2 * count_descendants(xx, yy + 1) >= K)
    return -1;
  
  llint ret = 0;
  REP(i, K) ret += dist(xx, yy, x[i], y[i]);
  
  return ret;
}

int main(void) 
{
  scanf("%d", &K);
  REP(i, K) scanf("%d%d", x+i, y+i);

  if (K == 2) {
    printf("%lld\n", dist(x[0], y[0], x[1], y[1]));
    exit(0);
  }

  for (;;) {
    int r = rand() % K;
    llint sol = try_to_solve(x[r], y[r]);
    if (sol != -1) {
      printf("%lld\n", sol);
      exit(0);
    }
  }

  return 0;
}
