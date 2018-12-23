/* Model solution to the task Treasure hunt
 * Author: Jakub Radoszewski
 * Date: 10.06.2011
 * Time complexity: O(#calls * log(#calls)).
 * Description: the explicit nodes are renumbered.
 */


#define MAX_CALLS 400000
#define LOG_2_MAX_CALLS 20

/* This node will be created if a path call appears */
int curr;



/*****************************************************************************/
/* Data structures */


/* An (implicit or explicit) node located dist units below the explicit node
 * expl. */
typedef struct
{
  int expl, dist;
} node;

typedef struct
{
  int node, dist;
} ancestor;

/* The ancestors of the nodes (anc[v][i] is the ancestor 2^i edges above)
 * and their depths. */
ancestor anc[2 * MAX_CALLS][LOG_2_MAX_CALLS];

/* depth includes implicit nodes, real_depth considers only explicit nodes. */
int depth[2 * MAX_CALLS], real_depth[2 * MAX_CALLS];

/* If v is the upper end of an edge, attached[v] is the node to which
 * it is directly attached. Otherwise attached[v].node == -1. */
node attached[2 * MAX_CALLS];

typedef struct
{
  int first, second;
} pair;

/* If expl_anc contains a pair (y, x) then x is the explicit ancestor of
 * all the nodes x..y.
 * Initially the vector contains sentinel pairs (0, 0) and (1, 1). */
pair expl_anc[2 * MAX_CALLS];
int expl_anc_size;


/*****************************************************************************/
/* Simple utility functions */


pair make_pair(int a, int b)
{
  pair p;
  p.first = a;
  p.second = b;
  return p;
}

/* From a renumbered node to the real node value. */
int real_node(int a)
{
  return expl_anc[a].second;
}

int get_depth(node a)
{
  return depth[a.expl] + a.dist;
}

node get_node(int a)
{
  node v;
  int l, h;
  l = 0;
  h = expl_anc_size - 1;
  while (l < h)
  {
    int c;
    c = (l + h) / 2;
    if (expl_anc[c].first < a)
      l = c + 1;
    else
      h = c;
  }
  v.expl = l;
  v.dist = a - real_node(v.expl);
  return v;
}



/*****************************************************************************/
/* Important utility functions */

/* Computes anc[a], starting with anc[a][0] = par. */
void compute_anc(int a, int par, int len)
{
  ancestor v;
  int i;
  v.node = par;
  v.dist = len;
  anc[a][0] = v;
  for (i = 0; i < LOG_2_MAX_CALLS; i++)
  {
    v.node = anc[anc[a][i].node][i].node;
    v.dist = anc[a][i].dist + anc[anc[a][i].node][i].dist;
    anc[a][i + 1] = v;
  }
}


/* Auxiliary function, only on explicit nodes. */
node go_up_aux(int a, int h)
{
  /* Finding the highest explicit node located at most h units above a. */
  int i = 0;
  node b, p;
  while (i + 1 < LOG_2_MAX_CALLS && anc[a][i + 1].dist <= h)
    i++;
  while (i >= 0)
  {
    ancestor p;
    p = anc[a][i];
    if (p.dist <= h)
    {
      h -= p.dist;
      a = p.node;
    }
    i--;
  }

  /* The final touch: finding the potentially implicit node. */
  if (!h)
  {
    b.expl = a;
    b.dist = 0;
    return b;
  }
  p = attached[a];
  if (p.expl == -1) /* a is the lower end of its edge */
  {
    b.expl = anc[a][0].node;
    b.dist = (real_node(a) - real_node(b.expl)) - h;
  } else /* a is the upper end of its edge */
  {
    h--;
    b.expl = p.expl;
    b.dist = p.dist - h;
  }
  return b;
}

/* Advances the distance h up, starting from the node a. */
node go_up(node a, int h)
{
  if (h <= a.dist)
  {
    node b;
    b = a;
    b.dist = a.dist - h;
    return b;
  }
  return go_up_aux(a.expl, h - a.dist);
}

