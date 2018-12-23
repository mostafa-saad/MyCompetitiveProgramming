// CEOI 2013 - Task: Board - Solution
// Author: Gustav Matula

#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

#define MAX 100005

char pa[MAX]; int _a[MAX], loga, *a;
char pb[MAX]; int _b[MAX], logb, *b;

void carry(int *idx, int i) {
  idx[i - 1] += idx[i] / 2 - (idx[i] % 2 == -1);
  idx[i] = abs(idx[i]) % 2;
}

void trace(char *path, int *idx, int &log) {
  int n = strlen(path);
  idx[0] = log = 1;

  for (int i = 0; i < n; ++i) {
    if (path[i] == '1') idx[log++] = 0;
    if (path[i] == '2') idx[log++] = 1;
    if (path[i] == 'L') --idx[log - 1];
    if (path[i] == 'R') ++idx[log - 1];
    if (path[i] == 'U') carry(idx, --log);
  }

  for (int i = log - 1; i >= 1; --i) carry(idx, i);

  int r = 0; while (idx[r] == 0) ++r;
  for (int i = r; i < log; ++i) idx[i - r] = idx[i];
  log -= r;
}

int main(void)
{
  scanf("%s", pa); trace(pa, a = _a, loga);
  scanf("%s", pb); trace(pb, b = _b, logb);

  int log = min(loga, logb);
  int sol = 1 << 20;
  int delta = 0;

  for (int i = 0; i < log && delta < (1 << 20); ++i) {
    delta = delta * 2 + a[i] - b[i];
    sol = min(sol, abs(delta) + 2 * (log - i - 1));
  }

  printf("%d\n", sol + abs(loga - logb));

  return 0;
}
