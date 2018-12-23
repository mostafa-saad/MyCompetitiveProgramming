/* O(N*L) cas, O(N) pamet */

#include <stdio.h>

#define MAXN 1000000
#define M 4000000009U

long long x[MAXN+1];

int main(void)
{
  int n, l, k;
  scanf("%d%d%d", &n, &l, &k);
  if (!n) { printf("1\n"); return 0; }

  x[0] = 1;
  for (int i=1; i<=n; i++)
    {
      x[i] = 0;
      for (int z=i-1; z > i-l && z >= 0; z--)
	if (z == 0)
	  x[i] = (x[i] + 1) % M;
	else
	  x[i] = (x[i] + (k-1)*x[z]) % M;
      // printf("%u\n", k*x[i]);
    }
  printf("%u\n", (int)((k*x[n]) % M));

  return 0;
}
