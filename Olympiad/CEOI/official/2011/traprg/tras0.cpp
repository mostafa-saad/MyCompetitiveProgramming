/* Slower solution of TRA/jlac012
 * Brutal O(n^2) solution, for each west junction search the whole graph
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
vector<int> edges[MAXN]; /* junctions in road network */
int eastern[MAXN]; /* equals 1 when junction lies on the east bank */
size_t visited[MAXN];

void read_input() {
  scanf ("%d %d %d %d", &n, &m, &A, &B);
  for (i = 1; i <= n; ++i) {
    scanf ("%d %d", &tmp1, &tmp2);
    eastern[i] = 0;
    if (tmp1 == 0) west.pb(make_pair(tmp2, i));
    else if (tmp1 == A) eastern[i] = 1;
  }
  sort(west.begin(), west.end());
  while (m-->0) {
    scanf ("%d %d %d", &tmp1, &tmp2, &i);
    edges[tmp1].pb(tmp2);
    if (i == 2) edges[tmp2].pb(tmp1);
  }
}

int reachable(int v) {
  size_t j;
  int result = 0;
  queue<int> q;
  q.push(v);
  while (!q.empty()) {
    i = q.front(); q.pop();
    result += eastern[i];
    for (j = 0; j < edges[i].size(); ++j) {
      l = edges[i][j];
      if (visited[l] != west.size()) { visited[l] = west.size(); q.push(l); }
    }
  }
  return result;
}

void generate_output() {
  for (i = 1; i <= n; ++i) visited[i] = 0;
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
