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

int main (void)
{
  int i, k = 0;

  scanf ("%d", &n);

  for (i = 0; i < n; i++)
    scanf ("%d", &seq[i]);

  gen_part_until (0, 0, 1, &k);

  printf ("%d\n", k);
  return 0;
}

