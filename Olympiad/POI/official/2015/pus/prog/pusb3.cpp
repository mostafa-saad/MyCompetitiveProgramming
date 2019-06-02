/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Pustynia                                           *
 *   Autor programu:       Bartosz Tarnawski                                  *
 *   Opis:                 Rozwiazanie bledne                                 *
 *                         zapominamy o posortowaniu studni                   *
 *****************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100 * 1000;
const int S = 128 * 1024;
const int M = 200 * 1000;
const int K = 1000 * 1000 * 1000;

struct Edge {
  int l, r;
  int maxi;
  char color;
  vector<int> omit;
  Edge(int _l, int _r) : l(_l), r(_r), maxi(-1), color(0) {}
  Edge() : l(0), r(0), maxi(-1), color(0) {}
};

struct Tree {
  int tab[2 * S];
  Tree() {
    for(int i = 0; i < 2 * S; i++) tab[i] = 0;
  }
  void insert(int p, int v) {
    p += S;
    for(tab[p] = v, p /= 2; p; p /= 2) {
      tab[p] = max(tab[2 * p], tab[2 * p + 1]);
    }
  }
  int get(int l, int r) {
    l += S, r += S;
    int re = max(tab[l], tab[r]);
    while((l / 2) != (r / 2)) {
      if(!(l % 2)) re = max(re, tab[l + 1]);
      if(r % 2) re = max(re, tab[r - 1]);
      l /= 2, r /= 2;
    }
    return re;
  }
} tr;

int depth[N], next_shallower[N], color[N], order[N], vis[N];
int w[N], p[N], last[N];
pair<int, int> wells[N];
vector<int> g[N];
Edge edges[M];
int n, s, m;
int edges_sz, t;

void failure();
void sort_wells();
void init_fu();
void topo_sort();
void dfs(int);
void unite(int, int);
int find(int);
void compute_paths();

void failure() {
  printf("NIE\n");
  exit(0);
}

void sort_wells() {
  //sort(wells, wells + s);
  int next = -1;
  for(int i = 0; i < s; i++) {
    if(wells[i].first > wells[next + 1].first) {
      next = i - 1;
    }
    next_shallower[wells[i].second] = next;
  }
}

void init_fu() {
  for(int i = 0; i < n; i++) {
    p[i] = i;
    last[i] = i;
  }
}

int find(int x) {
  if(p[x] == x) return x;
  p[x] = find(p[x]);
  return p[x];
}

void unite(int x, int y) {
  x = find(x), y = find(y);
  if(x == y) return;
  if(w[x] < w[y]) {
    p[x] = y;
  } else if(w[x] > w[y]) {
    p[y] = x;
  } else {
    p[x] = y;
    w[y]++;
  }
  last[find(x)] = max(last[x], last[y]);
}

void dfs(int v) {
  if(color[v] == 1) {
    failure();
  }
  color[v] = 1;
  if(depth[v]) {
    for(int i = next_shallower[v]; i >= 0; i--) {
      int u = wells[i].second;
      if(color[u] == 2) {
        break;
      }
      dfs(u);
    }
  }

  for(size_t i = 0; i < g[v].size(); i++) {
    Edge &e = edges[g[v][i]];
    if(e.color == 2) {
      continue;
    }
    e.color = 1;
    int u = e.l;
    size_t it = 0;
    while(u <= e.r) { 
      while(it < e.omit.size() && e.omit[it] < u) it++;
      if(it >= e.omit.size() || u != e.omit[it]) {
        if(color[u] != 2) {
          dfs(u);
        }
      }
      u = last[find(u)] + 1;
    }
    e.color = 2;
  }
  vis[v] = t++;
  color[v] = 2;
  if(v + 1 < n && color[v + 1] == 2) {
    unite(v, v + 1);
  }
  if(v - 1 >= 0 && color[v - 1] == 2) {
    unite(v, v - 1);
  }
}

void topo_sort() {
  for(int i = 0; i < n; i++) {
    if(color[i] == 0) {
      dfs(i);
    }
  }
  for(int i = 0; i < n; i++) {
    order[vis[i]] = i;
  }
}

void compute_paths() {
  for(int i = 0; i < n; i++) {
    int u = order[i];
    int nd = 1;
    for(size_t j = 0; j < g[u].size(); j++) {
      Edge &e = edges[g[u][j]];
      if(e.maxi == -1) {
        e.maxi = tr.get(e.l, e.r);
      }
      nd = max(e.maxi + 1, nd);
    }
    if((depth[u] && depth[u] < nd) || (nd > K)) {
      failure();
    }
    depth[u] = max(depth[u], nd);
    tr.insert(u, depth[u]);
  }
}

int main() {
  scanf("%d%d%d", &n, &s, &m);
  for(int i = 0; i < s; i++) {
    int pos, d;
    scanf("%d%d", &pos, &d);
    pos--;
    depth[pos] = d;
    wells[i] = {d, pos};
  }
  for(int i = 0; i < m; i++) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    l--, r--;
    Edge e(l, r);
    for(int j = 0; j < k; j++) {
      int x;
      scanf("%d", &x);
      x--;
      e.omit.push_back(x);
      g[x].push_back(i);
    }
    edges[i] = e;
  }

  sort_wells();
  init_fu();
  topo_sort();
  compute_paths();

  printf("TAK\n");
  for(int i = 0; i < n; i++) {
    printf("%d ", depth[i]);
  }
  printf("\n");

  return 0;
}
