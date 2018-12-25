/* Slow solution to the task Treasure hunt
 * Author: Jakub Radoszewski
 * Date: 10.06.2011
 * Time complexity: O(#calls^2).
 * Description: the explicit nodes are renumbered. Apart from that,
 * naive LCA algorithm is used.
 */


#include <utility>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

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

/* real_depth includes implicit nodes, depth considers only explicit nodes. */
int real_depth[2 * MAX_CALLS], depth[2 * MAX_CALLS];

/* Explicit parent for an explicit node. */
ancestor parent[2 * MAX_CALLS];

/* If v is the upper end of an edge, attached[v] is the node to which
 * it is directly attached. Otherwise attached[v].node == -1. */
node attached[2 * MAX_CALLS];

/* If expl_anc contains a pair (y, x) then x is the explicit ancestor of
 * all the nodes x..y.
 * Initially the vector contains sentinel pairs (0, 0) and (1, 1). */
vector<pair<int, int> > expl_anc;


/*****************************************************************************/
/* Simple utility functions */


/* From a renumbered node to the real node value. */
int real_node(int a)
{
  return expl_anc[a].second;
}

int get_real_depth(node a)
{
  return real_depth[a.expl] + a.dist;
}

node get_node(int a)
{
  node v;
  v.expl = lower_bound(expl_anc.begin(), expl_anc.end(), make_pair(a, -1)) - expl_anc.begin();
  v.dist = a - real_node(v.expl);
  return v;
}



/*****************************************************************************/
/* Important utility functions */


/* Auxiliary function, only on explicit nodes. */
node go_up(int a, int h)
{
  /* Finding the highest explicit node located at most h units above a. */
  while (a != 1 && parent[a].dist <= h)
  {
    h -= parent[a].dist;
    a = parent[a].node;
  }

  /* The final touch: finding the potentially implicit node. */
  node b;
  if (!h)
  {
    b.expl = a;
    b.dist = 0;
    return b;
  }
  node p = attached[a];
  if (p.expl == -1) /* a is the lower end of its edge */
  {
    b.expl = parent[a].node;
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
    node b = a;
    b.dist = a.dist - h;
    return b;
  }
  return go_up(a.expl, h - a.dist);
}

/* Advances h explicit edges up, starting from the node a.
 * Brute force. */
int go_up_real(int a, int h)
{
  if (h)
    while (a != 1 && h--)
      a = parent[a].node;
  return a;
}

/* O(log(n)) time */
node lca(node a, node b)
{
  /* Equalizing depths */
  int da = depth[a.expl], db = depth[b.expl];
  if (da < db || da == db && a.dist < b.dist)
  {
    swap(a, b);
    swap(da, db);
  }
  if (a.expl == b.expl)
    return b;
  a.dist = 0;
  if (da > db)
  {
    a.expl = go_up_real(a.expl, da - db - 1);
    if (parent[a.expl].node == b.expl)
    {
      node c = attached[a.expl];
      if (c.expl == -1)
        c = b;
      if (c.dist <= b.dist)
        return c;
      else
        return b;
    }
    a.expl = parent[a.expl].node;
  }
  b.dist = 0;

  /* Finding LCA */
  while (parent[a.expl].node != parent[b.expl].node)
  {
    a.expl = parent[a.expl].node;
    b.expl = parent[b.expl].node;
  }

  node p = attached[a.expl], q = attached[b.expl];
  node res;
  if (p.expl == -1 || q.expl == -1)
  {
    res = p;
    if (res.expl == -1)
      res = q;
    if (res.expl == -1)
    {
      res.expl = parent[a.expl].node;
      res.dist = 0;
    }
  } else
  {
    res.expl = parent[a.expl].node;
    res.dist = min(p.dist, q.dist);
  }
  return res;
}




/*****************************************************************************/

void init()
{
  real_depth[0] = depth[0] = -1;
  real_depth[1] = depth[1] = 0;
  ancestor a;
  a.node = 1;
  a.dist = 0;
  parent[1] = a;
  expl_anc.push_back(make_pair(0, 0));
  expl_anc.push_back(make_pair(1, 1));
  curr = 2;
}


/*****************************************************************************/

void path(int a, int l)
{
  node v = get_node(a);
  int real_start = curr, real_end = curr + l - 1;
  int start = int(expl_anc.size()), end = start;
  if (real_start != real_end)
    end++;

  real_depth[start] = real_depth[v.expl] + v.dist + 1;
  depth[start] = depth[v.expl] + 1;
  if (start != end)
  {
    real_depth[end] = real_depth[start] + l - 1;
    depth[end] = depth[start] + 1;
  }
  ancestor x;
  x.node = v.expl;
  x.dist = v.dist + 1;
  parent[start] = x;
  if (start != end)
  {
    x.node = start;
    x.dist = l - 1;
    parent[end] = x;
  }
  attached[start] = v;
  if (start != end)
    attached[end].expl = -1;
  if (start != end)
    expl_anc.push_back(make_pair(real_end - 1, real_start));
  expl_anc.push_back(make_pair(real_end, real_end));
  curr = real_end + 1;
}


/*****************************************************************************/

int dig(int a, int b)
{
  node na = get_node(a), nb = get_node(b);
  node v = lca(na, nb);
  int da = real_depth[na.expl] + na.dist;
  int db = real_depth[nb.expl] + nb.dist;
  int dv = real_depth[v.expl] + v.dist;

  int len = da + db - 2 * dv;
  int pos = len / 2;
  node res;
  if (pos <= da - dv)
    res = go_up(na, pos);
  else
    res = go_up(nb, len - pos);
  return real_node(res.expl) + res.dist;
}
