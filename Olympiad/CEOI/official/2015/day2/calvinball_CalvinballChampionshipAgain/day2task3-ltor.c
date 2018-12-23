#include <stdio.h>

#define MAXN 10000
#define MAXM 40000
#define MAXP 5000
#define MAXD 8 

static int es[MAXM][2];
static int nlist[2 * MAXM];
static int n, m;
static int deg[MAXN];
static int *ns[MAXN];

static int part[MAXP][MAXD];
static int max_part_no[MAXP];
static int npart;

static char col_needed[MAXN][MAXP];
static char copy_delta[MAXN][MAXP];
static short prev_part[MAXN][MAXP];

static int parts[MAXN];
static int colors[MAXN];

static int
proper (int fv, int v, int c, int col[])
{
  int i, u;

  for (i = 0; i < deg[v]; i++)
    {
      u = ns[v][i];
      if (u > v || u < fv)
	continue;

      if (c == col[u - fv])
	return 0;
    }

  return 1;
}

static int
all_proper (int fv, int col[], int k)
{
  int v;

  for (v = fv + 1; v < fv + k; v++)
    if (!proper (fv, v, col[v - fv], col))
      return 0;

  return 1;
}

static int nused[MAXD + 1];

static int
find_distinct_color (void)
{
  int i;

  for (i = 0; nused[i]; i++)
    continue;

  return i;
}

static void
gen_parts (int ap[], int k, int mpno, int len)
{
  int i;

  if (k == len)
    {
      for (i = 0; i < len; i++)
	part[npart][i] = ap[i];
      max_part_no[npart] = mpno;
      npart++;

      return;
    }

  for (i = 0; i < mpno; i++)
    {
      ap[k] = i;
      gen_parts (ap, k + 1, mpno, len);
    }

  ap[k] = mpno;
  gen_parts (ap, k + 1, mpno + 1, len);
}

static void
canon_part (int p[], int mdelta)
{
  int trto[MAXP + 1];
  int i, am = 0;

  for (i = 0; i <= MAXP; i++)
    trto[i] = -1;

  for (i = 0; i < mdelta; i++)
    {
      int a = p[i];

      if (trto[a] != -1)
	p[i] = trto[a];
      else
	p[i] = trto[a] = am++;
    }
}

static int
cmp_parts (int p1[], int p2[], int mdelta)
{
  int i;

  for (i = 0; i < mdelta; i++)
    if (p1[i] != p2[i])
      break;

  if (i == mdelta)
    return 0;

  if (p1[i] < p2[i])
    return -1;
  else
    return 1;
}

static int
find_part (int p[], int mdelta)
{
  int l = 0, h = npart;

  while (1)
    {
      int m = (l + h) / 2;
      int c = cmp_parts (p, part[m], mdelta);

      if (c == 0)
	return m;

      if (c < 0)
	h = m;
      else
	l = m + 1;
    }
}

static void
extend_colorings (int v, int mdelta)
{
  int p, np, c, i, cd;
  int nw[MAXP], cn;

  for (p = 0; p < npart; p++)
    col_needed[v][p] = -1;

  for (p = 0; p < npart; p++)
    {
      if (col_needed[v - 1][p] == -1)
	continue;
      for (c = 0; c <= max_part_no[p]; c++)
	{
	  if (!proper (v - mdelta, v, c, part[p]))
	    continue;

	  cd = c == 0 ? mdelta : 0;
	  for (i = 0; i < mdelta - 1; i++)
	    {
	      nw[i] = part[p][i + 1];
	      if (nw[i] == c)
		cd = mdelta - 1 - i;
	    }
	  nw[mdelta - 1] = c;

	  canon_part (nw, mdelta);
	  np = find_part (nw, mdelta);

	  cn = col_needed[v - 1][p];
	  if (cd == 0 && max_part_no[p] == col_needed[v - 1][p])
	    cn++;

	  if (col_needed[v][np] >= 0 && col_needed[v][np] <= cn)
	    continue;

	  prev_part[v][np] = p;
	  copy_delta[v][np] = cd;
	  col_needed[v][np] = cn;
	}
    }
}

int main (void)
{
  int i, x, y, mdelta = 0, d, nc, ep, c;
  int apart[MAXD];

  scanf ("%d%d", &n, &m);
  for (i = 0; i < m; i++)
    {
      scanf ("%d%d", &x, &y);
      x--; y--;

      deg[x]++;
      deg[y]++;
      es[i][0] = x;
      es[i][1] = y;

      d = x - y;
      if (d < 0)
	d = -d;
      if (d > mdelta)
	mdelta = d;
    }
  ns[0] = nlist;
  for (i = 1; i < n; i++)
    ns[i] = ns[i - 1] + deg[i - 1];
  for (i = 0; i < m; i++)
    {
      x = es[i][0];
      y = es[i][1];
      *(ns[x]++) = y;
      *(ns[y]++) = x;
    }
  for (i = 0; i < n; i++)
    ns[i] -= deg[i];

  gen_parts (apart, 0, 0, mdelta);

  for (i = 0; i < npart; i++)
    if (all_proper (0, part[i], mdelta))
      col_needed[mdelta - 1][i] = max_part_no[i];
    else
      col_needed[mdelta - 1][i] = -1;

  for (i = mdelta; i < n; i++)
    {
      if (i % 100 == 0)
	{
	  fprintf (stderr, "#");
	  fflush (stderr);
	}
      extend_colorings (i, mdelta);
    }

  nc = n + 1; ep = -1;
  for (i = 0; i < npart; i++)
    if (col_needed[n - 1][i] >= 0 && col_needed[n - 1][i] < nc)
      {
	nc = col_needed[n - 1][i];
	ep = i;
      }
  printf ("%d\n", nc);

  parts[n - 1] = ep;
  for (i = n - 2; i >= mdelta - 1; i--)
    parts[i] = prev_part[i + 1][parts[i + 1]];

  for (i = 0; i < mdelta; i++)
    {
      colors[i] = part[parts[mdelta - 1]][i];
      nused[colors[i]]++;
    }
  for (; i < n; i++)
    {
      int delta = copy_delta[i][parts[i]];

      if (delta == 0)
	colors[i] = find_distinct_color ();
      else
	colors[i] = colors[i - delta];
      nused[colors[i]]++;
      nused[colors[i - mdelta]]--;
    }

  for (c = 0; c < nc; c++)
    {
      const char *sep = "";

      for (i = 0; i < n; i++)
	if (colors[i] == c)
	  {
	    printf ("%s%d", sep, i + 1);
	    sep = " ";
	  }

      printf ("\n");
    }

  return 0;
}
