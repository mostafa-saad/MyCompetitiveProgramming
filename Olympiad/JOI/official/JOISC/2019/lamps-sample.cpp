#include <cstdio>

constexpr int MAX_N = 1000000;

int N;
char A[MAX_N + 1], B[MAX_N + 1];

/*
  0: OFF
  1: ON
  2: KEPT
*/
char apply(char a, int y) {
  return (y == 0) ? '0' : (y == 1) ? '1' : a;
}

int dp[MAX_N + 1][3];

int main() {
  scanf("%d%s%s", &N, A, B);
  for (int i = 0; i <= N; ++i) {
    for (int x = 0; x < 3; ++x) {
      dp[i][x] = N + 1;
    }
  }
  dp[0][2] = 0;
  for (int i = 0; i < N; ++i) {
    for (int x = 0; x < 3; ++x) {
      for (int xx = 0; xx < 3; ++xx) {
        int cost = dp[i][x];
        if (x != xx && xx != 2) {
          ++cost;
        }
        if ((i == 0 || apply(A[i - 1], x) == B[i - 1]) &&
            apply(A[i], xx) != B[i]) {
          ++cost;
        }
        if (dp[i + 1][xx] > cost) {
          dp[i + 1][xx] = cost;
        }
      }
    }
  }
  int ans = N + 1;
  for (int x = 0; x < 3; ++x) {
    if (ans > dp[N][x]) {
      ans = dp[N][x];
    }
  }
  printf("%d\n", ans);
  return 0;
}
