/* Slow solution to the task Treasure hunt
 * Author: Jakub Radoszewski
 * Date: 9.06.2011
 * Time complexity: O(#calls * log^3(#calls + #nodes)).
 * Description: a log^2 solution with too many maps.
 */


#include <utility>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;


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

inline bool operator==(const node &a, const node &b)
{
  return a.expl == b.expl && a.dist == b.dist;
}

/* anc[v][i] = the ancestor of the node v located 2^i edges upwards. */
typedef struct
{
  int node, dist;
} ancestor;

/* The ancestors of the nodes (anc[v][i] is the ancestor 2^i edges above)
 * and their depths. */
map<int, vector<ancestor> > anc;
map<int, int> depth;

/* If v is the upper end of an edge, attached[v] is the node to which
 * it is directly attached. Otherwise attached[v].node == -1. */
map<int, node> attached;

/* If expl_anc contains a pair (y, x) then x is the explicit ancestor of
 * all the nodes x..y.
 * Initially the set contains a sentinel pair (1, 1). */
set<pair<int, int> > expl_anc;


/*****************************************************************************/
/* Simple utility functions */


inline int get_depth(const node &a)
{
  return depth[a.expl] + a.dist;
}

inline node get_node(int a)
{
  node v;
  v.expl = expl_anc.lower_bound(make_pair(a, -1))->second;
  v.dist = a - v.expl;
  return v;
}


/*****************************************************************************/
/* Important utility functions */


/* Computes anc[a], starting with anc[a][0] = par. */
inline void compute_anc(int a, int par, int len)
{
  ancestor v;
  v.node = par;
  v.dist = len;
  anc[a].push_back(v);
  for (int i = 0; i < LOG_2_MAX_CALLS; i++)
  {
    v.node = anc[anc[a][i].node][i].node;
    v.dist = anc[a][i].dist + anc[anc[a][i].node][i].dist;
    anc[a].push_back(v);
  }
}


/* Auxiliary function, only on explicit nodes. */
inline node go_up(int a, int h)
{
  /* Finding the highest explicit node located at most h units above a. */
  vector<ancestor> &t = anc[a];
  int i = 0;
  while (i + 1 < (int)t.size() && t[i + 1].dist <= h)
    i++;
  while (i >= 0)
  {
    ancestor &p = anc[a][i];
    if (p.dist <= h)
    {
      h -= p.dist;
      a = p.node;
    }
    i--;
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
    b.expl = anc[a][0].node;
    b.dist = (a - b.expl) - h;
  } else /* a is the upper end of its edge */
  {
    h--;
    b.expl = p.expl;
    b.dist = p.dist - h;
  }
  return b;
}

/* Advances the distance h up, starting from the node a. */
inline node go_up(node a, int h)
{
  if (h <= a.dist)
  {
    node b = a;
    b.dist = a.dist - h;
    return b;
  }
  return go_up(a.expl, h - a.dist);
}

inline node lca(node a, node b)
{
  /* Equalizing depths */
  int da = get_depth(a), db = get_depth(b);
  if (da < db)
  {
    swap(a, b);
    swap(da, db);
  }
  a = go_up(a, da - db);
  if (a == b)
    return a;

  /* Finding LCA */
  int lo = 1, hi = db;
  while (lo < hi)
  {
    int med = (lo + hi) / 2;
    if (go_up(a, med) == go_up(b, med))
      hi = med;
    else
      lo = med + 1;
  }
  return go_up(a, lo);
}




/*****************************************************************************/

void init()
{
  depth[1] = 0;
  ancestor a;
  a.node = 1;
  a.dist = 0;
  for (int i = 0; i < LOG_2_MAX_CALLS; i++)
    anc[1].push_back(a); /* sentinel */
  expl_anc.insert(make_pair(1, 1));
  curr = 2;
}


/*****************************************************************************/

void path(int a, int s)
{
  node v = get_node(a);
  int start = curr, end = curr + s - 1;
  depth[start] = depth[v.expl] + v.dist + 1;
  depth[end] = depth[start] + s - 1;
  compute_anc(start, v.expl, v.dist + 1);
  if (start != end)
    compute_anc(end, start, s - 1);
  attached[start] = v;
  if (start != end)
    attached[end].expl = -1;
  if (start != end)
    expl_anc.insert(make_pair(end - 1, start));
  expl_anc.insert(make_pair(end, end));
  curr = end + 1;
}


/*****************************************************************************/

int dig(int a, int b)
{
  node na = get_node(a), nb = get_node(b);
  node v = lca(na, nb);
  int da = depth[na.expl] + na.dist;
  int db = depth[nb.expl] + nb.dist;
  int dv = depth[v.expl] + v.dist;

  int len = da  + db - 2 * dv;
  int pos = len / 2;
  node res;
  if (pos <= da - dv)
    res = go_up(na, pos);
  else
    res = go_up(nb, len - pos);
  return res.expl + res.dist;
}
