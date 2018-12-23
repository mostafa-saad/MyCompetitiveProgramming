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
  int id, compid, pos, clique;
  struct edge ns;
  struct vertex *pair;
};

struct graph
{
  int nv;
  struct vertex **vs;
};

static int mark = -3;

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
      g->vs[i]->clique = g->vs[i]->compid = 0;
      g->vs[i]->pair = NULL;
    }
}

static int
number_component (struct vertex *v, int cn)
{
  struct edge *e;
  int sz = 1;

  v->compid = cn;
  for (e = v->ns.next; e->to; e = e->next)
    {
      if (e->to->compid == -1)
	sz += number_component (e->to, cn);
      else if (e->to->compid != cn && e->to->compid != mark)
	{
	  e->to->compid = mark;
	  sz++;
	}
    }

  return sz;
}

static int
number_nonnbr_components (struct graph *g, struct vertex *cv, int sizes[])
{
  int i, nc = 0;
  struct edge *e;

  for (i = 0; i < g->nv; i++)
    if (g->vs[i]->clique)
      g->vs[i]->compid = -2;
    else
      g->vs[i]->compid = -1;

  cv->compid = -2;
  for (e = cv->ns.next; e->to; e = e->next)
    e->to->compid = -2;

  for (i = 0; i < g->nv; i++)
    if (g->vs[i]->compid == -1)
      {
	sizes[nc] = number_component (g->vs[i], nc);
	nc++;
	mark--;
      }

  return nc;
}

static void
establish_pairs_and_clique (struct vertex *crep, int compid, struct graph *sg, int *apos)
{
  struct vertex *p = sg->vs[*apos];
  struct edge *e;

  (*apos)++;
  crep->pair = p;
  p->pair = crep;
  p->id = crep->id;

  if (crep->compid != compid)
    {
      crep->compid = mark;
      p->clique = 1;
      return;
    }

  crep->compid = mark;
  for (e = crep->ns.next; e->to; e = e->next)
    if (e->to->compid != mark)
      establish_pairs_and_clique (e->to, compid, sg, apos);
}

static void
move_incident_edges (struct vertex *v)
{
  while (v->ns.next->to)
    {
      struct edge *e = v->ns.next;

      unlink (e);
      unlink (e->opp);
      link (e, v->pair);
      link (e->opp, e->to->pair);
      e->to = e->to->pair;
      e->opp->to = v->pair;
    }
}

static void
delete_vertex (struct graph *g, struct vertex *v)
{
  struct vertex *r;

  while (v->ns.next->to)
    {
      struct edge *e = v->ns.next;

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

static struct graph *
separate_component (struct graph *g, struct vertex *crep, int sgnv)
{
  struct graph *nw = malloc (sizeof (struct graph));
  int i, pos = 0;

  init_graph (nw, sgnv);
  establish_pairs_and_clique (crep, crep->compid, nw, &pos);
  mark--;

  for (i = 0; i < sgnv; i++)
    if (!nw->vs[i]->clique)
      {
	move_incident_edges (nw->vs[i]->pair);
	delete_vertex (g, nw->vs[i]->pair);
	nw->vs[i]->pair = NULL;
      }

  return nw;
}

static int
nonclique_attachment (struct graph *sg, struct vertex **x, struct vertex **y)
{
  struct vertex **incl, **outcl;
  int nincl = 0, noutcl = 0;
  int i, j, ret = 0;

  incl = malloc (sg->nv * sizeof (struct vertex *));
  outcl = malloc (sg->nv * sizeof (struct vertex *));
  for (i = 0; i < sg->nv; i++)
    if (sg->vs[i]->clique)
      {
	if (sg->vs[i]->pair->clique)
	  incl[nincl++] = sg->vs[i];
	else
	  outcl[noutcl++] = sg->vs[i];
      }

  for (i = 0; i < nincl; i++)
    for (j = 0; j < noutcl; j++)
      if (!adj[incl[i]->id][outcl[j]->id])
	{
	  *x = incl[i];
	  *y = outcl[j];
	  ret = 1;
	  goto end;
	}
  for (i = 0; i < noutcl; i++)
    for (j = i + 1; j < noutcl; j++)
      if (!adj[outcl[i]->id][outcl[j]->id])
	{
	  *x = outcl[i];
	  *y = outcl[j];
	  ret = 1;
	  goto end;
	}
end:
  free (incl);
  free (outcl);
  return ret;
}

static void
print_shortest_path (struct graph *g, struct vertex *f, struct vertex *t)
{
  struct vertex **queue = malloc (g->nv * sizeof (struct vertex *));
  int qb = 0, ql = 1, i;
  struct edge *e;
  struct vertex *v;

  for (i = 0; i < g->nv; i++)
    g->vs[i]->compid = -1;
  queue[0] = f;
  f->compid = 0;
  f->pair = NULL;

  while (1)
    {
      if (ql == 0)
	abort ();

      v = queue[qb];
      qb++;
      ql--;

      for (e = v->ns.next; e->to; e = e->next)
	if (e->to->compid == -1)
	  {
	    e->to->compid = v->compid + 1;
	    e->to->pair = v;
	    if (e->to == t)
	      {
		v = e->to;
		goto end;
	      }
	    if (e->to->clique)
	      continue;
	    queue[qb + ql++] = e->to;
	  }
    }

end:
  for (v = t; v != NULL; v = v->pair)
    printf (" %d", v->id + 1);

  free (queue);
}

static void
free_graph (struct graph *g)
{
  while (g->nv)
    delete_vertex (g, g->vs[0]);
  free (g->vs);
  free (g);
}

static int
find_induced_cycle (struct graph *g)
{
  int i;
  struct vertex *cv;
  int *sizes = malloc (g->nv * sizeof (int));
  int nc;

  while (g->nv > 3)
    {
      for (i = 0; i < g->nv; i++)
	if (g->vs[i]->clique)
	  break;
      if (i == g->nv)
	i = 0;
      cv = g->vs[i];

      nc = number_nonnbr_components (g, cv, sizes);
      if (nc)
	{
	  struct vertex **crep;
	  struct vertex *x, *y;
	  int lid = -1;

	  crep = malloc (nc * sizeof (struct vertex *));

	  for (i = 0; i < g->nv; i++)
	    if (g->vs[i]->compid > lid)
	      {
		lid++;
		crep[lid] = g->vs[i];
	      }

	  for (i = 0; i < nc; i++)
	    {
	      struct graph *sg = separate_component (g, crep[i], sizes[i]);

	      if (nonclique_attachment (sg, &x, &y))
		{
		  printf ("%d", cv->id + 1);
		  print_shortest_path (sg, x, y);
		  printf ("\n");
		  return 1;
		}
	    
	      if (find_induced_cycle (sg))
	       	return 1;

	      free_graph (sg);
	    }

	  free (crep);
	}

      delete_vertex (g, cv);
    }
  free (sizes);
  return 0;
}

int main (void)
{
  int m, i, x, y;
  struct graph g;

  scanf ("%d %d", &n, &m);
  init_graph (&g, n);
  for (i = 0; i < m; i++)
    {
      scanf ("%d %d", &x, &y);
      add_edge (g.vs[x - 1], g.vs[y - 1]);
      adj[x - 1][y - 1] = adj[y - 1][x - 1] = 1;
    }

  if (!find_induced_cycle (&g))
    printf ("no\n");

  return 0;
}
