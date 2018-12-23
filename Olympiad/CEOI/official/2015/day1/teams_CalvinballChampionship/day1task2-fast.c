#include <stdio.h>

#define MAXN 10000
#define MP 1000007

static long long num[2][MAXN];
static int seq[MAXN];
static int max_till[MAXN];

int main (void)
{
  int i, k, n, old, before = 0;

  scanf ("%d", &n);

  for (i = 0; i < n; i++)
    {
      num[0][i] = 1;
      scanf ("%d", &seq[i]);
    }

  max_till[0] = 0;
  for (i = 1; i < n; i++)
    if (max_till[i - 1] < seq[i - 1])
      max_till[i] = seq[i - 1];
    else
      max_till[i] = max_till[i - 1];

  old = 0;
  for (i = n - 1; i >= 0; i--)
    {
      int p = (num[old][max_till[i]] * (seq[i] - 1)) % MP;
      before = (before + p) % MP;

      for (k = 0; k < i; k++)
	num[1 - old][k] = (k * num[old][k] + num[old][k + 1]) % MP;
      old = 1 - old;
    }

  printf ("%d\n", before + 1);

  return 0;
}
