#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
using llint = long long;

const int MAXN = 1000010;

int n;
llint x;
bool mid[MAXN];

int main(void) {
  scanf("%d %lld",&n,&x);

  for(int k = 1; k <= n - 2; ++k)
    if (x >= n - 1 - k) {
      mid[k] = true;
      x -= n - 1 - k;
    }
  if (x > 0) {
    printf("-1\n");
    return 0;
  }
    
  printf("%d ",n);
  for (int k = 1; k <= n - 2; ++k)
    if (mid[k])
      printf("%d ",k);
  printf("%d ",n - 1);
  for (int k = n - 2; k >= 1; --k)
    if (!mid[k])
      printf("%d ",k);
  printf("\n");

  return 0;
}
