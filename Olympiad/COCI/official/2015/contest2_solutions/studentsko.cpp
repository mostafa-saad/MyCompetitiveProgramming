#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 5000;

int a[MAXN], dp[MAXN];
pair<int, int> v[MAXN];

int main(void) {

  int n, k;
  scanf("%d%d", &n, &k);

  for(int i = 0; i < n; ++i) {
    int x; scanf("%d", &x);
    v[i] = make_pair(x, i);
  }

  sort(v, v + n);

  int mm = 0;

  for(int i = 0; i < n; ++i)
    a[v[i].second] = i / k;

  for(int i = 0; i < n; ++i) {
    dp[i] = 1;
    for(int j = i-1; j >= 0; --j)
      if(a[i] >= a[j]) dp[i] = max(dp[i], 1+dp[j]);
    mm = max(mm, dp[i]);
  }

  printf("%d\n", n-mm);

  return 0;

}
