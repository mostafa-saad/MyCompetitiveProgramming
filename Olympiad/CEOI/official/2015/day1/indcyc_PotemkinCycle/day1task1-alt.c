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
  int id, pos, vis, tgt;
  int deg, ntriang;
  struct edge ns;
  struct vertex *fr;
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

static void
unlink (struct edge *e)
{
  e->next->prev = e->prev;
  e->prev->next = e->next;
  e->prev = e->next = NULL;
}

static struct edge *
add_half (struct vertex *x, struct vertex *y)
{
  struct edge *nw = malloc (sizeof (struct edge));
  nw->to = y;
  link (nw, x);
  x->deg++;
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
      g->vs[i]->id = g->vs[i]->pos = i;
      g->vs[i]->ntriang = 0;
      g->vs[i]->deg = 0;
    }
}

static void
delete_vertex (struct graph *g, struct vertex *v, int update_tr)
{
  struct vertex *r;

  if (update_tr)
    {
      struct edge *e1, *e2;

      for (e1 = v->ns.next; e1->to; e1 = e1->next)
	for (e2 = e1->next; e2->to; e2 = e2->next)
	  if (adj[e1->to->id][e2->to->id])
	    {
	      e1->to->ntriang--;
	      e2->to->ntriang--;
	    }
    }

  while (v->ns.next->to)
    {
      struct edge *e = v->ns.next;

      e->to->deg--;
      unlink (e);
      unlink (e->opp);
      free (e->opp);
      free (e);
    }

  r = g->vs[g->nv - 1];
  g->vs[v->pos] = r;
  r->pos = v->pos;
  free (v);

  g->nv--;
}

static int
print_nontrivial_path (struct graph *g, struct vertex *f)
{
  struct vertex **queue = malloc (g->nv * sizeof (struct vertex *));
  int qb = 0, ql = 1, i;
  struct edge *e;
  struct vertex *v;

  for (i = 0; i < g->nv; i++)
    g->vs[i]->vis = -1;
  queue[0] = f;
  f->vis = 0;
  f->fr = NULL;

  while (ql)
    {
      v = queue[qb];
      qb++;
      ql--;

      if (v->tgt && v->vis > 0)
	{
	  if (v->vis > 1)
	    {
	      for (; v != NULL; v = v->fr)
		printf (" %d", v->id + 1);
	      free (queue);
	      return 1;
	    }

	  continue;
	}

      for (e = v->ns.next; e->to; e = e->next)
	if (e->to->vis == -1)
	  {
	    e->to->vis = v->vis + 1;
	    e->to->fr = v;
	    queue[qb + ql++] = e->to;
	  }
    }

  free (queue);
  return 0;
}

static int
is_simplicial (struct vertex *v)
{
  int d = v->deg;

  return 2 * v->ntriang == d * (d - 1);
}

static struct vertex *
simplicial_vertex (struct graph *g)
{
  int i;

  for (i = 0; i < g->nv; i++)
    if (is_simplicial (g->vs[i]))
      return g->vs[i];

  return NULL;
}

static int
find_induced_cycle (struct graph *g, struct graph *gc)
{
  struct vertex *v;
  struct edge *e;
  int i, n = g->nv;
  int sgvs[MAXN];
  struct vertex *to_del[MAXN];
  int tested_id = -1, ndel = 0;

  for (i = 0; i < g->nv; i++)
    sgvs[i] = 2;

  while (1)
    {
      while ((v = simplicial_vertex (g)) != NULL)
	{
	  sgvs[v->id] = 1;
	  delete_vertex (g, v, 1);
	}

      if (g->nv <= 3)
	break;

      for (i = 0; i < n; i++)
	if (sgvs[i] == 1)
	  sgvs[i] = 0;

      v = g->vs[0];
      tested_id = v->id;

      sgvs[v->id] = 0;
      delete_vertex (g, v, 1);
    }

  if (tested_id < 0)
    return 0;

  for (i = 0; i < gc->nv; i++)
    {
      if (gc->vs[i]->id == tested_id)
	v = gc->vs[i];
      else if (sgvs[gc->vs[i]->id] == 0)
	to_del[ndel++] = gc->vs[i];
    }
  for (i = 0; i < ndel; i++)
    delete_vertex (gc, to_del[i], 0);

  for (i = 0; i < gc->nv; i++)
    gc->vs[i]->tgt = 0;
  for (e = v->ns.next; e->to; e = e->next)
    e->to->tgt = 1;
  delete_vertex (gc, v, 0);

  printf ("%d", tested_id + 1);
  for (i = 0; i < gc->nv; i++)
    if (gc->vs[i]->tgt
	&& print_nontrivial_path (gc, gc->vs[i]))
      break;
  printf ("\n");

  return 1;
}

static void
count_triangles (struct graph *g)
{
  int i;
  struct vertex *v;
  struct edge *e1, *e2;

  for (i = 0; i < g->nv; i++)
    {
      v = g->vs[i];

      for (e1 = v->ns.next; e1->to; e1 = e1->next)
	if (v->id < e1->to->id)
	  for (e2 = e1->next; e2->to; e2 = e2->next)
	    if (v->id < e2->to->id
		&& adj[e1->to->id][e2->to->id])
	      {
		v->ntriang++;
		e1->to->ntriang++;
		e2->to->ntriang++;
	      }
    }
}

int main (void)
{
  int m, i, x, y;
  struct graph g, gc;

  scanf ("%d %d", &n, &m);
  init_graph (&g, n);
  init_graph (&gc, n);
  for (i = 0; i < m; i++)
    {
      scanf ("%d %d", &x, &y);
      add_edge (g.vs[x - 1], g.vs[y - 1]);
      add_edge (gc.vs[x - 1], gc.vs[y - 1]);
      adj[x - 1][y - 1] = adj[y - 1][x - 1] = 1;
    }

  count_triangles (&g);

  if (!find_induced_cycle (&g, &gc))
    printf ("no\n");

  return 0;
}
