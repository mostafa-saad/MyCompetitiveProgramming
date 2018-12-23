#include <stdio.h>
#include <stdlib.h>

#define MAXN 40
#define MREC (1 << 26)

typedef unsigned long long ullg;

static ullg nrs[MAXN];
static ullg ways[MREC];
static ullg possib;

static void
add_cnts (int by, int mx)
{
  int i;

  for (i = mx; i >= by; i--)
    ways[i] += ways[i - by];
}

static int
cmpull (const void *a, const void *b)
{
  ullg aa = *(ullg *) a;
  ullg bb = *(ullg *) b;

  if (aa < bb)
    return -1;
  if (aa > bb)
    return 1;

  return 0;
}

static void
accum_possib (int f, int till, int mx, ullg reval)
{
  if (f < till)
    {
      if (reval <= mx)
	possib += ways[reval];
      else
	possib += ways[mx];

      return;
    }
  if (reval >= nrs[f])
    accum_possib (f - 1, till, mx, reval - nrs[f]);
  accum_possib (f - 1, till, mx, reval);
}

int main (void)
{
  int i, n, k;
  ullg m, mx, nmx;

  scanf ("%d%llu", &n, &m);

  k = 0;
  for (i = 0; i < n; i++)
    {
      scanf ("%llu", &nrs[k]);
      if (nrs[k] <= m)
	k++;
    }
  n = k;

  qsort (nrs, n, sizeof (ullg), cmpull);
  mx = 0;
  ways[0] = 1;
  for (i = 0; i < n; i++)
    {
      nmx = mx + nrs[i];
      if (nmx > m)
      	nmx = m;

      if (nmx >= MREC)
	break;

      mx = nmx;
      add_cnts (nrs[i], mx);
    }
  k = i;

  for (i = 1; i <= mx; i++)
    ways[i] += ways[i - 1];

  accum_possib (n - 1, k, mx, m);
  printf ("%llu\n", possib);

  return 0;
}
