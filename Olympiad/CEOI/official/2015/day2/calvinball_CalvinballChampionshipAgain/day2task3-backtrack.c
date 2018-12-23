#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
static int kill[MAXN][MAXC];
static int n, totc;

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
uncolor (int v)
{
  struct edge *e;
  int c = color[v];

  color[v] = -1;

  for (e = ns[v]; e; e = e->next)
    {
      kill[e->to][c]--;
      if (kill[e->to][c] == 0)
	navail[e->to]++;
    }
}

static void
set_color (int v, int c)
{
  struct edge *e;

  if (color[v] != -1)
    uncolor (v);

  color[v] = c;

  for (e = ns[v]; e; e = e->next)
    {
      if (kill[e->to][c] == 0)
	navail[e->to]--;
      kill[e->to][c]++;
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

static int
try_extend (void)
{
  int v = smallest_avail ();
  int c;

  if (v == -1)
    return 1;

  if (navail[v] == 0)
    return 0;

  for (c = 0; c < totc; c++)
    if (kill[v][c] == 0)
      {
	set_color (v, c);
	if (try_extend ())
	  return 1;
      }
  uncolor (v);

  return 0;
}

static int
adjacent (int u, int v)
{
  struct edge *e;
  for (e = ns[v]; e; e = e->next)
    if (e->to == u)
      return 1;

  return 0;
}

static int
adjacent_to_all (int s, int clique[], int v)
{
  int i;

  for (i = 0; i < s; i++)
    if (!adjacent (clique[i], v))
      return 0;

  return 1;
}

static int
find_clique_rec (int s, int clique[], int after)
{
  struct edge *e;
  int v = clique[0], best = s, a;
  int acl[MAXC];

  if (s > totc)
    return s;

  memcpy (acl, clique, s * sizeof (int));

  for (e = ns[v]; e; e = e->next)
    if (e->to > after && adjacent_to_all (s, clique, e->to))
      {
	acl[s] = e->to;
	a = find_clique_rec (s + 1, acl, e->to);

	if (a > best)
	  {
	    memcpy (clique, acl, a * sizeof (int));
	    best = a;
	  }
      }

  return best;
}

static int
find_clique (int clique[])
{
  int v, best = 0, s;
  int acl[MAXC];

  for (v = 0; v < n; v++)
    {
      acl[0] = v;
      s = find_clique_rec (1, acl, v);
      if (s > best)
	{
	  memcpy (clique, acl, s * sizeof (int));
	  best = s;
	}
    }

  return best;
}

int main (int argc, char *argv[])
{
  int m, i, k, f, t, c;
  int clique[MAXC], cs;

  totc = atoi (argv[1]);
  scanf ("%d%d", &n, &m);

  for (i = 0; i < n; i++)
    {
      color[i] = -1;
      navail[i] = totc;
      for (c = 0; c < totc; c++)
	kill[i][c] = 0;
    }

  for (i = 0; i < m; i++)
    {
      scanf ("%d%d", &f, &t);
      f--;
      t--;
      adde (f, t);
    }

  cs = find_clique (clique);
  if (cs > totc)
    abort ();

  for (i = 0; i < cs; i++)
    set_color (clique[i], i);

  if (!try_extend ())
    abort ();

  printf ("%d\n", totc);
  for (k = 0; k < totc; k++)
    {
      for (i = 0; i < n; i++)
	if (color[i] == k)
	  printf ("%d ", i + 1);
      printf ("\n");
    }

  return 0;
}

