#include "secret.h"

#define MAX_N 1000

int range[MAX_N + 1][MAX_N + 1];

void Solve(int left, int right) {
  int mid, i;
  if (right - left <= 1) {
    return;
  }
  mid = (left + right) / 2;
  for (i = mid - 1; i >= left; --i) {
    if (range[i][mid] == -1) {
      range[i][mid] = Secret(range[i][i + 1], range[i + 1][mid]);
    }
  }
  for (i = mid + 1; i <= right; ++i) {
    if (range[mid][i] == -1) {
      range[mid][i] = Secret(range[mid][i - 1], range[i - 1][i]);
    }
  }
  Solve(left, mid);
  Solve(mid, right);
}

void Init(int N, int A[]) {
  int i, j;
  for (i = 0; i <= N; ++i) {
    for (j = 0; j <= N; ++j) {
      range[i][j] = -1;
    }
  }
  for (i = 0; i < N; ++i) {
    range[i][i + 1] = A[i];
  }
  Solve(0, N);
}

int Query(int L, int R) {
  int i;
  for (i = L + 1; i <= R; ++i) {
    if (range[L][i] != -1 && range[i][R + 1] != -1) {
      return Secret(range[L][i], range[i][R + 1]);
    }
  }
  return range[L][R + 1];
}
