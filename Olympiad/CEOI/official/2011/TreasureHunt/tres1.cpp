/* Slow solution to the task Treasure hunt
 * Author: Jakub Radoszewski
 * Date: 9.06.2011
 * Time complexity: O(#nodes * #dig).
 * Description: DFS algorithm.
 */


#include <utility>
#include <vector>
#include <algorithm>

using namespace std;


#define INFTY 100000000

/* This node will be created if a path call appears */
int curr;
vector<vector<int> > edges;

inline void add_edge(int a, int b)
{
  edges[a].push_back(b);
  edges[b].push_back(a);
}


/*****************************************************************************/

void init()
{
  edges.push_back(vector<int>()); /* node 0 */
  edges.push_back(vector<int>()); /* node 1 */
  curr = 2;
}


/*****************************************************************************/

void path(int a, int s)
{
  int pop = a;
  for (int i = 0; i < s; i++)
  {
    edges.push_back(vector<int>()); /* node curr */
    add_edge(curr, pop);
    pop = curr;
    curr++;
  }
}


/*****************************************************************************/

int dig(int a, int b)
{
  vector<int> d, parent;
  d.resize(curr, INFTY);
  parent.resize(curr, -1);

  vector<int> queue;
  d[a] = 0;
  queue.push_back(a);
  for (int i = 0; i < (int)queue.size(); i++)
  {
    int v = queue[i];
    for (int j = 0; j < (int)edges[v].size(); j++)
    {
      int w = edges[v][j];
      if (d[w] == INFTY)
      {
        d[w] = d[v] + 1;
        parent[w] = v;
        queue.push_back(w);
        if (w == b)
        {
          /* recovering the path */
          int len = (d[w] + 1) / 2;
          while (len--)
            w = parent[w];
          return w;
        }
      }
    }
  }
  return -1;
}
