/* Slow solution to the task Treasure hunt
 * Author: Jakub Radoszewski
 * Date: 9.06.2011
 * Time complexity: O(#nodes * #dig).
 * Description: in the call path(a,b) we traverse the tree upwards from a and b.
 */


#include <utility>
#include <vector>
#include <algorithm>

using namespace std;


/* This node will be created if a path call appears */
int curr;
vector<int> depth, parent;

/*****************************************************************************/

void init()
{
  parent.resize(2, -1);
  depth.push_back(-1); /* node 0 */
  depth.push_back(0); /* node 1 */
  curr = 2;
}


/*****************************************************************************/

void path(int a, int s)
{
  int prev = a;
  for (int i = 0; i < s; i++)
  {
    parent.push_back(prev);
    depth.push_back(depth[prev] + 1);
    prev = curr;
    curr++;
  }
}


/*****************************************************************************/

int dig(int a, int b)
{
  vector<int> pa, pb; /* the parts of the path */
  pa.push_back(a);
  pb.push_back(b);

  /* Equalizing the depths */
  while (depth[a] > depth[b])
  {
    a = parent[a];
    pa.push_back(a);
  }
  while (depth[b] > depth[a])
  {
    b = parent[b];
    pb.push_back(b);
  }

  /* Finding LCA */
  while (a != b)
  {
    a = parent[a];
    b = parent[b];
    pa.push_back(a);
    pb.push_back(b);
  }
  pb.pop_back(); /* removing the duplicate */
  while (!pb.empty())
  {
    pa.push_back(pb.back());
    pb.pop_back();
  }
  return pa[((int)pa.size() - 1) / 2];
}
