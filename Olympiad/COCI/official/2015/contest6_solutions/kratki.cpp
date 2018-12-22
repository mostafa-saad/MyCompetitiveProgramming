#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int n, k;

int main (void){
  scanf("%d%d", &n, &k);

  if (k*1LL*k*1LL < n){ printf("-1\n"); return 0; }
  
  for (int i = n; i >= 1; i -= k){
    for (int j = max(1, i - k + 1); j <= i; ++j)
      printf("%d ", j);
  }

  printf("\n");

  return 0;
}

