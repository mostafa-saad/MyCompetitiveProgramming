#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

static char adj[MAXN][MAXN];
struct vertex;

struct edge
{
  struct vertex *to;
  struct edge *next, *prev, *opp;
};

static int n;

struct vertex
{
  int id;
  struct edge ns;
};

struct graph
{
  int nv;
  struct vertex **vs;
};

static void
link (struct edge *e, struct vertex *at)
{
  e->next = at->ns.next;
  e->prev = &at->ns;
  e->next->prev = e;
  e->prev->next = e;
}

static struct edge *
add_half (struct vertex *x, struct vertex *y)
{
  struct edge *nw = malloc (sizeof (struct edge));
  nw->to = y;
  link (nw, x);
  return nw;
}

static void
add_edge (struct vertex *x, struct vertex *y)
{
  struct edge *e1 = add_half (x, y);
  struct edge *e2 = add_half (y, x);
  e1->opp = e2;
  e2->opp = e1;
}

static void
init_graph (struct graph *g, int nv)
{
  int i;

  g->nv = nv;
  g->vs = malloc (n * sizeof (struct vertex *));
  for (i = 0; i < n; i++)
    {
      g->vs[i] = malloc (sizeof (struct vertex));
      g->vs[i]->ns.to = NULL;
      g->vs[i]->ns.opp = NULL;
      g->vs[i]->ns.prev = g->vs[i]->ns.next = &g->vs[i]->ns;
      g->vs[i]->id = i;
    }
}


int main (void)
{
  int m, i, x, y;
  struct graph g;
  struct edge *e, *e1, *e2;

  scanf ("%d %d", &n, &m);
  init_graph (&g, n);
  for (i = 0; i < m; i++)
    {
      scanf ("%d %d", &x, &y);
      add_edge (g.vs[x - 1], g.vs[y - 1]);
      adj[x - 1][y - 1] = adj[y - 1][x - 1] = 1;
    }

  for (i = 0; i < n; i++)
    for (e = g.vs[i]->ns.next; e->to; e = e->next)
      {
	if (e->to->id < i)
	  continue;

	for (e1 = e->to->ns.next; e1->to; e1 = e1->next)
	  {
	    if (e1->to->id <= i || adj[i][e1->to->id])
	      continue;

	    for (e2 = e1->to->ns.next; e2->to; e2 = e2->next)
	      if (e2->to != e->to
		  && !adj[e2->to->id][e->to->id]
		  && adj[e2->to->id][i])
		{
		  printf ("%d %d %d %d\n", i + 1, e->to->id + 1, e1->to->id + 1, e2->to->id + 1);
		  return 0;
		}
	  }
      }

  printf ("no\n");

  return 0;
}

