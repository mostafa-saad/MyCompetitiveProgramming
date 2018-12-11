/**
 *    author:  tourist
 *    created: 10.05.2018 15:20:24       
**/
#include <bits/stdc++.h>
 
using namespace std;
 
template <typename T>
class graph {
  public:
  struct edge {
    int from;
    int to;
    T cost;
  };
 
  vector<edge> edges;
  vector< vector<int> > g;
  int n;
 
  function<bool(int)> ignore;
 
  graph(int _n) : n(_n) {
    g.resize(n);
    ignore = nullptr;
  }
 
  virtual int add(int from, int to, T cost) = 0;
 
  virtual void set_ignore_edge_rule(const function<bool(int)> &f) {
    ignore = f;
  }
 
  virtual void reset_ignore_edge_rule() {
    ignore = nullptr;
  }
};
 
template <typename T>
class undigraph : public graph<T> {
  public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;
 
  undigraph(int _n) : graph<T>(_n) {
  }
 
  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int) edges.size();
    g[from].push_back(id);
    g[to].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }
};
 
template <typename T>
class dfs_undigraph : public undigraph<T> {
  public:
  using undigraph<T>::edges;
  using undigraph<T>::g;
  using undigraph<T>::n;
  using undigraph<T>::ignore;
 
  vector<int> pv;
  vector<int> pe;
  vector<int> order;
  vector<int> pos;
  vector<int> end;
  vector<int> sz;
  vector<int> root;
  vector<int> depth;
  vector<int> min_depth;
  vector<T> dist;
  vector<int> was;
  int attempt;
 
  dfs_undigraph(int _n) : undigraph<T>(_n) {
  }
 
  void init() {
    pv = vector<int>(n, -1);
    pe = vector<int>(n, -1);
    order.clear();
    pos = vector<int>(n, -1);
    end = vector<int>(n, -1);
    sz = vector<int>(n, 0);
    root = vector<int>(n, -1);
    depth = vector<int>(n, -1);
    min_depth = vector<int>(n, -1);
    dist = vector<T>(n);
    was = vector<int>(n, -1);
    attempt = 0;
  }
 
  void clear() {
    pv.clear();
    pe.clear();
    order.clear();
    pos.clear();
    end.clear();
    sz.clear();
    root.clear();
    depth.clear();
    min_depth.clear();
    dist.clear();
    was.clear();
  }
 
  private:
  void do_dfs(int v) {
    was[v] = attempt;
    pos[v] = (int) order.size();
    order.push_back(v);
    sz[v] = 1;
    min_depth[v] = depth[v];
    for (int id : g[v]) {
      if (id == pe[v] || (ignore != nullptr && ignore(id))) {
        continue;
      }
      auto &e = edges[id];
      int to = e.from ^ e.to ^ v;
      if (was[to] == attempt) {
        min_depth[v] = min(min_depth[v], depth[to]);
        continue;
      }
      depth[to] = depth[v] + 1;
      dist[to] = dist[v] + e.cost;
      pv[to] = v;
      pe[to] = id;
      root[to] = (root[v] != -1 ? root[v] : to);
      do_dfs(to);
      sz[v] += sz[to];
      min_depth[v] = min(min_depth[v], min_depth[to]);
    }
    end[v] = (int) order.size() - 1;
  }
 
  void do_dfs_from(int v) {
    ++attempt;
    depth[v] = 0;
    dist[v] = T{};
    root[v] = v;
    pv[v] = pe[v] = -1;
    do_dfs(v);
  }
 
  public:
  void dfs(int v, bool clear_order = true) {
    if (pv.empty()) {
      init();
    } else {
      if (clear_order) {
        order.clear();
      }
    }
    do_dfs_from(v);
  }
 
  void dfs_all() {
    init();
    for (int v = 0; v < n; v++) {
      if (depth[v] == -1) {
        do_dfs_from(v);
      }
    }
    assert((int) order.size() == n);
  }
};
 
template <typename T>
vector<int> find_biconv(dfs_undigraph<T> &g, int &cnt) {
  g.dfs_all();
  vector<int> vertex_comp(g.n);
  cnt = 0;
  for (int i : g.order) {
    if (g.pv[i] == -1) {
      vertex_comp[i] = -1;
      continue;
    }
    if (g.min_depth[i] >= g.depth[g.pv[i]]) {
      vertex_comp[i] = cnt++;
    } else {
      vertex_comp[i] = vertex_comp[g.pv[i]];
    }
  }
  vector<int> edge_comp(g.edges.size(), -1);
  for (int id = 0; id < (int) g.edges.size(); id++) {
    if (g.ignore != nullptr && g.ignore(id)) {
      continue;
    }
    int x = g.edges[id].from;
    int y = g.edges[id].to;
    int z = (g.depth[x] > g.depth[y] ? x : y);
    edge_comp[id] = vertex_comp[z];
  }
  return edge_comp;
}
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  dfs_undigraph<int> g(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    x--; y--;
    g.add(x, y);
  }
/*  if (n == 4 && m == 4 && g.edges[0].from == 0 && g.edges[0].to == 1 &&
                          g.edges[1].from == 1 && g.edges[1].to == 2 &&
                          g.edges[2].from == 2 && g.edges[2].to == 3 &&
                          g.edges[3].from == 3 && g.edges[3].to == 1) {
    cout << 14 << '\n';
    return 0;
  }*/
  int cnt;
  vector<int> edge_comp = find_biconv(g, cnt);
  int nv = n + cnt;
  vector< vector<int> > tree(nv);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < 2; j++) {
      int x = (j == 0 ? g.edges[i].from : g.edges[i].to);
      int y = n + edge_comp[i];
      tree[x].push_back(y);
      tree[y].push_back(x);
    }
  }
  for (int i = 0; i < nv; i++) {
    sort(tree[i].begin(), tree[i].end());
    tree[i].resize(unique(tree[i].begin(), tree[i].end()) - tree[i].begin());
  }
  vector<int> cost(nv);
  for (int i = 0; i < nv; i++) {
    cost[i] = (i < n);
  }
  vector<int> was(nv, 0);
  vector<int> root(nv, -1);
  vector<int> sum(nv);
  long long ans = 0;
  function<void(int,int)> dfs1 = [&](int v, int pr) {
    was[v] = 1;
    sum[v] = cost[v];
    for (int u : tree[v]) {
      if (u == pr) {
        continue;
      }
      root[u] = root[v];
      dfs1(u, v);
      sum[v] += sum[u];
    }
  };
  function<void(int,int)> dfs2 = [&](int v, int pr) {
    was[v] = 1;
    vector<int> children;
    for (int u : tree[v]) {
      if (u == pr) {
        continue;
      }
      root[u] = root[v];
      dfs2(u, v);
      children.push_back(sum[u]);
    }
    children.push_back(sum[root[v]] - sum[v]);
    int cc = (int) children.size();
    ans += (long long) (sum[root[v]] - cost[v]) * (sum[root[v]] - cost[v]) * (cost[v] == 1 ? 1 : cc - 2);
    for (int i = 0; i < cc; i++) {
      ans -= (long long) children[i] * children[i] * (cost[v] == 1 ? 1 : cc - 2);
    }
  };
  for (int i = 0; i < nv; i++) {
    if (!was[i]) {
      root[i] = i;
      dfs1(i, -1);
      dfs2(i, -1);
    }
  }
  cout << ans << '\n';
  return 0;
}