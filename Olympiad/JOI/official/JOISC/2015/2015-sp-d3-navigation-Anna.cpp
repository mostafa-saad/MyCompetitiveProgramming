#include "Annalib.h"
#include <bits/stdc++.h>

using namespace std;

static vector<int> g[100005];

static int mark[100005];

static void dfs(int v, int p) {
  for (auto to : g[v]) {
    if (to == p) continue;

    if (to > v)
      mark[to] = (1 ^ mark[v]);
    else
      mark[to] = (mark[v]);

    dfs(to, v);
  }
}

void Anna(int K, int N, int T, int A[], int B[]) {
  for (int i = 0; i < N - 1; ++i) {
    g[A[i]].push_back(B[i]);
    g[B[i]].push_back(A[i]);
  }

  dfs(T, -1);

  for (int i = 1; i <= N; ++i) {
    Flag(i, mark[i]);
  }
}
