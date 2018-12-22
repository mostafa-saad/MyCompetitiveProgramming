#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long llint;

llint n;
int k, q;

llint myabs (llint x) {
  if (x < 0) return -x;
  return x;
}

llint dist (llint x, llint y) {
  if (k == 1) return myabs(y - x);
  int ans = 0;
  while (x != y) {
    if (x < y) swap(x, y); 
    x = (x + k - 2) / k;
    ++ans;
  }

  return ans;
}

int main (void){
  scanf("%lld%d%d", &n, &k, &q);

  for (int i = 0; i < q; ++i) {
    llint x, y;
    scanf("%lld%lld", &x, &y);
    printf("%lld\n", dist(x, y));
  }

  return 0;
}

