#include <stdio.h>
#include <stdlib.h>

#define MAXH 3500

struct node
{
  unsigned long long coef[2];
};

static int w, h;
static struct node *accumcoefs[MAXH];
static unsigned long long *values[MAXH];
static struct node *coefs;

static void
exch (int *a, int *b, int sw)
{
  int t;

  if (!sw)
    return;

  t = *a;
  *a = *b;
  *b = t;
}

static void
add_to_coefs (struct node *itree, int tof, int tot, unsigned long long toadd[2])
{
  itree[tof].coef[0] += toadd[0];
  itree[tof].coef[1] += toadd[1];
  itree[tot + 1].coef[0] -= toadd[0];
  itree[tot + 1].coef[1] -= toadd[1];
}

static void
extract_coefs (struct node *itree, struct node coefs[])
{
  struct node add = {{0,0}};
  int i;

  for (i = 0; i < w; i++)
    {
      add.coef[0] += itree[i].coef[0];
      add.coef[1] += itree[i].coef[1];
      coefs[i] = add;
    }
}

static void
plant_interval (int x1, int x2, int y, unsigned long long toadd[2])
{
  if (x1 < 0)
    x1 = 0;

  if (x2 >= w)
    x2 = w - 1;

  if (x1 > x2)
    return;

  add_to_coefs (accumcoefs[y], x1, x2, toadd);
}

static void
plant_row (int x, int y, int delta, int rowsz, unsigned long long a, unsigned long long b)
{
  unsigned long long toadd[2];

  toadd[0] = a;
  toadd[1] = 0;
  plant_interval (x - delta, x + delta, y, toadd);

  toadd[0] = a + b * (x + delta);
  toadd[1] = -b;
  plant_interval (x + delta + 1, x + rowsz, y, toadd);

  toadd[0] = a - b * (x - delta);
  toadd[1] = b;
  plant_interval (x - rowsz, x - delta - 1, y, toadd);
}

static void
add_plant (int x, int y, unsigned long long a, unsigned long long b)
{
  int ay, sp = (a - 1) / b;
  long long abv;

  abv = a;
  for (ay = y; ay < h; ay++)
    {
      plant_row (x, ay, ay - y, sp, abv, b);
      if (abv <= b)
	break;
      abv -= b;
    }

  if (a <= b)
    return;

  abv = a - b;
  for (ay = y - 1; ay >= 0; ay--)
    {
      plant_row (x, ay, y - ay, sp, abv, b);
      if (abv <= b)
	break;
      abv -= b;
    }
}

static unsigned long long
get_value (int x, int y, struct node c)
{
  return c.coef[0] + c.coef[1] * x;
}

static unsigned long long
corsum (int x, int y)
{
  if (x < 0 || y < 0)
    return 0;
  return values[y][x];
}

static unsigned long long
get_sum (int x1, int y1, int x2, int y2)
{
  return corsum (x2, y2) - corsum (x1 - 1, y2) - corsum (x2, y1 - 1) + corsum (x1 - 1, y1 - 1);
}

int main (void)
{
  int i, n;
  int swap = 0;
  int x, y, a, b, q;

  scanf ("%d%d", &w, &h);
  if (w < h)
    {
      swap = 1;
      exch (&w, &h, swap);
    }

  for (i = 0; i < h; i++)
    accumcoefs[i] = calloc (w + 1, sizeof (struct node));

  scanf ("%d", &n);
  for (i = 0; i < n; i++)
    {
      scanf ("%d%d%d%d", &x, &y, &a, &b);
      x--; y--;
      exch (&x, &y, swap);
      add_plant (x, y, a, b);
    }

  coefs = malloc (w * sizeof (struct node));
  for (y = 0; y < h; y++)
    {
      values[y] = malloc (w * sizeof (unsigned long long));
      extract_coefs (accumcoefs[y], coefs);

      for (x = 0; x < w; x++)
	{
	  unsigned long long av = get_value (x, y, coefs[x]);

	  unsigned long long psum = corsum (x - 1, y) + corsum (x, y - 1) - corsum (x - 1, y - 1);

	  values[y][x] = psum + av;
	}
    }

  scanf ("%d", &q);
  for (i = 0; i < q; i++)
    {
      int x1, y1, x2, y2;
      unsigned long long s, ar;

      scanf ("%d%d%d%d", &x1, &y1, &x2, &y2);
      x1--; y1--; x2--; y2--;
      exch (&x1, &y1, swap);
      exch (&x2, &y2, swap);
      s = get_sum (x1, y1, x2, y2);
      ar = (unsigned long long) (x2 - x1 + 1) * (y2 - y1 + 1);

      printf ("%llu\n", (s + ar / 2) / ar);
    }

  return 0;
}
