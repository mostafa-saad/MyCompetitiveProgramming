#include <algorithm>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef long long llint;

int main(void)
{
  int n_a, n_b; scanf("%d %d", &n_a, &n_b);
  vector<int> lb(n_a);

  llint op_suma = 0;
  int cmd_cnt = 0;

  auto out_rev = [&cmd_cnt, &op_suma](int lo, int hi) { // [lo, hi>
    if (lo >= hi) return;
    printf("reverse %d %d\n", lo+1, hi); fflush(stdout);
    op_suma += hi - lo;
    ++cmd_cnt;
  };
  auto is_less = [&cmd_cnt](int x, int y) {
    printf("cmp %d %d\n", x+1, y+1); fflush(stdout);
    int ret; scanf("%d", &ret);
    ++cmd_cnt;
    return ret < 0;
  };

  for (int i = 0; i < n_a; ++i) {
    int lo = n_a, hi = n_a+n_b;
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      if (is_less(mid, i))
        lo = mid + 1;
      else
        hi = mid;
    }
    lb[i] = lo;
  }

  int start = 0;
  int left = n_a;
  int last_idx = n_a;
  for (int i = 0; i < n_a; ++i) {
    int dulj = lb[i] - last_idx;
    out_rev(start+1, lb[i]);
    out_rev(start, start+1+dulj);
    start += 1+dulj;
    --left;
    out_rev(start, start+left);
    last_idx = lb[i];
  }

  assert(op_suma <= int(3e6));
  assert(cmd_cnt <= 100000);
  printf("end\n"); fflush(stdout);

  return 0;
}
