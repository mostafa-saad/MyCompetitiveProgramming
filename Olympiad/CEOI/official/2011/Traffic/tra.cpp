/* Model solution of task TRA/jlac012
 * Author: Mateusz Baranowski
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define pb push_back
#define MAXN 500000

typedef pair<int, int> PII;

size_t j;
int n, m, A, B;
int i, l, k;
int tmp1, tmp2;
int scc_size; /* number of strongly connected components */
vector<int> west, east; /* junctions on respective river banks */
vector<int> edges[MAXN]; /* streets in road network */
vector<int> edges_rev[MAXN]; /* edges in reversed network */
vector<int> scc[MAXN]; /* vertices in strongly connected component */
int visited[MAXN]; /* was a junction visited */
int order[MAXN]; /* dfs post-order of junctions */
int scc_inv[MAXN]; /* the scc for given junction */
int scc_edges[MAXN]; /* number of edges starting from scc */
PII interval[MAXN]; /* intervals of junctions reachable from junction */

void reorder(int v) {
  size_t j;
  visited[v] = 1;
  for (j = 0; j < edges[v].size(); ++j)
    if (!visited[edges[v][j]]) reorder(edges[v][j]);
  order[l++] = v;
}

void mark_scc(int v) {
  size_t j;
  visited[v] = 0;
  scc[scc_size].pb(v);
  scc_inv[v] = scc_size;
  for (j = 0; j < edges_rev[v].size(); ++j)
    if (visited[edges_rev[v][j]]) mark_scc(edges_rev[v][j]);
}

void calculate_strongly_connected_components() {
  for (i = 0; i < n; ++i) visited[i] = 0;
  l = 0; scc_size = 0;
  for (i = 0; i < n; ++i) if (!visited[i]) reorder(i);
  for (i = n-1; i >= 0; --i) if (visited[order[i]]) {
    mark_scc(order[i]);
    ++scc_size;
  }
  for (i = 0; i < scc_size; ++i) scc_edges[i] = 0;
  for (i = 0; i < n; ++i) for (j = 0; j < edges[i].size(); ++j)
    if (scc_inv[edges[i][j]] != scc_inv[i]) ++scc_edges[scc_inv[i]];
}

void add_interval (PII & a, const PII & b) {
  if (b.first == -1) return;
  if (a.first == -1) { a = b; return; }
  a.first = min(a.first, b.first);
  a.second = max(a.second, b.second);
}

void calculate_reachable_intervals() {
  queue<int> q;
  for (i = 0; i < n; ++i) visited[i] = 0;
  for (i = 0; i < scc_size; ++i) interval[i] = make_pair(-1, -1);
  for (j = 0; j < east.size(); ++j) {
    l = scc_inv[east[j]];
    add_interval (interval[l], make_pair(j, j));
  }
  for (l = 0; l < scc_size; ++l) if (scc_edges[l] == 0) { visited[l] = 1; q.push(l); }
  while (!q.empty()) {
    k = q.front(); q.pop();
    for (j = 0; j < scc[k].size(); ++j) {
      i = scc[k][j];
      while (!edges_rev[i].empty()) {
        l = scc_inv[edges_rev[i].back()]; edges_rev[i].pop_back();
        add_interval(interval[l], interval[k]);
        if (--scc_edges[l] == 0) {
          visited[l] = 1;
          q.push(l);
        }
      }
    }
  }
}

void mark_reachable_industrial() {
  for (i = 0; i < n; ++i) visited[i] = 0;
  l = 0;
  for (j = 0; j < west.size(); ++j) if (!visited[west[j]]) reorder(west[j]);
  for (i = 0; i < n; ++i) order[i] = 0;
  order[0] = visited[east[0]];
  for (j = 1; j < east.size(); ++j)
    order[j] = order[j-1] + visited[east[j]];
}

void read_input() {
  vector<PII> west_tmp; west_tmp.clear();
  vector<PII> east_tmp; east_tmp.clear();
  scanf ("%d %d %d %d", &n, &m, &A, &B);
  for (i = 0; i < n; ++i) {
    scanf ("%d %d", &tmp1, &tmp2);
    if (tmp1 == 0) west_tmp.pb(make_pair(tmp2, i));
    else if (tmp1 == A) east_tmp.pb(make_pair(tmp2, i));
  }
  /* sort junctions according to increasing second coordinates */
  sort(west_tmp.begin(), west_tmp.end());
  for (j = 0; j < west_tmp.size(); ++j) west.pb(west_tmp[j].second);
  sort(east_tmp.begin(), east_tmp.end());
  for (j = 0; j < east_tmp.size(); ++j) east.pb(east_tmp[j].second);
  while (m-->0) {
    scanf("%d %d %d", &tmp1, &tmp2, &i);
    --tmp1; --tmp2;
    edges[tmp1].pb(tmp2);
    edges_rev[tmp2].pb(tmp1);
    if (i == 2) {
      edges[tmp2].pb(tmp1);
      edges_rev[tmp1].pb(tmp2);
    }
  }
}

void write_output() {
  l = west.size();
  for (--l; l >= 0; --l) {
    tmp1 = interval[scc_inv[west[l]]].first;
    tmp2 = interval[scc_inv[west[l]]].second;
    if (tmp1 == -1) printf("0\n");
    else if (tmp1 == 0) printf("%d\n", order[tmp2]);
    else printf("%d\n", order[tmp2] - order[tmp1-1]);
  }
}

int main() {
  read_input();
  calculate_strongly_connected_components();
  calculate_reachable_intervals();
  mark_reachable_industrial();
  write_output();
  return 0;
}
