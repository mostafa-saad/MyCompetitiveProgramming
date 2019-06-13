#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

int N, M[2], Q;
int X[2][200010], Y[2][200010];
vector<int> adj[2][200010];

int gap[2][100010];

int par[200010];
pair<int, int> itv[200010];

void unite(int a, int b) {
  par[b] = a;
  itv[a].first  = min(itv[a].first , itv[b].first );
  itv[a].second = max(itv[a].second, itv[b].second);
}

int root(int t) {
  return par[t] == t ? t : par[t] = root(par[t]);
}

void compute_gap(int k) {
  int T = N + M[k];
  vector<pair<pair<int, int>, int> > ord(T);
  rep (i, T) ord[i] = mp(mp(Y[k][i], X[k][i]), i);
  sort(all(ord));

  rep (i, T) {
    int t = ord[i].second;
    par[t] = t;
    itv[t] = t < N ? mp(t, t) : mp(INT_MAX, INT_MIN);

    vector<int> cs;
    vector<pair<int, int> > is;
    rep (j, adj[k][t].size()) {
      int c = adj[k][t][j];
      if (mp(Y[k][c], X[k][c]) > mp(Y[k][t], X[k][t])) continue;
      int r = root(c);
      cs.pb(r);
      if (itv[r].first != INT_MAX) is.pb(itv[r]);
    }
    sort(all(is));
    rep (j, int(is.size()) - 1) {
      assert(is[j].second + 1 == is[j + 1].first);
      gap[k][is[j].second] = Y[k][t];
    }
    rep (j, cs.size()) unite(t, cs[j]);
  }
}

int main() {
  scanf("%d%d%d%d", &N, &M[0], &M[1], &Q);
  rep (k, 2) {
    rep (i, N) X[k][i] = i;
    for (int i = N; i < N + M[k]; ++i) {
      scanf("%d%d", &X[k][i], &Y[k][i]);
      if (k == 1) Y[k][i] *= -1;
    }
    rep (i, N + M[k] - 1) {
      int t, a, b;
      scanf("%d%d%d", &t, &a, &b);
      a = a - 1 + (t == 1 ? 0 : N);
      b = b - 1 + N;
      adj[k][a].pb(b);
      adj[k][b].pb(a);
    }
  }

  rep (k, 2) compute_gap(k);

  vector<pair<int, int> > ord;
  rep (i, N - 1) ord.pb(mp(gap[0][i], gap[1][i]));
  sort(all(ord));
  reverse(all(ord));

  map<int, int> ans;
  ans[INT_MAX] = 0;
  int b = 0;
  int num_change = 0;
  rep (i, ord.size()) {
    int a = ord[i].first;
    if (ord[i].second > b) {
      b = ord[i].second;
      ans[a] = b;
      num_change++;
    }
  }

  rep (q, Q) {
    int a;
    scanf("%d", &a);
    printf("%d\n", -ans.upper_bound(a)->second);
  }

  return 0;
}
