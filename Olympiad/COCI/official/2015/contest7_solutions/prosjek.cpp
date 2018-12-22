#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 300010;

long double s[MAXN];
int a[MAXN];
int n, k;

bool can(long double P) {
  s[0] = 0;
  for (int i = 1; i <= n; ++i)
    s[i] = s[i-1] + a[i] - P;

  long double mins = 0;
  for (int i = k; i <= n; ++i) {
    if (s[i] >= mins) return true;
    mins = min(mins, s[i-k+1]);
  }
  return false;
}

int main(void) {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);

  long double lo = 0, hi = 2e6;
  while (hi-lo > 1e-6) {
    long double mid = (lo + hi) / 2;
    if (can(mid)) lo = mid; else
      hi = mid;
  }

  printf("%.6lf\n", (double)lo);
  return 0;
}
