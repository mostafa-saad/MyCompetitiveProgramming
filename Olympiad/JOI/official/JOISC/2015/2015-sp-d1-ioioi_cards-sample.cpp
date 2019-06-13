#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;

const int MAX_V = 500005;
const ll INF = 1ll<<50;

vector<int> to[MAX_V], cost[MAX_V];
ll dist[MAX_V];
int a[5], V;
ll g[4][4];

ll mcp(int sv, int tv) {
  for (int i = 0; i < V; ++i) dist[i] = INF;
  priority_queue<P, vector<P>, greater<P> > q;
  q.push(P(0ll,sv));
  while (!q.empty()) {
    ll d = q.top().first;
    int v = q.top().second;
    q.pop();
    if (dist[v] != INF) continue;
    dist[v] = d;
    for (int i = 0; i < to[v].size(); ++i) {
      int u = to[v][i];
      ll nd = d + cost[v][i];
      if (dist[u] == INF) q.push(P(nd,u));
    }
  }
  return dist[tv];
}

int main() {
  for (int i = 0; i < 5; ++i) scanf("%d",&a[i]);
  for (int i = 0; i < 4; ++i) a[i+1] += a[i];
  V = a[4]+1;
  int n;
  scanf("%d",&n);
  for (int i = 0; i < n; ++i) {
    int l, r;
    scanf("%d%d",&l,&r);
    --l;
    to[l].push_back(r); cost[l].push_back(r-l);
    to[r].push_back(l); cost[r].push_back(r-l);
  }
  for (int i = 0; i < 4; ++i) for(int j = i+1; j < 4; ++j) {
    g[i][j] = mcp(a[i],a[j]);
  }
  ll ans = INF;
  ans = min(ans, g[0][1] + g[2][3]);
  ans = min(ans, g[0][2] + g[1][3]);
  ans = min(ans, g[0][3] + g[1][2]);
  if (ans == INF) ans = -1;
  printf("%lld\n", ans);
  return 0;
}