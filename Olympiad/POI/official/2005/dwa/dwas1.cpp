/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DWA (Dwa przyjêcia)                            *
 *   Plik:                dwas1.pas                                      *
 *   Autor:               Krzysztof Onak                                 *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef vector < vector < int > > Graph;

const int MAX_SIZE = 10000;

Graph graph;
int n;

vector < int >hash_table(200003, -1);
vector < int >hash_val;

struct State {
  vector < bool > set1;
  vector < int >degree;
  int odd_count;
  int hash;

   State() {
    set1.resize(n, false);
    degree.resize(n);
    odd_count = 0;
    for (int i = 0; i < n; ++i) {
      degree[i] = graph[i].size();
      if (degree[i] % 2 == 1)
        ++odd_count;
    } hash = 0;
  }

  State(const State & state):set1(state.set1), degree(state.degree),
      odd_count(state.odd_count), hash(state.hash) {
  }

  void print_solution() {
    int count = 0;
    for (int i = 0; i < n; ++i)
      if (!set1[i])
        ++count;
    printf("%d\n", count);
    for (int i = 0; i < n; ++i)
      if (!set1[i])
        printf("%d ", i + 1);
    printf("\n");
  }

  void change_set(int i) {
    int m = graph[i].size();
    if (degree[i] % 2 == 1)
      --odd_count;
    degree[i] = 0;
    for (int j = 0; j < m; ++j) {
      int k = graph[i][j];
      if (set1[i] == set1[k])
        --degree[k];
      else {
        ++degree[k];
        ++degree[i];
      }
      if (degree[k] % 2 == 1)
        ++odd_count;
      else
        --odd_count;
    }
    set1[i] = !set1[i];
    hash ^= hash_val[i];
    if (degree[i] % 2 == 1)
      ++odd_count;
  }

  void visit() {
    hash_table[hash % hash_table.size()] = hash;
  }

  bool visited() {
    return hash_table[hash % hash_table.size()] == hash;
  }

  void find_odd(priority_queue < State > &q) {
    if (odd_count == 0) {
      print_solution();
      exit(0);
    }

    static vector < State > moves;
    for (int i = 0; i < n; ++i) {
      change_set(i);
      if (!visited()) {
        visit();
        q.push(*this);
        if ((int) q.size() >= MAX_SIZE) {
          priority_queue < State > new_q;
          for (int i = 0; i < MAX_SIZE / 10; ++i) {
            new_q.push(q.top());
            q.pop();
          }
          q = new_q;
        }
      }
      change_set(i);
    }
  }
};

bool operator<(const State & s1, const State & s2)
{
  return s1.odd_count > s2.odd_count;
}

int main()
{
  // wczytujê graf z wej¶cia
  scanf("%d", &n);
  graph.resize(n);
  for (int i = 0; i < n; ++i) {
    int m;
    scanf("%d", &m);
    for (int j = 0; j < m; ++j) {
      int k;
      scanf("%d", &k);
      --k;
      graph[i].push_back(k);
    }
  }


  hash_val.resize(n);
  for (int i = 0; i < n; ++i)
    hash_val[i] = rand();

  State start;

  priority_queue < State > q;
  q.push(start);
  while (!q.empty()) {
    State state = q.top();
    q.pop();
    state.find_odd(q);
  }
}