/* Advances h explicit edges up, starting from the node a. */
int go_up_real(int a, int h)
{
  int i;
  i = 0;
  while ((1 << (i + 1)) <= h)
    i++;
  while (h)
  {
    if ((1 << i) <= h)
    {
      a = anc[a][i].node;
      h -= (1 << i);
    }
    i--;
  }
  return a;
}

/* O(log(n)) time */
node lca(node a, node b)
{
  int da, db, i;
  node p, q, res;

  /* Equalizing depths */
  da = real_depth[a.expl]; db = real_depth[b.expl];
  if (da < db || (da == db && a.dist < b.dist))
  {
    p = a; a = b; b = p;
    i = da; da = db; db = i;
  }
  if (a.expl == b.expl)
    return b;
  a.dist = 0;
  if (da > db)
  {
    a.expl = go_up_real(a.expl, da - db - 1);
    if (anc[a.expl][0].node == b.expl)
    {
      node c = attached[a.expl];
      if (c.expl == -1)
        c = b;
      if (c.dist <= b.dist)
        return c;
      else
        return b;
    }
    a.expl = anc[a.expl][0].node;
  }
  b.dist = 0;

  /* Finding LCA */
  i = 0;
  while (anc[a.expl][i].node != anc[b.expl][i].node)
    i++;
  i--;
  while (i >= 0)
  {
    a.expl = anc[a.expl][i].node;
    b.expl = anc[b.expl][i].node;
    while (i >= 0 && anc[a.expl][i].node == anc[b.expl][i].node)
      i--;
  }

  p = attached[a.expl];
  q = attached[b.expl];
  if (p.expl == -1 || q.expl == -1)
  {
    res = p;
    if (res.expl == -1)
      res = q;
    if (res.expl == -1)
    {
      res.expl = anc[a.expl][0].node;
      res.dist = 0;
    }
  } else
  {
    res.expl = anc[a.expl][0].node;
    res.dist = p.dist;
    if (q.dist < p.dist)
      res.dist = q.dist;
  }
  return res;
}




/*****************************************************************************/

void init()
{
  ancestor a;
  int i;

  depth[0] = real_depth[0] = -1;
  depth[1] = real_depth[1] = 0;
  a.node = 1;
  a.dist = 0;
  for (i = 0; i < LOG_2_MAX_CALLS; i++)
    anc[1][i] = a; /* sentinel */
  expl_anc[expl_anc_size++] = make_pair(0, 0);
  expl_anc[expl_anc_size++] = make_pair(1, 1);
  curr = 2;
}


/*****************************************************************************/

void path(int a, int s)
{
  int real_start, real_end, start, end;
  node v;

  v = get_node(a);
  real_start = curr;
  real_end = curr + s - 1;
  start = expl_anc_size;
  end = start;
  if (real_start != real_end)
    end++;

  depth[start] = depth[v.expl] + v.dist + 1;
  real_depth[start] = real_depth[v.expl] + 1;
  if (start != end)
  {
    depth[end] = depth[start] + s - 1;
    real_depth[end] = real_depth[start] + 1;
  }
  compute_anc(start, v.expl, v.dist + 1);
  if (start != end)
    compute_anc(end, start, s - 1);
  attached[start] = v;
  if (start != end)
    attached[end].expl = -1;
  if (start != end)
    expl_anc[expl_anc_size++] = make_pair(real_end - 1, real_start);
  expl_anc[expl_anc_size++] = make_pair(real_end, real_end);
  curr = real_end + 1;
}


/*****************************************************************************/

int dig(int a, int b)
{
  node na, nb, v, res;
  int da, db, dv, len, pos;

  na = get_node(a);
  nb = get_node(b);
  v = lca(na, nb);
  da = depth[na.expl] + na.dist;
  db = depth[nb.expl] + nb.dist;
  dv = depth[v.expl] + v.dist;

  len = da + db - 2 * dv;
  pos = len / 2;
  if (pos <= da - dv)
    res = go_up(na, pos);
  else
    res = go_up(nb, len - pos);
  return real_node(res.expl) + res.dist;
}
