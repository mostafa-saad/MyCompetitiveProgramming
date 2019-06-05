#include <cstdio>
#include <algorithm>
#include <vector>

#include <iostream>

using namespace std;

const int MAXN = 200050, MAXK = 200050, MAXV = 2 * MAXN + MAXK;
int N, K, M;
int A[MAXN], B[MAXN], T[MAXK], X[MAXV];
pair<int, int> J[MAXN];
vector<int> S[MAXV * 4 + 50];

void insert(int x, int u, int a, int b, int L, int R) {
  if (a == L && b == R) {
    S[x].push_back(u);
    return;
  }
  int m = (L + R) / 2;
  if (a < m) insert(2 * x + 0, u, a, min(b, m), L, m);
  if (b > m) insert(2 * x + 1, u, max(a, m), b, m, R);
}

void check(int x, int j, int t, int L, int R) {
  for (int i = 0; i < S[x].size(); ++i) {
    if (J[S[x][i]].first < 0) {
      J[S[x][i]].first = j;
    }
  }
  S[x].clear();
  if (R - L == 1) {
    return;
  }
  int m = (L + R) / 2;
  if (t < m) check(2 * x + 0, j, t, L, m);
  else       check(2 * x + 1, j, t, m, R);
  return;
}

int F[MAXV];

void update(int x) {
  while (x <= M) {
    ++F[x];
    x += x & -x;
  }
}

int sum(int x) {
  int s = 0;
  while (x > 0) {
    s += F[x];
    x -= x & -x;
  }
  return s;
}


int main() {
  scanf("%d%d", &N, &K);

  int xs = 0;
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &A[i], &B[i]);
    X[xs++] = A[i];
    X[xs++] = B[i];
  }
  for (int j = 0; j < K; ++j) {
    scanf("%d", &T[j]);
    X[xs++] = T[j];
  }

  sort(X, X + xs);
  M = unique(X, X + xs) - X;

  for (int i = 0; i < N; ++i) {
    A[i] = lower_bound(X, X + M, A[i]) - X;
    B[i] = lower_bound(X, X + M, B[i]) - X;
    J[i] = make_pair(-1, i);
    insert(1, i, min(A[i], B[i]), max(A[i], B[i]), 0, M);
  }
  for (int j = K - 1; j >= 0; --j) {
    T[j] = lower_bound(X, X + M, T[j]) - X;
    check(1, j, T[j], 0, M);
  }

  sort(J, J + N);
  reverse(J, J + N);

  int cur = K - 1, all = 0;
  long long res = 0;
  for (int i = 0; i < N; ++i) {
    while (cur > J[i].first) {
      update(T[cur--] + 1);
      ++all;
    }

    int u = J[i].second;
    int flip = (all - sum(B[u])) % 2;
    int start = cur >= 0 ? (A[u] < B[u] ? 1 : 0) : 0;
    res += X[(start + flip) % 2 ? B[u] : A[u]];
  }

  printf("%lld\n", res);

  return 0;
}
