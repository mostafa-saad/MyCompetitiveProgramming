/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LIS (Listonosz)                                *
 *   Plik:                liss1.c                                        *
 *   Autor:               Jakub Pawlewicz                                *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                                                                       *
 *************************************************************************/

using namespace std;

#include <map>
#include <vector>
#include <set>
#include <stack>

int n;
int m;

vector< vector<int> > node;

struct edge {
  int a, b;
  edge(int a, int b) : a(a), b(b) { }
};

bool operator<(const edge &e1, const edge &e2)
{
  if (e1.a == e2.a)
    return e1.b < e2.b;
  else
    return e1.a < e2.a;
}

bool operator==(const edge &e1, const edge &e2)
{
  return e1.a == e2.a && e1.b == e2.b;
}

bool operator!=(const edge &e1, const edge &e2)
{
  return !(e1 == e2);
}

map<edge, int> prev;
map<edge, int> next;

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

bool try_read_and_process_seq()
{
  int k;
  scanf("%d", &k);
  int a, b;
  scanf("%d%d", &a, &b);
  a--; b--;
  for (k -= 2; k; k--) {
    int c;
    scanf("%d", &c);
    c--;
    pair<map<edge,int>::iterator,bool> i;
    i = next.insert(map<edge,int>::value_type(edge(a, b), c));
    if (!i.second && i.first->second != c)
        return false;
    i = prev.insert(map<edge,int>::value_type(edge(b, c), a));
    if (!i.second && i.first->second != a)
        return false;
    a = b;
    b = c;
  }
  return true;
}

bool try_read_and_process_seqs()
{
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++)
    if (!try_read_and_process_seq())
      return false;
  return true;
}

bool try_go_edge(edge e)
{
  map<edge,int>::const_iterator i;
  i = prev.find(e);
  if (i != prev.end())
    return false;
  set<edge> seq;
  for (;;) {
    if (!seq.insert(e).second)
      return false;
    i = next.find(e);
    if (i == next.end())
      break;
    visited.push(e.b + n);
    e.a = e.b;
    e.b = i->second;
  }
  visited.push(e.b);
  return true;
}

bool try_move_from(int a)
{
  vector<int>::const_iterator& i = cur_edge[a];
  int b;
  while (i != node[a].end()) {
    b = *i;
    i++;
    if (try_go_edge(edge(a, b)))
      return true;
  }
  return false;
}

bool try_find_euler_cycle()
{
  cur_edge = vector<vector<int>::const_iterator>(n);
  for (int i = 0; i < n; i++)
    cur_edge[i] = node[i].begin();
  visited.push(0);
  while (!visited.empty()) {
    int a = visited.top();
    if (a >= n) {
      path.push_back(a - n);
      visited.pop();
    } else {
      if (!try_move_from(a)) {
        path.push_back(a);
        visited.pop();
      }
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
    if (try_read_and_process_seqs()) {
      if (try_find_euler_cycle())
        found = true;
    }
  }
  if (found) {
    printf("TAK\n");
    print_path();
  } else
    printf("NIE\n");
  return 0;
}
