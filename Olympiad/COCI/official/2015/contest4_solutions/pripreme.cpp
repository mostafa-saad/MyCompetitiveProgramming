#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

int main(void) {
  int n;
  scanf("%d", &n);
  long long x, sum = 0, maks = 0;
  while (n--) {
    scanf("%lld", &x);
    sum += x;
    maks = max(maks, x);
  }

  printf("%lld\n", max(2*maks, sum));
  return 0;
}
