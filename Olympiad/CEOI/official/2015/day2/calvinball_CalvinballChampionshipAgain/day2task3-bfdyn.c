#include <stdio.h>
#include <stdlib.h>

#define MAXN 28
#define MAXS 10000

typedef unsigned set;
static set indsets[MAXS];
static int nind;

static inline int
elem (set s, int e)
{
  return (s >> e) & 1;
}

static void
print_set (set s)
{
  int i;
  const char *sep = "";

  for (i = 0; s != 0; s >>= 1, i++)
    if (s & 1)
      {
	printf ("%s%d", sep, i + 1);
	sep = " ";
      }
  printf ("\n");
}

static int gr[MAXN][MAXN];
static int n;
static char chrom[1 << MAXN];
static set colclass[1 << MAXN];

static int
determine_chrom (set s)
{
  int i, c = n + 1;
  set best;

  if (chrom[s] >= 0)
    return chrom[s];

  for (i = 0; i < nind; i++)
    if ((s & indsets[i]) != 0)
      {
	int ac = determine_chrom (s & ~indsets[i]);
	if (ac < c)
	  {
	    c = ac;
	    best = s & indsets[i];
	  }
      }

  chrom[s] = c + 1;
  colclass[s] = best;

  return c + 1;
}

static int
any_nbr (int v, set s)
{
  int u;

  for (u = 0; u < n; u++)
    if (elem (s, u) && gr[u][v])
      return 1;

  return 0;
}

static int
is_maximal_independent (set s)
{
  int v;

  for (v = 0; v < n; v++)
    if (elem (s, v) == any_nbr (v, s))
      return 0;

  return 1;
}

int main (void)
{
  int m, i, x, y, c;
  set s;

  scanf ("%d%d", &n, &m);
  for (i = 0; i < m; i++)
    {
      scanf ("%d%d", &x, &y);
      gr[x - 1][y - 1] = gr[y - 1][x - 1] = 1;
    }

  for (s = 0; s < (1 << n); s++)
    {
      chrom[s] = -1;
      if (is_maximal_independent (s))
	{
	  if (nind >= MAXS)
	    abort ();
	  indsets[nind++] = s;
	}
    }

  chrom[0] = 0;
  c = determine_chrom ((1 << n) - 1);
  printf ("%d\n", c);
  for (s = (1 << n) - 1; s; s &= ~colclass[s])
    print_set (colclass[s]);

  return 0;
}
