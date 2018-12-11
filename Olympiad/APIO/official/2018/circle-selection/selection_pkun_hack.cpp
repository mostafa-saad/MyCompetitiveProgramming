#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include <cassert>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;

struct point {
  int x, y;
};

ll operator*(const point& a, const point& b) {
  return a.x * 1LL * b.x + a.y * 1LL * b.y;
}

point operator-(const point& a, const point& b) {
  return {a.x - b.x, a.y - b.y};
}

struct circle {
  point c;
  int r, id;
};

bool intersect(const circle& a, const circle &b) {
  return (b.c - a.c) * (b.c - a.c) <= (a.r + b.r) * 1LL * (a.r + b.r);
}

struct cmp {
  point dir;
  bool operator()(const circle& a, const circle& b) const{
    ll p1 = dir * a.c;
    ll p2 = dir * b.c;
    if (p1 != p2) return p1 < p2;
    return a.id < b.id;
  }
};


int main() {
  int n;
  scanf("%d", &n);
  point dir{rand(), rand()};
  set<circle, cmp> s(cmp{dir});

  vector<circle> order;

  for (int i = 0; i < n; i++) {
    circle x;
    x.id = i;
    scanf("%d%d%d", &x.c.x, &x.c.y, &x.r);
    s.insert(x);
    order.push_back(x);
  }
  sort(order.begin(), order.end(), [](const circle& a, const circle& b) {
        if (a.r != b.r) return a.r > b.r;
        return a.id < b.id;
      });

  vector<int> ans(n, -1);

  for (circle c : order) {
    auto it = s.find(c);
    if (it == s.end()) {
      assert(ans[c.id] != -1);
      continue;
    }
    ll limit = (ll)(((ld)sqrt(dir * dir)) * c.r * 2);
    {
      auto cur = it;
      while (cur != s.begin()) {
        auto ncur = cur;
        ncur--;
        if (abs((ncur->c - c.c) * dir) > limit) break;
        if (intersect(*ncur, c)) {
          ans[ncur->id] = c.id;
          s.erase(ncur);
        } else {
          cur = ncur;
        }
      }
    }
    {
      auto cur = it;
      while (cur != s.end()) {
        if (abs((cur->c - c.c) * dir) > limit) break;
        auto ncur = cur;
        ncur++;
        if (intersect(*cur, c)) {
          ans[cur->id] = c.id;
          s.erase(cur);
        } 
        cur = ncur;
      }
    }
  }
  
  for (int i = 0; i < n; i++) {
    printf("%d%c", ans[i] + 1, " \n"[i == n - 1]);
  }

}


