#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <numeric>
#include <algorithm>
#include <bitset>
#include <complex>

using namespace std;

typedef unsigned uint;
typedef long long Int;

const int INF = 1001001001;
const Int INFLL = 1001001001001001001LL;

template<typename T> void pv(T a, T b) { for (T i = a; i != b; ++i) cout << *i << " "; cout << endl; }
template<typename T> void chmin(T& a, T b) { if (a > b) a = b; }
template<typename T> void chmax(T& a, T b) { if (a < b) a = b; }
int in() { int x; scanf("%d", &x); return x; }

const int MAXN = 100050, MAXM = 200050;
int ptr[MAXN], A[MAXM], B[MAXM], adj[MAXM], nxt[MAXM];
int outdeg[MAXN], visited[MAXN], sz[MAXN];

int U[MAXN];
void init(int n) {
  for (int i = 0; i < n; ++i) {
    U[i] = i;
  }
}
int find(int x) {
  if (U[x] != x) {
    return U[x] = find(U[x]);
  }
  return U[x];
}
void uni(int x, int y) {
  U[find(x)] = find(y);
}

void dfs(int u, vector<int>& reachable) {
  for (int z = ptr[u]; ~z; z = nxt[z]) {
    int v = adj[z];
    reachable.push_back(v);
    if (!visited[v]) {
      visited[v] = 1;
      dfs(v, reachable);
    }
  }
}

int main()
{
  int N = in();
  int M = in();

  memset(ptr, ~0, sizeof(ptr));
  for (int i = 0; i < M; ++i) {
    A[i] = in() - 1;
    B[i] = in() - 1;
    nxt[i] = ptr[A[i]]; ptr[A[i]] = i; adj[i] = B[i];
    ++outdeg[A[i]];
  }

  init(N);
  for (int i = 0; i < N; ++i) {
    if (outdeg[i] >= 2 && !visited[i]) {
      vector<int> reachable;
      dfs(i, reachable);
      for (int j = 0; j + 1 < reachable.size(); ++j) {
        uni(reachable[j], reachable[j + 1]);
      }
    }
  }

  Int res = 0;
  for (int i = 0; i < N; ++i) {
    ++sz[find(i)];
  }
  for (int i = 0; i < N; ++i) {
    res += (Int)sz[i] * (sz[i] - 1);
  }
  for (int i = 0; i < M; ++i) {
    if (find(A[i]) != find(B[i])) {
      ++res;
    }
  }

  printf("%lld\n", res);

  return 0;
}
