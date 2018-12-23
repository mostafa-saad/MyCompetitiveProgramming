#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MP 1000007

static int n, seq[MAXN];

static int *saved;

static int
num_until (int len_gen, int max_part, int matches)
{
  long long s = 0;
  int idx;

  if (len_gen == n)
    return 1;

  if (matches)
    {
      s = (long long) (seq[len_gen] - 1) * num_until (len_gen + 1, max_part, 0);
      s += num_until (len_gen + 1, max_part < seq[len_gen] ? seq[len_gen] : max_part, 1);
      return s % MP;
    }

  idx = n * len_gen + max_part;
  if (saved[idx])
    return saved[idx];

  s = (long long) max_part * num_until (len_gen + 1, max_part, 0);
  s += num_until (len_gen + 1, max_part + 1, 0);
  s %= MP;
  saved[idx] = s;
  return s;
}

int main (void)
{
  int i, t;

  scanf ("%d", &n);
  t = n * n;
  saved = malloc (t * sizeof (int));
  for (i = 0; i < t; i++)
    saved[i] = 0;

  for (i = 0; i < n; i++)
    scanf ("%d", &seq[i]);

  printf ("%d\n", num_until (0, 0, 1));

  return 0;
}

