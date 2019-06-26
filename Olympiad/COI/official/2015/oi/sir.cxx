// Autor: Goran Zuzic

#include <cassert>
#include <cstring>

#include <algorithm>
#include <iostream>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;

struct Pt { int x, y; };
struct Sol { 
  llint val;
  int a, b;
  friend bool operator < (Sol a, Sol b) { return a.val < b.val; };
};

const int MAXN = 6e5 + 123;

int ni, no, norig;
Pt orig_in[MAXN];
Pt in[MAXN], out[MAXN];

int ccw(Pt a, Pt b, Pt c) {
  llint ans = 0;
  ans += (llint)a.x * (b.y - c.y);
  ans += (llint)b.x * (c.y - a.y);
  ans += (llint)c.x * (a.y - b.y);
  return (ans > 0) - (ans < 0);
}

int edge_f(int io, int x) {
  if (x < 0) x += ni;
  if (x >= ni) x -= ni;
  int y = x+1; if (y == ni) y = 0;
  return ccw(out[io], in[x], in[y]);
}

llint dA(Pt a, Pt b) { return a.x*(llint)b.y - a.y*(llint)b.x; }

llint check_solution(int a, int b) {
  REP(i, norig) {
    assert(ccw(out[a], out[b], orig_in[i]) > 0);
  }
  llint ans = 0;
  FOR(i, a, b+1) {
    int j = i+1; if (i == b) j = a;
    ans += out[i].x*(llint)out[j].y - out[i].y*(llint)out[j].x;
  }
  return ans;
}

llint solve() {
  Sol ans = {0, -1, -1};

  REP(i, ni) in[i+ni] = in[i];
  REP(i, no) out[i+no] = out[i];
  
  static llint prefix[MAXN]; prefix[0] = 0;
  REP(i, 2*no) prefix[i+1] = prefix[i] + dA(out[i], out[i+1]);

  auto get_area = [&](int a, int b) {
    assert(a <= b); assert(b <= 2*no);
    return prefix[b] - prefix[a] + dA(out[b], out[a]);
  };
  auto get_tg = [&](int io) {
    int ii; for (ii = 0; ii < ni; ++ii) { // ubrzaj
      if (edge_f(io, ii) >= 0 && edge_f(io, ii-1) <= 0)
        break;
    } assert(ii != ni);
    return ii;
  };

  int io = 0, ii = get_tg(io);
  FOR(io, 0, no) {
    while (ii < 2*ni && edge_f(io, ii) < 0) ++ii;
    assert(ii < 2*ni);

    int lo = io, ho = lo + no - 1;
    while (lo < ho) {
      int mid = (lo + ho + 1) / 2;
      if (ccw(out[io], out[mid], in[ii]) > 0)
        lo = mid;
      else
        ho = mid - 1;
    }

    ans = max(ans, {get_area(io, lo), io, lo});
  }

  assert(check_solution(ans.a, ans.b) == ans.val);
  return ans.val;
}            

llint sq_dist(Pt a, Pt b) {
  llint dx = a.x-b.x, dy = a.y-b.y;
  return dx*dx + dy*dy;
}

int main(void) {
  scanf("%d", &no);
  REP(io, no) scanf("%d %d", &out[io].x, &out[io].y);

  scanf("%d", &ni); norig = ni;
  REP(ii, ni) scanf("%d %d", &in[ii].x, &in[ii].y);
  REP(ii, ni) orig_in[ii] = in[ii];

  // convex hull
  sort(in, in+ni, [&](Pt a, Pt b) { return a.x < b.x; });
  sort(in+1, in+ni, [&](Pt a, Pt b) { 
      llint s = ccw(in[0], a, b);
      if (s != 0) return s > 0;
      return sq_dist(in[0], a) < sq_dist(in[0], b);
    });
  int nhull = min(2, ni);
  for (int i = 2; i < ni; ++i) {
    while (nhull >= 2 && ccw(in[nhull-2], in[nhull-1], in[i]) <= 0) --nhull;
    in[nhull++] = in[i];
  }
  ni = nhull;

  llint ans = solve();
  printf("%lld\n", ans);
  return 0;
}   
