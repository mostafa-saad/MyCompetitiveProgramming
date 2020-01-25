#include <cstdio>

using namespace std;

typedef long long llint;

int q;

int main(void) {
  scanf("%d", &q);
  while (q--) {
    llint l, r;
    scanf("%lld%lld", &l, &r);
    llint tot = r - l + 1;
    llint sol = (tot / 9) * 9 * 10 / 2;
    for (int i = 0; i < tot % 9; ++i) {
      int add = (int) ((l + i) % 9);
      if (add == 0) add = 9;
      sol += (llint) add;
    }
    printf("%lld\n", sol);
  }
  return 0;
}
