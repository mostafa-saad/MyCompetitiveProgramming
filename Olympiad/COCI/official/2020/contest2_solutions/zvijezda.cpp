#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double lf;
typedef long double Lf;
typedef pair <int,int> pii;
typedef pair <ll, ll> pll;

#define TRACE(x) cerr << #x << "  " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define _ << " " <<

#define fi first
#define sec second
#define mp make_pair
#define pb push_back

const string ODG[] = {"NE", "DA"};

int n;
vector <pll> poly;

ll x, y;

lf ccw(pll a, pll b, pll c) {
  return (lf)a.fi * (b.sec - c.sec) +
         (lf)b.fi * (c.sec - a.sec) +
         (lf)c.fi * (a.sec - b.sec);
}

bool get(int i) {
  return ccw(poly[i], poly[(i+1)%n], {x, y}) >= 0;
}

int mjeri(int l, int r) {
  int lo = l, hi = r, mid;
  while (lo != hi) {
    mid = (lo + hi + 1) / 2;
    if (get(mid) == get(l)) lo = mid;
    else hi = mid - 1;
  }
  int ret = lo - l + 1;
  if (!get(l)) ret = n/2 - ret;
  return ret;
}

bool solve() {
  int a = get(0);
  int b = get(n / 2);
  if (a == b) return a;
  return mjeri(0, n / 2 - 1) + mjeri(n / 2, n - 1) > n / 2;
}

int main() {
  int t;
  scanf("%d %d",&t,&n);
  REP(i, n) {
    scanf("%lld %lld",&x,&y);
    poly.pb({x, y});
  }
  int q;
  ll da = 0;
  scanf("%d",&q);
  REP(i, q) {
    scanf("%lld %lld",&x,&y);
    x ^= da * da * da * t;
    y ^= da * da * da * t;
    int ans = solve();
    da += ans;
    cout << ODG[ans] << '\n';
  }
  return 0;
}

