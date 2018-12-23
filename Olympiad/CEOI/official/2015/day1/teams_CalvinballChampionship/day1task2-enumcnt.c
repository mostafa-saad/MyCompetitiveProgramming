#include <stdio.h>

#define MAXN 10000
#define MP 1000007

static int n, seq[MAXN];

static int
gen_part_until (int len_gen, int max_part, int matches, int *seen)
{
  int p;

  if (len_gen == n)
    {
      *seen = ((*seen + 1) % MP);
      return matches;
    }

  for (p = 1; p <= max_part; p++)
    if (gen_part_until (len_gen + 1, max_part, matches && seq[len_gen] == p, seen))
      return 1;

  return gen_part_until (len_gen + 1, max_part + 1, matches && seq[len_gen] == max_part + 1, seen);
}

static int
is_last (void)
{
  int i;

  for (i = 0; i < n; i++)
    if (seq[i] != i + 1)
      return 0;

  return 1;
}

static long long np[MAXN + 1];
static long long binom[MAXN];

static int
count_parts (int x)
{
  int n, k;
  long long s;

  np[0] = np[1] = 1;
  binom[0] = 1;

  for (n = 1; n < x; n++)
    {
      for (k = n; k > 0; k--)
	binom[k] = (binom[k] + binom[k - 1]) % MP;

      s = 0;
      for (k = 0; k <= n; k++)
	s = (s + np[k] * binom[k]) % MP;

      np[n + 1] = s;
    }

  return np[x];
}

int main (void)
{
  int i, k = 0;

  scanf ("%d", &n);

  for (i = 0; i < n; i++)
    scanf ("%d", &seq[i]);

  if (is_last ())
    k = count_parts (n);
  else
    gen_part_until (0, 0, 1, &k);

  printf ("%d\n", k);
  return 0;
}

