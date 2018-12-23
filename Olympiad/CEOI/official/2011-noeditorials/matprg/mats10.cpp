/* Veryfing solution for the task MAT (Matching)
 * Author: Jakub Radoszewski
 * Date: July 2011
 * Time complexity: O(nlogn + m)
 */

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

#define MAX 1000000
#define INFTY 100000000

/* p1 is the original pattern from the problem statement, while
 * p is given from left to right, like the text t. */
int n, m;
int p1[MAX + 1], p[MAX + 1], t[MAX + 1];

void read()
{
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
  {
    cin >> p1[i];
  }
  for (int i = 1; i <= n; i++)
    p[p1[i]] = i;
  for (int i = 1; i <= m; i++)
    cin >> t[i];
}


/* Segment trees, efficient implementation. */
pair<int, int> min_tree[1 << 21], max_tree[1 << 21];
int size;

void init_trees()
{
  size = 1;
  while (size <= n)
    size *= 2;
  for (int i = 0; i <= 2 * size - 1; i++)
  {
    min_tree[i] = make_pair(INFTY, -1);
    max_tree[i] = make_pair(-1, -1);
  }
}

int max_query(int v)
{
  int ind = size + v;
  pair<int, int> res = make_pair(-1, -1);
  while (ind != 1)
  {
    if (ind % 2 == 1 && max_tree[ind - 1].first > res.first)
      res = max_tree[ind - 1];
    ind /= 2;
  }
  return res.second;
}

int min_query(int v)
{
  int ind = size + v;
  pair<int, int> res = make_pair(INFTY, -1);
  while (ind != 1)
  {
    if (ind % 2 == 0 && min_tree[ind + 1].first < res.first)
      res = min_tree[ind + 1];
    ind /= 2;
  }
  return res.second;
}

void min_insert(pair<int, int> p)
{
  int ind = size + p.first;
  min_tree[ind] = p;
  while (ind != 1)
  {
    ind /= 2;
    if (p.first < min_tree[ind].first)
      min_tree[ind] = p;
  }
}

void max_insert(pair<int, int> p)
{
  int ind = size + p.first;
  max_tree[ind] = p;
  while (ind != 1)
  {
    ind /= 2;
    if (p.first > max_tree[ind].first)
      max_tree[ind] = p;
  }
}


int g[MAX + 1], h[MAX + 1];

/* Computes the g and h functions, as defined in the solution description,
 * using a segment tree. */
void compute_gh()
{
  init_trees();
  for (int i = 1; i <= n; i++)
  {
    g[i] = max_query(p[i]);
    h[i] = min_query(p[i]);
    min_insert(make_pair(p[i], i));
    max_insert(make_pair(p[i], i));
  }
}


int f[MAX + 1];

inline bool matches(int pos, int pos2)
{
  if (g[pos] != -1 && p[pos2] <= p[pos2 - (pos - g[pos])])
    return false;
  if (h[pos] != -1 && p[pos2] >= p[pos2 - (pos - h[pos])])
    return false;
  return true;
}

inline bool matches_t(int pos, int pos2)
{
  if (g[pos] != -1 && t[pos2] <= t[pos2 - (pos - g[pos])])
    return false;
  if (h[pos] != -1 && t[pos2] >= t[pos2 - (pos - h[pos])])
    return false;
  return true;
}

/* Computes the failure function of the pattern. */
void compute_f()
{
  f[0] = f[1] = 0;
  int last = 0;
  for (int i = 2; i <= n; i++)
  {
    f[i] = last;
    while (last && !matches(last + 1, i))
      last = f[last];
    if (matches(last + 1, i))
      last++;
    f[i] = last;
  }
}


vector<int> result;

void matching()
{
  int last = 0;
  for (int i = 1; i <= m; i++)
  {
    while (last && !matches_t(last + 1, i))
      last = f[last];
    if (matches_t(last + 1, i))
      last++;
    if (last == n)
    {
      result.push_back(i - n + 1);
      last = f[last];
    }
  }
}

void write()
{
  cout << result.size() << endl;
  for (int i = 0; i < (int)result.size(); i++)
  {
    cout << result[i];
    if (i < (int)result.size() - 1)
      cout << " ";
  }
  cout << endl;
}

int main()
{
  ios_base::sync_with_stdio(0);
  read();
  compute_gh();
  compute_f();
  matching();
  write();
  return 0;
}
