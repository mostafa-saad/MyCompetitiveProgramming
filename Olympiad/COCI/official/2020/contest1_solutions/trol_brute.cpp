#include <cstdio>

using namespace std;

typedef long long llint;

int q;

int value(llint x) {
  if (x < 10) return (int) x;
  llint sum = 0;
  while (x) {
    sum += (llint) (x % 10);
    x /= 10;
  }
  return value(sum);
}

int main(void) {
  scanf("%d", &q);
  while (q--) {
    llint l, r;
    scanf("%lld%lld", &l, &r);
    int sol = 0;
    for (llint i = l; i <= r; ++i) {
      sol += value(i);
    }
    printf("%d\n", sol);
  }
  return 0;
}
