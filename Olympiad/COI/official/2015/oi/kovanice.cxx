// Autor: Gustav Matula 

#include <cstdio>
#include <cassert>
#include <cstring>

#include <algorithm>
#include <iostream>

using namespace std;
typedef long long llint;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

const int MAXN = 1000005;

int n, m, v;
vector< pair< int, int > > E;
vector< int > B[MAXN];
int com[MAXN];

void mark(int i, int c) {
  if (com[i]) return;
  com[i] = c;
  for (int j : B[i])
    mark(j, c);
}

vector< int > D[MAXN]; int d[MAXN];
vector< int > R[MAXN]; int r[MAXN];

int dfs(int i, vector< int > *D, int *d) {
  if (d[i] != 0) return d[i];
  for (int j : D[i]) d[i] = max(d[i], dfs(j, D, d));
  return ++d[i];
}

int main(void) 
{
  scanf("%d%d%d", &n, &m, &v);

  REP(i, v) {
    int a, b; char op;
    scanf("%d%c%d", &a, &op, &b);
    if (op == '<') 
      E.push_back({a, b});
    else {
      B[a].push_back(b);
      B[b].push_back(a);
    }
  }

  FOR(i, 1, m + 1) if (!com[i]) mark(i, i);

  for (auto e : E) {
    D[com[e.first]].push_back(com[e.second]);
    R[com[e.second]].push_back(com[e.first]);
  }

  FOR(i, 1, m + 1) dfs(com[i], D, d);
  FOR(i, 1, m + 1) dfs(com[i], R, r);

  FOR(i, 1, m + 1) {
    if (d[com[i]] + r[com[i]] - 1 == n)
      printf("K%d\n", r[com[i]]);
    else
      puts("?");
  }

  return 0;
}
