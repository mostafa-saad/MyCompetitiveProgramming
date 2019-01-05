// CEOI 2013 - Task: Treasure - Solution
// Author: Luka Kalinovcic

#include <cstdio>
#include <map>

using namespace std;

struct Rect {
  int r1, c1, r2, c2;
  Rect(int r1, int c1, int r2, int c2) : r1(r1), c1(c1), r2(r2), c2(c2) {}
};
bool operator < (Rect const& A, Rect const& B) {
  if (A.r1 != B.r1) return A.r1 < B.r1;
  if (A.c1 != B.c1) return A.c1 < B.c1;
  if (A.r2 != B.r2) return A.r2 < B.r2;
  if (A.c2 != B.c2) return A.c2 < B.c2;
  return 0;
}

int n;
map<Rect, int> memo;

int Sum(int r1, int c1, int r2, int c2) {
  if (r1 == r2) return 0;
  if (c1 == c2) return 0;
  if (r1 != 0 && r2 != n) {
    return Sum(r1, c1, n, c2) + Sum(0, c1, r2, c2) - Sum(0, c1, n, c2);
  }
  if (c1 != 0 && c2 != n) {
    return Sum(r1, c1, r2, n) + Sum(r1, 0, r2, c2) - Sum(r1, 0, r2, n);
  }
  if (r1 != 0 && r1 >= n - r1) {  // r2 == n
    return Sum(0, c1, n, c2) - Sum(0, c1, r1, c2);
  }
  if (r2 != n - 1 && n - r2 > r2) {  // r1 == 0
    return Sum(0, c1, n, c2) - Sum(r2, c1, n, c2);
  }
  if (c1 != 0 && c1 >= n - c1) {  // c2 == n
    return Sum(r1, 0, r2, n) - Sum(r1, 0, r2, c1);
  }
  if (c2 != n - 1 && n - c2 > c2) {  // c1 == 0
    return Sum(r1, 0, r2, n) - Sum(r1, c2, r2, n);
  }
  Rect rect(r1, c1, r2, c2);
  if (memo.count(rect)) return memo[rect];
  printf("%d %d %d %d\n", r1 + 1, c1 + 1, r2, c2);
  fflush(stdout);
  scanf("%d", &memo[rect]);
  return memo[rect];
}

int main() {
  scanf("%d", &n);
  for (int r = 0; r < n; ++r)
    for (int c = 0; c < n; ++c)
      Sum(r, c, r + 1, c + 1);

  printf("END\n");
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < n; ++c) {
      printf("%d", Sum(r, c, r + 1, c + 1));
    }
    printf("\n");
  }

  return 0;
}
