#include <stdio.h>

#define MAXN 24
#define MAXSS 100000

static struct
{
  int *wh;
  int orig;
} undo_stack[MAXSS];
static int undo_top;

static void
set_with_undo (int *wh, int co)
{
  undo_stack[undo_top].wh = wh;
  undo_stack[undo_top].orig = *wh;
  *wh = co;
  undo_top++;
}

static void
undo_till (int u)
{
  while (undo_top > u)
    {
      undo_top--;
      *(undo_stack[undo_top].wh) = undo_stack[undo_top].orig;
    }
}


static int gr[MAXN][MAXN];
static int killed[MAXN][MAXN];
static int nkill[MAXN];
static int n;
static int maxc;

static void
kill_at_nbrs (int v, int c)
{
  int u;

  for (u = 0; u < n; u++)
    if (gr[u][v] && !killed[u][c])
      {
	set_with_undo (&killed[u][c], 1);
	set_with_undo (&nkill[u], nkill[u] + 1);
      }
}

static int
best_coloring (int pcol[], int bcol[])
{
  int v, bv = -1, mc = -1, c, cbest = n + 1, a;
  int until = undo_top;
  int best[MAXN];
  int mtry;

  for (v = 0; v < n; v++)
    {
      if (pcol[v] == -1
  	  && (bv == -1
  	      || nkill[bv] < nkill[v]))
    	bv = v;

      if (pcol[v] > mc)
	mc = pcol[v];

      bcol[v] = pcol[v];
    }

  if (bv == -1)
    return mc + 1;

  mtry = mc + 1;
  if (mtry > maxc)
    mtry = maxc;

  for (c = 0; c <= mtry; c++)
    if (!killed[bv][c])
      {
	pcol[bv] = c;
	kill_at_nbrs (bv, c);
	a = best_coloring (pcol, best);
	if (a < cbest)
	  {
	    cbest = a;
	    for (v = 0; v < n; v++)
	      bcol[v] = best[v];
	  }
	undo_till (until);
      }

  pcol[bv] = -1;
  return cbest;
}

int main (void)
{
  int m, i, x, y, c, cused;
  int col[MAXN], bcol[MAXN];

  scanf ("%d%d", &n, &m);
  for (i = 0; i < m; i++)
    {
      scanf ("%d%d", &x, &y);
      gr[x - 1][y - 1] = gr[y - 1][x - 1] = 1;
    }

  for (i = 0; i < n; i++)
    col[i] = -1;

  maxc = 0;
  while ((cused = best_coloring (col, bcol)) == n + 1)
    maxc++;

  printf ("%d\n", cused);
  for (c = 0; c < cused; c++)
    {
      const char *sep = "";

      for (x = 0; x < n; x++)
	if (bcol[x] == c)
	  {
	    printf ("%s%d", sep, x + 1);
	    sep = " ";
	  }

      printf ("\n");
    }

  return 0;
}
