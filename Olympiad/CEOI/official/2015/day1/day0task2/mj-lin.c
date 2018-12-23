/* O(N) cas, O(L) pamet */

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
  unsigned long long s = 1;
  for (int i=2; i<l; i++)
    s += x[i] = x[i-1]*k % M;
  if (n<l) { printf("%llu\n", x[n]*k % M); return 0; }

  unsigned p = l-1;
  for (int i=l; i<=n; i++)
    {
      p = (p+1) % MAXQ;
      x[p] = (s*(k-1)) % M;
      s = (s + x[p] - x[(p-l+1+MAXQ) % MAXQ] + M) % M;
    }
  printf("%llu\n", x[p]*k % M);
  return 0;
}
