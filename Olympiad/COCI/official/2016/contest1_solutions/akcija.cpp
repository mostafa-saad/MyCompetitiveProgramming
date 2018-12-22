#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 100000
typedef long long llint;

int C[MAXN];

bool cmp(int a, int b) {
  return a > b;
}

int main(void) {
  int n; scanf ("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf ("%d", &C[i]);
  }

  sort(C, C+n, cmp);

  llint sol = 0;
  for (int i = 0; i < n; i++) {
    if (i % 3 == 2) {
      continue;
    }
    sol += C[i];
  }

  printf ("%lld\n", sol);

  return 0;
}
