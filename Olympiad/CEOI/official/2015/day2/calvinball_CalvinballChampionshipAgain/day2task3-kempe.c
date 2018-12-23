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
static int kill[MAXN][MAXC];
static int n, totc, rep;

static int
first_available (int v)
{
  int i;

  for (i = 0; i < totc; i++)
    if (kill[v][i] == 0)
     return i;

  return -1;
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

static int chain[2][MAXN];
static int nchain[2];
static int seen[MAXN];

static void
find_chain_rec (int v, int c1, int c2, int mark)
{
  struct edge *e;

  if (seen[v] == mark)
    return;

  if (color[v] == c1)
    chain[0][nchain[0]++] = v;
  else if (color[v] == c2)
    chain[1][nchain[1]++] = v;
  else
    return;

  seen[v] = mark;

  for (e = ns[v]; e; e = e->next)
    find_chain_rec (e->to, c1, c2, mark);
}

static void
find_chain (int v, int c1, int c2)
{
  static int amark;

  amark++;
  nchain[0] = nchain[1] = 0;

  find_chain_rec (v, c1, c2, amark);
}

static void
kempe_from (int w)
{
  int c1, c2, i;

  c1 = color[w];
  c2 = rand () % (totc - 1);
  if (c2 == c1)
    c2++;

  find_chain (w, c1, c2);

  for (i = 0; i < nchain[0]; i++)
    set_color (chain[0][i], c2);
  for (i = 0; i < nchain[1]; i++)
    set_color (chain[1][i], c1);
}

static void
kempe_at (int v)
{
  int ncn = 0;
  struct edge *e;

  for (e = ns[v]; e; e = e->next)
    if (color[e->to] != -1)
      ncn++;
  ncn = rand () % ncn;

  for (e = ns[v]; e; e = e->next)
    if (color[e->to] != -1)
      {
	if (ncn == 0)
	  break;
	ncn--;
      }

  kempe_from (e->to);
}

static int
random_colored_vertex (void)
{
  while (1)
    {
      int v = rand () % n;

      if (color[v] != -1)
	return v;
    }
}

int main (int argc, char *argv[])
{
  int m, i, j, k, f, t, c;

  srand (0);
  totc = atoi (argv[1]);
  rep = atoi (argv[2]);
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

  c = 0;
  for (i = 0; i < n; i++)
    {
      k = smallest_avail ();
      
      for (j = 0; j < rep; j++)
	{
	  c = first_available (k);
	  if (c != -1)
	    break;

	  kempe_at (k);
	  c = first_available (k);
	  if (c != -1)
	    break;
	  kempe_from (random_colored_vertex ());
	}


      if (c == -1)
	abort ();
      set_color (k, c);
    }

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

