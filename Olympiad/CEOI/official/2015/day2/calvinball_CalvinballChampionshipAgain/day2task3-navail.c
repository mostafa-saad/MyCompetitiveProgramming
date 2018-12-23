#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MAXC 20

struct edge
{
  int to;
  struct edge *next;
};

static struct edge *ns[MAXN];
static int color[MAXN];
static int navail[MAXN];
static int avail[MAXN][MAXC];
static int n;

static int
first_available (int v)
{
  int i;

  for (i = 0; i < MAXC; i++)
    if (avail[v][i])
     return i;

  abort ();
}

static int
smallest_avail (void)
{
  int v;
  int mav = MAXC + 1, bv = -1;

  for (v = 0; v < n; v++)
    {
      if (color[v] != -1)
	continue;

      if (navail[v] < mav)
	{
	  mav = navail[v];
	  bv = v;
	}
    }

  return bv;
}

static void
prune_neighbors (int v, int c)
{
  struct edge *e;

  for (e = ns[v]; e; e = e->next)
    if (avail[e->to][c])
      {
	avail[e->to][c] = 0;
	navail[e->to]--;
      }
}

static void
addhe (int f, int t)
{
  struct edge *e = malloc (sizeof (struct edge));

  e->to = t;
  e->next = ns[f];
  ns[f] = e;
}

static void
adde (int f, int t)
{
  addhe (f, t);
  addhe (t, f);
}

int main (int argc, char *argv[])
{
  int m, i, k, f, t, c;

  scanf ("%d%d", &n, &m);

  for (i = 0; i < n; i++)
    {
      color[i] = -1;
      navail[i] = MAXC;
      for (c = 0; c < MAXC; c++)
	avail[i][c] = 1;
    }

  for (i = 0; i < m; i++)
    {
      scanf ("%d%d", &f, &t);
      f--;
      t--;
      adde (f, t);
    }

  c = 0;
  for (i = 0; i < n; i++)
    {
      k = smallest_avail ();
      color[k] = first_available (k);
      prune_neighbors (k, color[k]);
      if (color[k] >= c)
	c = color[k] + 1;
    }

  printf ("%d\n", c);
  for (k = 0; k < c; k++)
    {
      for (i = 0; i < n; i++)
	if (color[i] == k)
	  printf ("%d ", i + 1);
      printf ("\n");
    }

  return 0;
}

