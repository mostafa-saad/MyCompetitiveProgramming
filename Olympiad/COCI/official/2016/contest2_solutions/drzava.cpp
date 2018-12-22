#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#include <cmath>

using namespace std;
using llint = long long;

#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

const int MAXN = 50010;
const int MAXK = 35;

int n, k, cookie;
int bio[MAXN];
vector<int> e[MAXN], val;

struct point {
  int x, y, cnt;

  point (int _x = 0, int _y = 0, int _cnt = 0) {
    x = _x;
    y = _y;
    cnt = _cnt;
  }
  
  friend bool operator < (const point& a, const point& b) {
    return a.x < b.x;
  }
} p[MAXN];

struct cmpf {
  bool operator()(const int& i, const int& j) {
    if (p[i].y != p[j].y) return p[i].y < p[j].y;
    return i > j;
  }
};

set<int, cmpf> s;
bool ok[MAXN][MAXK];

inline int modulo (int x) { return x >= k ? x - k : x; }
inline llint sqr(int x) { return (llint)x * x; }
inline llint dist(int i, int j) {
  return sqr(p[i].x - p[j].x) + sqr(p[i].y - p[j].y);
}

bool findSubset(const vector<int>& vec) {
  int m = vec.size();
  if (m > k) return true;

  for (int mod = 0; mod < k; ++mod)
    ok[m][mod] = !mod;

  for (int i = m - 1; i >= 0; --i) {
    for (int mod = 0; mod < k; ++mod) {
      ok[i][mod] = ok[i + 1][mod];
      if (ok[i + 1][modulo(mod + vec[i])])
	ok[i][mod] = true;
    }
    if (ok[i + 1][vec[i]])
      return true;
  }

  return false;
}

void dfs(int x) {
  bio[x] = cookie;
  val.push_back(p[x].cnt);

  for (int y : e[x])
    if (bio[y] != cookie)
      dfs(y);
}

bool check(llint d) {
  int dsqrt = (double)(sqrt(d) + 1);
  for (int i = 0; i < n; ++i) {
    e[i].clear();
  }
  s.clear();
  
  int j = 0;
  for (int i = 0; i < n; ++i) {
    for (; p[i].x - p[j].x > d; ++j)
      s.erase(j);
    
    if (!s.empty()) {
      int inbox = 0;
      p[n] = point(p[i].x, p[i].y - dsqrt, 0);
      for (auto it = s.lower_bound(n); it != s.end(); ++it) {
	int idx = *it;
      
	if (p[idx].y > p[i].y + dsqrt) break;
	++inbox;
	if (inbox >= 8 * k) {
	  return true;
	}
	if (dist(i, idx) <= d) {
	  e[i].push_back(idx);
	  e[idx].push_back(i);
	}
      }
    }
    
    s.insert(i);
  }

  ++cookie;
  for (int i = 0; i < n; ++i)
    if (bio[i] != cookie) {
      val.clear();
      dfs(i);
      if (findSubset(val)) {
	return true;
      }
    }
  return false;
}

void init(void) {
  scanf("%d %d",&n,&k);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d %d",&p[i].x,&p[i].y,&p[i].cnt);
    p[i].cnt %= k;
  }
  sort(p, p + n);
}

void solve(void) {
  llint lo = 0, hi = 1e18, res = -1;
  while (lo <= hi) {
    llint mid = (lo + hi) / 2;
    if (check(mid)) {
      res = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  if (res == -1)
    printf("No solution!\n");
  else
    printf("%.3lf\n",sqrt(res));
}

int main(void) {
  init();
  solve();
  return 0;
}
