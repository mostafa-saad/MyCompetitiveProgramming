#include <cstdio>

using namespace std;

typedef long long llint; 

const int MAXN = 1e6 + 10;

int n;
llint a[MAXN];

int main(void) {

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) 
    scanf("%lld", &a[i]);

  int sol = 0, lo = 0, hi = n - 1;

  while (lo < hi) {
    
    if (a[lo] == a[hi]) {
      ++lo; --hi;
      continue;
    }

    if (a[lo] < a[hi]) {
      a[lo + 1] += a[lo];
      ++lo;
    } else {
      a[hi - 1] += a[hi];
      --hi;
    }

    ++sol;

  }

  printf("%d\n", sol);

  return 0;

}
