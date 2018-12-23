#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MAXM 20000000

static int es[MAXM][2];
static int nlist[2 * MAXM];
static int n, m;
static int deg[MAXN];
static int *ns[MAXN];

static int color[MAXN];

static void
assign_colors (int v, int c)
{
  int i;

  if (color[v])
    {
      if (color[v] != c)
	abort ();

      return;
    }

  color[v] = c;
  for (i = 0; i < deg[v]; i++)
    assign_colors (ns[v][i], 3 - c);
}

int main (void)
{
  int i, x, y, nc, c;

  scanf ("%d%d", &n, &m);
  for (i = 0; i < m; i++)
    {
      scanf ("%d%d", &x, &y);
      x--; y--;

      deg[x]++;
      deg[y]++;
      es[i][0] = x;
      es[i][1] = y;
    }
  ns[0] = nlist;
  for (i = 1; i < n; i++)
    ns[i] = ns[i - 1] + deg[i - 1];
  for (i = 0; i < m; i++)
    {
      x = es[i][0];
      y = es[i][1];
      *(ns[x]++) = y;
      *(ns[y]++) = x;
    }
  for (i = 0; i < n; i++)
    ns[i] -= deg[i];

  for (i = 0; i < n; i++)
    if (!color[i])
      assign_colors (i, 1);

  nc = 2;
  printf ("%d\n", nc);
  for (c = 1; c <= nc; c++)
    {
      const char *sep = "";

      for (i = 0; i < n; i++)
	if (color[i] == c)
	  {
	    printf ("%s%d", sep, i + 1);
	    sep = " ";
	  }
      printf ("\n");
    }

  return 0;
}

