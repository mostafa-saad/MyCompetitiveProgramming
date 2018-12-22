#include <algorithm>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define REP(i, n) FOR(i, 0, n)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define TRACE(x) cout << #x << " = " << (x) << endl

typedef long long llint;

const int inf = 1e8 + 123;
const int mod = 1e9;

int add(int a, int b) {
  return a+b >= mod ? a+b-mod : a+b;
}

int sub(int a, int b) {
  return a >= b ? a-b : a-b+mod;
}

int mul(int a, int b) {
  return (llint(a)*b)%mod;
}

struct Node {
  int lo, hi;

  int sm, sM, sL;
  int smM, smL, sML;
  int smML;

  int set_m, set_M, add_L;

  Node() { clear(); }
  void clear() {
    sm = sM = sL = 0;
    smM = smL = sML = 0;
    smML = 0;
    set_m = inf; set_M = inf; add_L = 0;
  }

  void go_set_m(llint m) {
    sm = mul(m, sub(hi, lo));
    smM = mul(m, sM);
    smL = mul(m, sL);
    smML = mul(m, sML);
    set_m = m;
  }

  void go_set_M(llint M) {
    sM = mul(M, sub(hi, lo));
    smM = mul(M, sm);
    sML = mul(M, sL);
    smML = mul(M, smL);
    set_M = M;
  }

  void go_add_L(llint L) {
    sL = add(sL, mul(L, sub(hi, lo)));
    smL = add(smL, mul(L, sm));
    sML = add(sML, mul(L, sM));
    smML = add(smML, mul(L, smM));
    add_L = add(add_L, L);
  }

  friend void prop_down(Node& p, Node& a, Node& b) {
    if (p.set_m != inf) {
      a.go_set_m(p.set_m);
      b.go_set_m(p.set_m);
      p.set_m = inf;
    }
    if (p.set_M != inf) {
      a.go_set_M(p.set_M);
      b.go_set_M(p.set_M);
      p.set_M = inf;
    }
    if (p.add_L != 0) {
      a.go_add_L(p.add_L);
      b.go_add_L(p.add_L);
      p.add_L = 0;
    }
  }

  friend void upd(Node&p, const Node& a, const Node& b) {
    p.sm = add(a.sm, b.sm);
    p.sM = add(a.sM, b.sM);
    p.sL = add(a.sL, b.sL);

    p.smM = add(a.smM, b.smM);
    p.smL = add(a.smL, b.smL);
    p.sML = add(a.sML, b.sML);

    p.smML = add(a.smML, b.smML);
  }
};

struct Tour {
  int n, offset;
  vector<Node> data;

  Tour(int n) : n(n) {
    offset = 1; for (; offset < n; offset *= 2);
    data.resize(2*offset);
    init(1, 0, offset);
  }
  void init(int x, int lo, int hi) {
    data[x].lo = lo;
    data[x].hi = hi;
    if (lo+1 == hi) {
      return;
    }
    int mid = (lo + hi) / 2;
    init(2*x, lo, mid);
    init(2*x+1, mid, hi);
  }

  int LO, HI, VAL;
  int RET;

  template<typename LF>
  void process(int x, int lo, int hi, const LF& f) {
    if (hi <= LO || HI <= lo) return;
    if (LO <= lo && hi <= HI) {
      f(data[x]);
      return;
    }
    prop_down(data[x], data[2*x], data[2*x+1]);
    int mid = (lo + hi) / 2;
    process(2*x, lo, mid, f);
    process(2*x+1, mid, hi, f);
    upd(data[x], data[2*x], data[2*x+1]);
  }

  void set_m(int lo, int hi, int val) { // [lo, hi>
    LO = lo; HI = hi; VAL = val;
    process(1, 0, offset, [this](Node& x) {
        x.go_set_m(VAL);
      });
  }

  void set_M(int lo, int hi, int val) { // [lo, hi>
    LO = lo; HI = hi; VAL = val;
    process(1, 0, offset, [this](Node& x) {
        x.go_set_M(VAL);
      });
  }

  void add_L(int lo, int hi, int val) { // [lo, hi>
    LO = lo; HI = hi; VAL = val;
    process(1, 0, offset, [this](Node& x) {
        x.go_add_L(VAL);
      });
  }

  int query(int lo, int hi) {
    LO = lo; HI = hi; RET = 0;
    process(1, 0, offset, [this](Node& x) {
        RET = add(RET, x.smML);
      });
    return RET;
  }
};

int main(void)
{
  int n; scanf("%d", &n);
  assert(1 <= n && n <= 500000);
  Tour T(n);

  struct S { int val, idx; };
  vector<S> inc = { {-inf, -1} }, dec = { {+inf, -1} };  

  int ans = 0;
  REP(i, n) {
    int val; scanf("%d", &val);
    assert(1 <= val && val <= 100000000);
    while (dec.back().val < val) dec.pop_back();
    while (inc.back().val > val) inc.pop_back();
    T.set_M(dec.back().idx+1, i+1, val);
    T.set_m(inc.back().idx+1, i+1, val);
    T.add_L(0, i+1, +1);
    dec.push_back({val, i});
    inc.push_back({val, i});
    ans = add(ans, T.query(0, i+1));
  }

  printf("%d\n", ans);
  return 0;
}
