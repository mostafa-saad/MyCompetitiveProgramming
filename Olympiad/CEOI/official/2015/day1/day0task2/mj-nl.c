/* O(N*L) cas, O(L) pamet */

#include <stdio.h>

#define MAXQ 256
#define M 4000000009U

long long x[MAXQ];

int main(void)
{
  int n, l, k;
  scanf("%d%d%d", &n, &l, &k);
  if (!n) { printf("1\n"); return 0; }

  x[1] = 1;
  for (int i=2; i<l; i++)
    x[i] = (x[i-1]*k) % M;
  if (n<l) { printf("%llu\n", (x[n]*k) % M); return 0; }

  unsigned p = l-1;
  for (int i=l; i<=n; i++)
    {
      p = (p+1) % MAXQ;
      long long t = 0;
      for (int z=1; z<l; z++)
	t += x[(p-z+MAXQ) % MAXQ];
      x[p] = t*(k-1) % M;
    }
  printf("%llu\n", (x[p]*k) % M);
  return 0;
}
