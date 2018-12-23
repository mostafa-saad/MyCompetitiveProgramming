#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

static int adj[MAXN][MAXN];

struct e
{
  int to;
  struct e *next, *prev, *opp;
};

static int n;
static struct vertex
{
  struct e ns;
  int vis;
} gr[MAXN];

static void
unlink (struct e *e)
{
  e->next->prev = e->prev;
  e->prev->next = e->next;
  e->prev = e->next = NULL;
}

static struct e *
add_half (int x, int y)
{
  struct e *nw = malloc (sizeof (struct e));
  nw->to = y;
  nw->next = gr[x].ns.next;
  nw->prev = &gr[x].ns;
  nw->next->prev = nw;
  nw->prev->next = nw;
  adj[x][y] = 1;
  return nw;
}

static void
add_edge (int x, int y)
{
  struct e *e1 = add_half (x, y);
  struct e *e2 = add_half (y, x);
  e1->opp = e2;
  e2->opp = e1;
}

static void
delete_incident_edges (int v)
{
  while (1)
    {
      struct e *ie = gr[v].ns.next;

      if (ie->to == -1)
	break;

      unlink (ie->opp);
      free (ie->opp);
      unlink (ie);
      free (ie);
    }
}

static int
valid_visited_nbrs (int a, int b, int fr, int alen)
{
  struct e *e;

  for (e = gr[a].ns.next; e->to != -1; e = e->next)
    {
      if (e->to == b)
	continue;

      if (e->to == fr)
	{
	  if (alen == 2)
	    return 0;
	  continue;
	}

      if (gr[e->to].vis)
	return 0;
    }

  return 1;
}

static int
find_ind_cyc_1 (int a, int fr, int alen)
{
  struct e *e;

  if (alen > 2)
    for (e = gr[a].ns.next; e->to != -1; e = e->next)
      if (e->to == fr)
	{
	  printf ("%d ", a + 1);
	  return 1;
	}

  gr[a].vis = 1;
  for (e = gr[a].ns.next; e->to != -1; e = e->next)
    if (!gr[e->to].vis
	&& valid_visited_nbrs (e->to, a, fr, alen + 1)
	&& find_ind_cyc_1 (e->to, fr, alen + 1))
      {
	printf ("%d ", a + 1);
	gr[a].vis = 0;
	return 1;
      }

  gr[a].vis = 0;
  return 0;
}

static int
find_ind_cyc (int from)
{
  int ret = 0;
  struct e *e;

  gr[from].vis = 1;
  for (e = gr[from].ns.next; e->to != -1; e = e->next)
    if (find_ind_cyc_1 (e->to, from, 1))
      {
	ret = 1;
	printf ("%d\n", from + 1);
	break;
      }

  gr[from].vis = 0;
  return ret;
}

int main (void)
{
  int m, i, x, y;

  scanf ("%d %d", &n, &m);
  for (i = 0; i < n; i++)
    {
      gr[i].ns.to = -1;
      gr[i].ns.prev = gr[i].ns.next = gr[i].ns.opp = &gr[i].ns;
    }

  for (i = 0; i < m; i++)
    {
      scanf ("%d %d", &x, &y);
      add_edge (x - 1, y - 1);
    }

  for (; n > 3; n--)
    {
      if (find_ind_cyc (n - 1))
	return 0;

      delete_incident_edges (n - 1);
    }

  printf ("no\n");

  return 0;
}
