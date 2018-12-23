/* Similar to medium, vertices processed in a random order.  */

#include <stdio.h>
#include <stdlib.h>

struct e
{
  int to;
  struct e *next, *prev, *opp;
};

static int n;
static int amark;
static struct vertex
{
  struct e ns;
  int target, dist, mark;
  struct e *from;
} *gr;
static int *queue;
static int qb, ql;

static struct e *
add_half (int x, int y)
{
  struct e *nw = malloc (sizeof (struct e));
  nw->to = y;
  nw->next = gr[x].ns.next;
  nw->prev = &gr[x].ns;
  nw->next->prev = nw;
  nw->prev->next = nw;
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
tgt_nbrs_of (int v, int t)
{
  struct e *ae;

  for (ae = gr[v].ns.next; ae->to != -1; ae = ae->next)
    gr[ae->to].target = t;
  gr[v].target = t;
}

static int
find_nontrivial_path (int f, int *tgt)
{
  amark++;
  qb = 0;
  ql = 1;
  queue[0] = f;
  gr[f].from = NULL;
  gr[f].dist = 0;
  gr[f].mark = amark;

  while (ql)
    {
      int v = queue[qb++];
      struct e *ae;
      ql--;

      for (ae = gr[v].ns.next; ae->to != -1; ae = ae->next)
	{
	  if (gr[ae->to].mark == amark)
	    continue;

	  gr[ae->to].mark = amark;
	  gr[ae->to].from = ae->opp;
	  gr[ae->to].dist = gr[v].dist + 1;

	  if (gr[ae->to].target)
	    {
	      if (gr[ae->to].dist > 1)
		{
		  *tgt = ae->to;
		  return 1;
		}
	    }
	  else
	    {
	      queue[qb + ql] = ae->to;
	      ql++;
	    }
	}
    }

  return 0;
}

static void
print_path (int v)
{
  for (; gr[v].from != NULL; v = gr[v].from->to)
    printf (" %d", v + 1);
  printf (" %d\n", v + 1);
}

int main (void)
{
  int m, i, x, y;
  struct e *ae;
  int *order;

  scanf ("%d %d", &n, &m);
  gr = malloc (n * sizeof (struct vertex));
  queue = malloc (n * sizeof (int));
  for (i = 0; i < n; i++)
    {
      gr[i].ns.to = -1;
      gr[i].ns.prev = gr[i].ns.next = gr[i].ns.opp = &gr[i].ns;
      gr[i].target = gr[i].dist = gr[i].mark = 0;
      gr[i].from = NULL;
    }

  for (i = 0; i < m; i++)
    {
      scanf ("%d %d", &x, &y);
      add_edge (x - 1, y - 1);
    }

  order = malloc (n * sizeof (int));
  srand (0);
  for (i = 0; i < n; i++)
    order[i] = i;
  for (i = 0; i < n; i++)
    {
      int sw, t;

      sw = i + rand () % (n - i);
      t = order[sw];
      order[sw] = order[i];
      order[i] = t;
    }

  for (i = 0; i < n; i++)
    {
      tgt_nbrs_of (order[i], 1);
      for (ae = gr[order[i]].ns.next; ae->to != -1; ae = ae->next)
	if (find_nontrivial_path (ae->to, &x))
	  {
	    printf ("%d", order[i] + 1);
	    print_path (x);
	    return 0;
	  }
      tgt_nbrs_of (order[i], 0);
    }
  printf ("no\n");

  return 0;
}

