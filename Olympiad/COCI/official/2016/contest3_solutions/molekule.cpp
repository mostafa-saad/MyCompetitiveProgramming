#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR (i, 0, (n))
#define TRACE(x) cout << #x << " = " << endl
#define _ << " _ " <<

using namespace std;

struct edge {
  int end, id;
  edge() {}
  edge(int end, int id): end(end), id(id) {}
};

const int MAXN = 100000;

int n;
int a[MAXN], b[MAXN];
vector<edge> E[MAXN];
int col[MAXN];

int main(void) {
  scanf("%d", &n);
  REP (i, n-1) {
    scanf("%d%d", &a[i], &b[i]);
    --a[i]; --b[i];
    E[a[i]].emplace_back(b[i], i);
    E[b[i]].emplace_back(a[i], i);
  }

  memset(col, -1, sizeof col);
  col[0] = 0;

  queue<int> Q;
  Q.push(0);

  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (edge e: E[u]) {
      if (col[e.end] != -1) continue;
      col[e.end] = 1-col[u];
      Q.push(e.end);
    }
  }

  REP (i, n-1)
    printf("%d\n", col[a[i]]);

  return 0;
}
