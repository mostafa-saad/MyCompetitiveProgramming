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

int main() {
  int n;
  scanf("%d", &n);
  point dir{rand(), rand()};

  vector<circle> order;
  vector<circle> lst;

  for (int i = 0; i < n; i++) {
    circle x;
    x.id = i;
    scanf("%d%d%d", &x.c.x, &x.c.y, &x.r);
    order.push_back(x);
    lst.push_back(x);
  }
  sort(order.begin(), order.end(), [](const circle& a, const circle& b) {
        if (a.r != b.r) return a.r > b.r;
        return a.id < b.id;
      });
  sort(lst.begin(), lst.end(), [&dir](const circle& a, const circle& b) {
        ll p1 = dir * a.c;
        ll p2 = dir * b.c;
        if (p1 != p2) return p1 < p2;
        return a.id < b.id;
      });
  vector<int> rlst(n);
  vector<int> next(n);
  vector<int> prev(n);
  for (int i = 0; i < n; i++) {
    rlst[lst[i].id] = i;
    next[i] = i + 1;
    prev[i] = i - 1;
  }

  auto remove = [&](int id) {
    if (next[id] != n)  prev[next[id]] = prev[id];
    if (prev[id] != -1) next[prev[id]] = next[id];
  };

  vector<int> ans(n, -1);

  ll ops = 0;

  for (circle c : order) {
    if (ans[c.id] != -1) {
      continue;
    }
    ll limit = (ll)(((ld)sqrt(dir * dir)) * c.r * 2);
    {
      int cur = prev[rlst[c.id]];
      while (cur != -1) {
        if (abs((lst[cur].c - c.c) * dir) > limit) break;
        ops++;
        if (intersect(lst[cur], c)) {
          ans[lst[cur].id] = c.id;
          remove(cur);
        }
        cur = prev[cur];
      }
    }
    {
      int cur = rlst[c.id];
      while (cur != n) {
        if (abs((lst[cur].c - c.c) * dir) > limit) break;
        ops++;
        if (intersect(lst[cur], c)) {
          ans[lst[cur].id] = c.id;
          remove(cur);
        }
        cur = next[cur];
      }
    }
  }

  fprintf(stderr, "ops = %lld\n", ops);
  
  for (int i = 0; i < n; i++) {
    printf("%d%c", ans[i] + 1, " \n"[i == n - 1]);
  }

}


