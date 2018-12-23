#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

struct edge
{
  int to;
  struct edge *next;
};

static struct edge *ns[MAXN];
static int color[MAXN];

static int perm[MAXN];

static int
first_available (int v, int c)
{
  int av[c];
  int i;
  struct edge *e;

  for (i = 0; i < c; i++)
    av[i] = 1;

  for (e = ns[v]; e; e = e->next)
    if (color[e->to] != -1)
      av[color[e->to]] = 0;

  for (i = 0; i < c; i++)
    if (av[i])
      return i;
  return c;
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
  int n, m, i, k, f, t, c = 0;

  scanf ("%d%d", &n, &m);

  for (i = 0; i < n; i++)
    {
      perm[i] = i;
      color[i] = -1;
    }

  if (argc > 1)
    {
      for (i = 0; i < n; i++)
	perm[i] = n - i - 1;
      if (argv[1][0] == 'x')
	{
	  srand (0);
	  for (i = 0; i < n; i++)
	    {
	      int w = i + rand () % (n - i);
	      int p = perm[i];
	      perm[i] = perm[w];
	      perm[w] = p;
	    }
	}
    }


  for (i = 0; i < m; i++)
    {
      scanf ("%d%d", &f, &t);
      f--;
      t--;
      adde (f, t);
    }

  for (i = 0; i < n; i++)
    {
      int pi = perm[i];
      color[pi] = first_available (pi, c);
      if (color[pi] >= c)
	c = color[pi] + 1;
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
