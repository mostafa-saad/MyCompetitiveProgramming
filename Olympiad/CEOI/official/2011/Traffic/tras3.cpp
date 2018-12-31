/* Slower solution of TRA/jlac012
 * Brutal O(m * min(west, east)) solution with an optimisation,
 * we search the reversed graph when there is more east than west junctions
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

int n, m, A, B;
int i, l;
int tmp1, tmp2;
vector<PII> west; /* junctions on west riverbank */
vector<int> east, edges[MAXN]; /* junctions in road network */
int final[MAXN]; /* if junction reached inc. the result 1 in start vertex, >1 in this vertex*/
int visited[MAXN];

void read_input() {
  scanf ("%d %d %d %d", &n, &m, &A, &B);
  for (i = 1; i <= n; ++i) {
    scanf ("%d %d", &tmp1, &tmp2);
    final[i] = 0;
    if (tmp1 == 0) west.pb(make_pair(tmp2, i));
    else if (tmp1 == A) east.pb(i);
  }
  sort(west.begin(), west.end());
  /* mark destination, if number of |east|<|west| then we consider reversed graph */
  if (west.size() > east.size()) {
    for (size_t s = 0; s < west.size(); ++s) final[west[s].second] = 2;
    while (m-->0) {
      scanf ("%d %d %d", &tmp1, &tmp2, &i);
      edges[tmp2].pb(tmp1);
      if (i == 2) edges[tmp1].pb(tmp2);
    }
  } else {
    for (size_t s = 0; s < east.size(); ++s) final[east[s]] = 1;
    while (m-->0) {
      scanf ("%d %d %d", &tmp1, &tmp2, &i);
      edges[tmp1].pb(tmp2);
      if (i == 2) edges[tmp2].pb(tmp1);
    }
  }
}

int reachable(int v) {
  size_t j;
  int result = 0;
  queue<int> q;
  q.push(v);
  while (!q.empty()) {
    i = q.front(); q.pop();
    if (final[i] == 1) ++result;
    else if (final[i] > 1) ++final[i];
    for (j = 0; j < edges[i].size(); ++j) {
      l = edges[i][j];
      if (visited[l] != v) { visited[l] = v; q.push(l); }
    }
  }
  return result;
}

void generate_output() {
  for (i = 1; i <= n; ++i) visited[i] = 0;
  if (west.size() > east.size()) {
    while (!east.empty()) {
      reachable(east.back());
      east.pop_back();
    }
    while (!west.empty()) {
      printf ("%d\n", final[west.back().second] - 2);
      west.pop_back();
    }
  } else
    while (!west.empty()) {
      printf ("%d\n", reachable(west.back().second));
      west.pop_back();
    }
}

int main() {
  read_input();
  generate_output();
  return 0;
}
