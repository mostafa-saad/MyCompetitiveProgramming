/* Slow solution to the task Treasure hunt
 * Author: Jakub Radoszewski
 * Date: 9.06.2011
 * Time complexity: O((#nodes + #dig) * log(#nodes)).
 * Description: computes LCA in #nodes * log(#nodes) time and space.
 * Constructs the tree explicitly.
 */


#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;


#define LOG_MAX_N 31

/* This node will be created if a path call appears */
int curr;



/*****************************************************************************/
/* Utility functions for handling ancestors and lca's. */

vector<vector<int> > anc;
vector<int> depth;

/* Computes anc[a], starting with anc[a][0] = par. */
inline void compute_anc(int a, int par)
{
  anc[a].push_back(par);
  for (int i = 0; i < LOG_MAX_N; i++)
    anc[a].push_back(anc[anc[a][i]][i]);
}

/* Advances h edges up, starting from the node a. */
inline int go_up(int a, int h)
{
  for (int i = 0; i < LOG_MAX_N; i++)
    if (h & (1 << i))
      a = anc[a][i];
  return a;
}

inline int lca(int a, int b)
{
  /* Equalizing depths */
  if (depth[a] < depth[b])
    swap(a, b);
  a = go_up(a, depth[a] - depth[b]);
  if (a == b)
    return a;

  /* Finding LCA */
  int i = 0;
  while (anc[a][i] != anc[b][i])
    i++;
  for (int j = i - 1; j >= 0; j--)
    if (anc[a][j] != anc[b][j])
    {
      a = anc[a][j];
      b = anc[b][j];
    }
  return anc[a][0];
}




/*****************************************************************************/

void init()
{
  depth.push_back(-1); /* node 0 */
  depth.push_back(0); /* node 1 */
  anc.resize(2, vector<int>());
  for (int i = 0; i < LOG_MAX_N; i++)
    anc[1].push_back(1); /* sentinel */
  curr = 2;
}


/*****************************************************************************/

void path(int a, int s)
{
  int prev = a;
  for (int i = 0; i < s; i++)
  {
    depth.push_back(depth[prev] + 1);
    anc.push_back(vector<int>());
    compute_anc(curr, prev);
    prev = curr;
    curr++;
  }
}


/*****************************************************************************/

int dig(int a, int b)
{
  int v = lca(a, b);
  int len = depth[a] + depth[b] - 2 * depth[v];
  int pos = len / 2;
  if (pos <= depth[a] - depth[v])
    return go_up(a, pos);
  else
    return go_up(b, len - pos);
}
