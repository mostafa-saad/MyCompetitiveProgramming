// Autor: Frane Kurtovic

#include <cstdio>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

#define x first
#define y second

typedef long long llint;
typedef pair<llint, llint> point;

point operator+(const point &l, const point &r) {
  return point(l.first+r.first, l.second+r.second);
}

point operator-(const point &l, const point &r) {
  return point(l.first-r.first, l.second-r.second);
}

llint ccw(const point &a, const point &b, const point &c) {
  point p1 = b-a;
  point p2 = c-a;
  return p1.first*p2.second - p1.second*p2.first;
}

bool out(const point &s, const point &e, const point &P) {
  return ccw(s, e, P) < 0;
}

bool out_or_on(const point &s, const point &e, const point &P) {
  return ccw(s, e, P) <= 0;
}

const int MAX_N = 100010;
point ships[MAX_N]; int n;
vector <point> poly; int m; // u ccw smjeru zadan

pair<int, int> find_tangent(const point &P) {
  point prev = poly[m-1];
  int left_t = -1, right_t = -1;
  for (int i = 0; i < m; i++) {
    point curr = poly[i];
    point next = poly[i+1];

    if (out(prev, curr, P) && !out(curr, next, P)) {
      // desna tangenta
      assert (right_t == -1);
      right_t = i;
    }

    if (!out(prev, curr, P) && out(curr, next, P)) {
      // lijeva tangenta
      assert (left_t == -1);
      left_t = i;
    }
    prev = curr;
  }
  assert (left_t != -1);
  assert (right_t != -1);
  return {left_t, right_t};
}

int prev(int x) {
  if (x == 0) return m-1;
  return x-1;
}

int next(int x) {
  return (x+1)%m;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lld %lld", &ships[i].x, &ships[i].y);
  }
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    point curr;
    scanf("%lld %lld", &curr.x, &curr.y);
    poly.push_back(curr);
  }
  poly.push_back(poly.front());

  point P = ships[0];
  auto tangents = find_tangent(P);

  int l_tangent = tangents.first, r_tangent = tangents.second;
  point l = P, r = P; // tocka iz koje ide najlijevija tangenta
  set <point> s;
  for (int i = 1; i < n; i++) {
    point T = ships[i];
    if (ccw(P, poly[tangents.first], ships[i]) >= 0 || ccw(P, poly[tangents.second], ships[i]) <= 0) {
      s.insert(ships[i]);
    } else if (ccw(P, poly[tangents.first], ships[i]) < 0 &&
        ccw(P, poly[tangents.second], ships[i]) > 0 &&
        ccw(poly[tangents.first], poly[tangents.second], ships[i]) <= 0) {
      // izmedju dvije tangente i otoka
      s.insert(ships[i]);
    }

    if (ccw(P, poly[tangents.first], T) >= 0) {
      // strana lijeve tangente
      while(true) {
        int next_e = prev(l_tangent);
        if (out_or_on(poly[next_e], poly[l_tangent], T)) {
          l_tangent = next_e;
          l = T;
        } else {
          break;
        }
      }
      if (ccw(l, poly[l_tangent], T) > 0) {
        l = T;
      }
    }

    if (ccw(P, poly[tangents.second], T) <= 0) {
      // strana desne tangente
      while(true) {
        int next_e = next(r_tangent);
        if (out_or_on(poly[r_tangent], poly[next_e], T)) {
          r_tangent = next_e;
          r = T;
        } else {
          break;
        }
      }
      if (ccw(r, poly[r_tangent], T) < 0) {
        r = T;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    point p = ships[i];
    if (ccw(l, poly[l_tangent], p) >= 0) {
      s.insert(p);
    } else if (ccw(l, P, p) >= 0 && ccw(P, poly[l_tangent], p) >= 0) {
      s.insert(p);
    }

    if (ccw(r, poly[r_tangent], p) <= 0) {
      s.insert(p);
    } else if (ccw(P, r, p) >= 0 && ccw(poly[r_tangent], P, p) >= 0) {
      s.insert(p);
    }
  }
  s.erase(P);
  printf("%lu\n", s.size());
  return 0;
}
