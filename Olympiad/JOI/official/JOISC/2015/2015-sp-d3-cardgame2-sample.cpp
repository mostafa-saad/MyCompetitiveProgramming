#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 1001001001;

template<typename T> void chmax(T& a, T b) { if (a < b) a = b; }
int in() { int x; scanf("%d", &x); return x; }

const int MAXN = 510;
int N, C[MAXN], A[MAXN], V[MAXN];
int dp[MAXN][MAXN][MAXN];

bool match(int x, int y) {
  return x == 0 || y == 0 || C[x] == C[y] || A[x] == A[y];
}

int main() {
  N = in();
  for (int i = 1; i <= N; ++i) {
    C[i] = in();
    A[i] = in();
    V[i] = in();
  }

  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j <= N; ++j) {
      fill(dp[i][j], dp[i][j] + MAXN, -INF);
    }
  }
  dp[0][1][2] = 0;

  for (int first = 0; first <= N + 1; ++first) {
    for (int second = 0; second <= N + 1; ++second) {
      for (int last = 0; last <= N; ++last) {
        const int cur = dp[last][first][second];
        if (cur >= 0) {
          int third = min(N + 1, max({last, first, second}) + 1);
          if (first <= N && match(last, first)) {
            chmax(dp[first][second][third], cur + V[first]);
          }
          if (third <= N && match(last, third)) {
            chmax(dp[third][first][second], cur + V[third]);
          }
        }
      }
    }
  }

  int res = 0;
  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j <= N + 1; ++j) {
      chmax(res, *max_element(dp[i][j], dp[i][j] + MAXN));
    }
  }

  printf("%d\n", res);
  
  return 0;
}
