#include <stdio.h>

#define MAXN 100000
#define MAXM 20000000

static int es[MAXM][2];
static int nlist[2 * MAXM];
static int n, m;
static int deg[MAXN];
static int *ns[MAXN];

static int chosen[MAXN];
static int order[MAXN];
static int effdeg[MAXN];
static int color[MAXN];

static int
min_unchosen (void)
{
  int md = n, mv = -1;
  int i;

  for (i = 0; i < n; i++)
    {
      if (chosen[i] || effdeg[i] >= md)
	continue;

      md = effdeg[i];
      mv = i;
    }

  return mv;
}

static int
min_available_color (int v, int anc)
{
  int us[anc + 1];
  int i;

  for (i = 0; i <= anc; i++)
    us[i] = 0;

  for (i = 0; i < deg[v]; i++)
    us[color[ns[v][i]]]++;

  for (i = 1; i <= anc; i++)
    if (!us[i])
      return i;

  return anc + 1;
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
    effdeg[i] = deg[i];
  for (i = 0; i < n; i++)
    {
      x = min_unchosen ();
      chosen[x] = 1;
      order[n - 1 - i] = x;

      for (y = 0; y < deg[x]; y++)
	effdeg[ns[x][y]]--;
    }

  nc = 0;
  for (i = 0; i < n; i++)
    {
      c = min_available_color (order[i], nc);
      color[order[i]] = c;
      if (c > nc)
	nc = c;
    }

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

