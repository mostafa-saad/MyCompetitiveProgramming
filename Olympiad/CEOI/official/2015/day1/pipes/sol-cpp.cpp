#include <stdio.h>

#define MAXM 300000
#define MAXN 100000

enum {
  REDUNDANT,
  BRIDGE,
  NEEDED,
};

static struct edge
{
  int u, v;
  int state;
} es[MAXM];
static int nes;

static struct edge *ns[2 * MAXM];
static int elb[MAXN + 2];
static int level[MAXN];
static enum {UNVISITED, OPEN, CLOSED} state[MAXN];

static int component[MAXN];
static int acomp;
static int comp_stack[MAXN];
static int csn;

static int
other_end (struct edge *e, int x)
{
  return e->u == x ? e->v : e->u;
}

static struct
{
  int v, pos, lev_back;
  struct edge *best_back;
} stack[MAXN];
static int st_top;

static void
dfs (int v)
{
  level[v] = 0;
  state[v] = OPEN;
  stack[0].v = v;
  stack[0].pos = elb[v];
  stack[0].lev_back = 0;
  stack[0].best_back = NULL;
  st_top = 1;

  comp_stack[0] = v;
  csn = 1;

  while (st_top)
    {
      int u, p, lb, w;
      struct edge *bb, *from, *e;
      
      u = stack[st_top - 1].v;
      p = stack[st_top - 1].pos;
      lb = stack[st_top - 1].lev_back;
      bb = stack[st_top - 1].best_back;
      from = st_top > 1 ? ns[stack[st_top - 2].pos - 1] : NULL;

      if (p == elb[u + 1])
	{
	  st_top--;
	  state[u] = CLOSED;

	  if (bb)
	    {
	      from->state = NEEDED;
	      bb->state = NEEDED;

	      if (stack[st_top - 1].lev_back > lb)
		{
		  stack[st_top - 1].lev_back = lb;
		  stack[st_top - 1].best_back = bb;
		}
	    }
	  else
	    {
	      do
		{
		  w = comp_stack[--csn];
		  component[w] = acomp;
		} while (w != u);
	      acomp++;
	    }
	  continue;
	}

      stack[st_top - 1].pos++;
      e = ns[p];
      if (e == from)
	continue;
      w = other_end (e, u);

      if (state[w] == CLOSED)
	continue;

      if (state[w] == OPEN)
	{
	  if (level[w] < lb)
	    {
	      stack[st_top - 1].lev_back = level[w];
	      stack[st_top - 1].best_back = e;
	    }

	  continue;
	}

      state[w] = OPEN;
      level[w] = level[u] + 1;
      stack[st_top].v = w;
      stack[st_top].pos = elb[w];
      stack[st_top].lev_back = level[w];
      stack[st_top].best_back = NULL;
      e->state = BRIDGE;
      st_top++;

      comp_stack[csn++] = w;
    }
}

static void
classify_edges (int n)
{
  int i;

  for (i = 0; i < n + 2; i++)
    elb[i] = 0;

  for (i = 0; i < nes; i++)
    {
      es[i].state = REDUNDANT;
      elb[es[i].u + 2]++;
      elb[es[i].v + 2]++;
    }
  for (i = 3; i < n + 2; i++)
    elb[i] += elb[i - 1];

  for (i = 0; i < nes; i++)
    {
      ns[elb[es[i].u + 1]++] = es + i;
      ns[elb[es[i].v + 1]++] = es + i;
    }

  for (i = 0; i < n; i++)
    state[i] = UNVISITED;

  acomp = 0;
  for (i = 0; i < n; i++)
    if (state[i] == UNVISITED)
      dfs (i);
}

int main (void)
{
  int n, m, i, j, k;

  scanf ("%d%d", &n, &m);

  for (i = 0; i < n; i++)
    component[i] = i;

  for (i = 0; i < m; i++)
    {
      int u, v;
      scanf ("%d%d", &u, &v);

      if (component[u - 1] == component[v - 1])
	continue;

      es[nes].u = u - 1;
      es[nes].v = v - 1;
      nes++;

      if (nes == 3 * n)
	{
	  classify_edges (n);
	  k = 0;

	  for (j = 0; j < nes; j++)
	    if (es[j].state != REDUNDANT)
	      es[k++] = es[j];
	  nes = k;
	}
    }
  classify_edges (n);
  for (j = 0; j < nes; j++)
    if (es[j].state == BRIDGE)
      printf ("%d %d\n", es[j].u + 1, es[j].v + 1);

  return 0;
}
