#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
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

const int MAXN = 100100;
const int offset = (1 << 18);

struct tournament {
  stack <pii> s[offset * 2];
  
  void add(int node, int l, int r, int a, int b, pii x) {
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
      s[node].push(x);
      return;
    }

    int mid = (l + r) / 2;

    add(node * 2, l, mid , a, b, x);
    add(node * 2 + 1, mid + 1, r, a, b, x);
  }

  void rem(int node, int l, int r, int a, int b) {
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
      s[node].pop();
      return;
    }

    int mid = (l + r) / 2;

    rem(node * 2, l, mid, a, b);
    rem(node * 2 + 1, mid + 1, r, a, b);
  }

  int get(int node) {
    node += offset;
    int ret = -1;
    int last = -1;

    while (node) {
      if (!s[node].empty()) {
        if (s[node].top().fi > last) {
          last = s[node].top().fi;
          ret = s[node].top().sec;
        }
      }
      node /= 2;
    }
    return ret;
  }
}T;

int n, m;
int a[MAXN], b[MAXN], c[MAXN], d[MAXN];
int x[MAXN], y[MAXN], k[MAXN];
int ans[MAXN];

int in_deg[MAXN];
vector <int> v[MAXN], rev[MAXN];

int where[MAXN];
set <int> in[MAXN];

void comp() {
  vector <int> v;
  REP(i, n) {
    v.push_back(b[i]);
    v.push_back(d[i]);
  }
  REP(i, m) v.push_back(y[i]);

  sort(all(v));
  v.erase(unique(all(v)), v.end());
  
  REP(i, n) {
    b[i] = lower_bound(all(v), b[i]) - v.begin();
    d[i] = lower_bound(all(v), d[i]) - v.begin();
  }
  REP(i, m) y[i] = lower_bound(all(v), y[i]) - v.begin();
}

void sweep() {
  vector <pair <pii, pii> > ev;
  REP(i, n) {
    ev.push_back(mp(mp(c[i] + 1, -(i + 1)), mp(b[i], d[i])));
    ev.push_back(mp(mp(a[i], (i + 1)), mp(b[i], d[i])));
  }
  REP(i, m) ev.push_back(mp(mp(x[i], MAXN), mp(y[i], i)));

  sort(all(ev));

  REP(i, (int)ev.size()) {
    if (ev[i].fi.sec == MAXN) {
      int ind = T.get(ev[i].sec.fi);
      if (ind != -1) in[ind].insert(k[ev[i].sec.sec]);
    }
    else if (ev[i].fi.sec > 0) {
      int ind = T.get(ev[i].sec.sec);
      if (ind != -1) {
        v[ind].push_back(ev[i].fi.sec);
        in_deg[ev[i].fi.sec]++;
      }
      T.add(1, 0, offset - 1, ev[i].sec.fi, ev[i].sec.sec, mp(i, ev[i].fi.sec));
    }
    else {
      T.rem(1, 0, offset - 1, ev[i].sec.fi, ev[i].sec.sec);
    }
  }
}

void merge(int a, int b) {
  if ((int)in[where[a]].size() < (int)in[where[b]].size()) swap(where[a], where[b]);
  for (set <int> :: iterator it = in[where[b]].begin(); it != in[where[b]].end(); it++)
    in[where[a]].insert(*it);
}

void dfs(int node) {
  REP(i, (int)v[node].size()) {
    int nnode = v[node][i];
    dfs(nnode);
    merge(node, nnode);
  }
  ans[node] = (int)in[where[node]].size();
}

void solve() {
  FOR(i, 1, n + 1) where[i] = i;
  FOR(i, 1, n + 1) 
    if (in_deg[i] == 0)
      dfs(i);
}

int main() {
  scanf("%d %d",&n,&m);
  REP(i, n) scanf("%d %d %d %d",&a[i],&b[i],&c[i],&d[i]);
  REP(i, m) scanf("%d %d %d",&x[i],&y[i],&k[i]);

  comp();
  sweep();
  solve();

  FOR(i, 1, n + 1) printf("%d\n",ans[i]);
  return 0;
}

