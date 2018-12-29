/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LIS (Listonosz)                                *
 *   Plik:                lisb2.c                                        *
 *   Autor:               Jakub Pawlewicz                                *
 *   Opis:                Rozwiazanie b³êdne.                            *
 *                                                                       *
 *************************************************************************/

using namespace std;

#include <vector>
#include <stack>

int n;
int m;

vector< vector<int> > node;
vector<vector<int>::const_iterator> cur_edge;
vector<int> path;
stack<int> visited;

bool read_streets_and_check_euler_condition()
{
  scanf("%d%d", &n, &m);
  node = vector< vector<int> >(n);
  vector<int> incount(n, 0), outcount(n, 0);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    node[a].push_back(b);
    incount[b]++;
    outcount[a]++;
  }
  for (int i = 0; i < n; i++)
    if (incount[i] != outcount[i])
      return false;
  return true;
}

bool try_move_from(int a)
{
  vector<int>::const_iterator& i = cur_edge[a];
  if (i == node[a].end())
    return false;
  visited.push(*i);
  i++;
  return true;
}

bool try_find_euler_cycle()
{
  cur_edge = vector<vector<int>::const_iterator>(n);
  for (int i = 0; i < n; i++)
    cur_edge[i] = node[i].begin();
  visited.push(0);
  while (!visited.empty()) {
    int a = visited.top();
    if (!try_move_from(a)) {
      path.push_back(a);
      visited.pop();
    }
  }
  return (int) path.size() == m + 1;
}

void print_path()
{
  for (vector<int>::reverse_iterator i = path.rbegin();
       i != path.rend(); i++)
    printf("%d\n", *i + 1);
}

int main()
{
  bool found = false;
  if (read_streets_and_check_euler_condition()) {
    if (try_find_euler_cycle())
      found = true;
  }
  if (found) {
    printf("TAK\n");
    print_path();
  } else
    printf("NIE\n");
  return 0;
}
