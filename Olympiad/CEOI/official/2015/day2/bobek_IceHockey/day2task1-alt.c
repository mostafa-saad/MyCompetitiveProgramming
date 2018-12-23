#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ullong;

static ullong nums[40];
static ullong sums[1 << 20];
static unsigned nsums;
static ullong total;
static ullong atmost;

typedef void (*gscbk) (ullong);

static void
record (ullong x)
{
  sums[nsums++] = x;
}

static void
count (ullong x)
{
  ullong sf = atmost - x;
  int l = 0, h = nsums, m;  /* sums[h] > sf, sums[l] <= sf */

  while (h > l + 1)
    {
      m = (h + l) / 2;

      if (sums[m] > sf)
	h = m;
      else
	l = m;
    }

  total += h;
}

static void
gen_sums (ullong ns[], int n, ullong asum, ullong max, gscbk cb)
{
  if (asum > max)
    return;

  if (n == 0)
    {
      cb (asum);
      return;
    }

  gen_sums (ns + 1, n - 1, asum, max, cb);
  gen_sums (ns + 1, n - 1, asum + ns[0], max, cb);
}

static int
cmpullong (const void *a, const void *b)
{
  ullong aa = *(ullong *) a;
  ullong bb = *(ullong *) b;

  if (aa < bb)
    return -1;

  if (aa > bb)
    return 1;

  return 0;
}

int main (void)
{
  int i, n, r;

  scanf ("%d%llu", &n, &atmost);
  for (i = 0; i < n; i++)
    scanf ("%llu", nums + i);

  r = n / 2;

  gen_sums (nums, r, 0, atmost, record);
  qsort (sums, nsums, sizeof (ullong), cmpullong);
  gen_sums (nums + r, n - r, 0, atmost, count);

  printf ("%llu\n", total);

  return 0;
}
