#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR (i, 0, (n))
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;
typedef pair<llint, int> pli;

const int INF = 1e9;
const int MAXNODES = 262144;
const int offset = 131072;

inline bool subset(llint mask1, llint mask2) {
  return (mask1 & mask2) == mask1;
}

int n, k, q;

class tournament {
 private:
  struct node {
    int len;
    pli pref[50];
    pli suff[50];
    int ans;

    node() { ans = INF; len = 0; }
    node(int t, int v) {
      len = 1;
      pref[0] = suff[0] = pli(1LL<<v, t);
      ans = INF;
    }
  };

  node tree[MAXNODES];

  void merge(node &t, node &l, node &r) {
    int pref_len, suff_len;
    
    pref_len = 0;
    for (int i = 0; i < l.len; ++i)
      t.pref[pref_len++] = l.pref[i];
    for (int i = 0; i < r.len; ++i)
      if (pref_len == 0 || !subset(r.pref[i].first, t.pref[pref_len-1].first)) {
        t.pref[pref_len] = r.pref[i];
        if (pref_len > 0) t.pref[pref_len].first |= t.pref[pref_len-1].first;
        ++pref_len;
      }

    suff_len = 0;
    for (int i = 0; i < r.len; ++i)
      t.suff[suff_len++] = r.suff[i];
    for (int i = 0; i < l.len; ++i)
      if (suff_len == 0 || !subset(l.suff[i].first, t.suff[suff_len-1].first)) {
        t.suff[suff_len] = l.suff[i];
        if (suff_len > 0) t.suff[suff_len].first |= t.suff[suff_len-1].first;
        ++suff_len;
      }

    assert(pref_len == suff_len);
    t.len = pref_len;

    t.ans = INF;
    int pref_pos = 0;
    for (int suff_pos = l.len-1; suff_pos >= 0; --suff_pos) {
      while (pref_pos < r.len && (l.suff[suff_pos].first | r.pref[pref_pos].first) != (1LL<<k)-1)
        ++pref_pos;
      if (pref_pos < r.len) {
        llint curr_mask = l.suff[suff_pos].first | r.pref[pref_pos].first;
        if (curr_mask == (1LL<<k)-1)
          t.ans = min(t.ans, r.pref[pref_pos].second-l.suff[suff_pos].second+1);
      }
    }
    t.ans = min(t.ans, min(l.ans, r.ans));
  }


 public:
  tournament() {}

  void update(int t, int v) {
    t += offset;
    tree[t] = node(t-offset, v);
    for (t /= 2; t > 0; t /= 2)
      merge(tree[t], tree[2*t], tree[2*t+1]);
  }

  int query(void) {
    return tree[1].ans;
  }
  
};

tournament T;

int main(void) {
  scanf("%d%d%d", &n, &k, &q);

  REP (i, n) { 
    int v;
    scanf("%d", &v);
    --v;
    T.update(i, v);
  }

  REP (i, q) {
    int t;
    scanf("%d", &t);
    if (t == 1) {
      int x, v;
      scanf("%d%d", &x, &v);
      --x; --v;
      T.update(x, v);
    } else {
      int ans = T.query();
      printf("%d\n", ans == INF ? -1 : ans);
    }
  }

  return 0;
}
