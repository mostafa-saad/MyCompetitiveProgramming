/* Alternative solution of TRA/jlac012
 * Searching for lowest and highest reachable eastern junction
 * Author: Mateusz Baranowski
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define pb push_back
#define MAXN 300001

typedef pair<int, int> PII;
size_t j;
int n, m, A, B;
int i, l, k;
int tmp1, tmp2;
vector<int> west, east; /* junctions on respective river banks */
vector<int> edges[MAXN]; /* streets in road network */
vector<int> edges_rev[MAXN]; /* edges in reversed network */
int visited[MAXN]; /* was a junction visited */
int visited2[MAXN]; /* whether a juntion was visited */
int eastern[MAXN]; /* the number of eastern bank junction for node */
PII interval[MAXN]; /* intervals of junctions reachable from junction */

/* check which junctions are reachable from nodes through current_edges */
void visit(vector<int> & nodes, vector<int> * current_edges) {
  queue<int> q;
  size_t j;
  for (i = 0; i < n; ++i) visited[i] = 0;
  for (j = 0; j < nodes.size(); ++j) {
    visited[nodes[j]] = 1;
    q.push(nodes[j]);
  }
  while (!q.empty()) {
    i = q.front(); q.pop();
    for (j = 0; j < current_edges[i].size(); ++j) {
      l = current_edges[i][j];
      if (!visited[l]) { visited[l] = 1; q.push(l); }
    }
  }
}

/* mark reachable eastern junctions */
void mark_reachable_east() {
  visit(west, edges);
  for (i = 0; i < n; ++i) eastern[i] = -1;
  l = 0;
  for (j = 0; j < east.size(); ++j)
    if (visited[east[j]]) eastern[east[j]] = l++;
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

/* find northernmost (when k==0 southernmost) eastern junction reachable from v */
int visit_and_find(int v, int p) {
  queue<int> q;
  size_t j;
  q.push(v);
  while (!q.empty()) {
    i = q.front(); q.pop();
    if ((k == 1 && eastern[i] > p) || (k == 0 && eastern[i] < p && eastern[i] != -1))
      p = eastern[i];
    for (j = 0; j < edges[i].size(); ++j) {
      l = edges[i][j];
      if (!visited2[l]) { visited2[l] = 1; q.push(l); }
    }
  }
  return p;
}

void calculate_output() {
  int l = west.size();
  size_t j;
  /* calculate southernmost reachable eastern bank junction */
  tmp1 = MAXN;
  k = 0;
  for (i = 0; i < n; ++i) visited2[i] = 0;
  for (--l; l >= 0; --l) if (visited[west[l]]) {
    visited2[i] = 1;
    tmp1 = visit_and_find(west[l], tmp1);
    interval[l].first = tmp1;
  }
  /* calculate northernmost reachable eastern bank junction */
  tmp1 = -1;
  k = 1;
  for (i = 0; i < n; ++i) visited2[i] = 0;
  for (j = 0; j < west.size(); ++j) if (visited[west[j]]) {
    visited2[i] = 1;
    tmp1 = visit_and_find(west[j], tmp1);
    interval[j].second = tmp1;
  }
}

void write_output() {
  l = west.size();
  for (--l; l >= 0; --l)
    if (visited[west[l]])
      printf("%d\n", interval[l].second - interval[l].first + 1);
    else
      printf("0\n");
}

int main() {
  read_input();
  mark_reachable_east();
  visit(east, edges_rev);
  calculate_output();
  write_output();
  return 0;
}
