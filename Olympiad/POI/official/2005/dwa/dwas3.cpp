/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DWA (Dwa przyjêcia)                            *
 *   Plik:                dwas3.pas                                      *
 *   Autor:               Krzysztof Onak                                 *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

typedef vector < vector < int > > Graph;

int n;
vector < bool > result;
Graph graph;
vector < int >degree;

void print_solution(vector < bool > &result)
{
  int count = 0;
  for (int i = 0; i < n; ++i)
    if (!result[i])
      ++count;
  printf("%d\n", count);
  for (int i = 0; i < n; ++i)
    if (!result[i])
      printf("%d ", i + 1);
  printf("\n");
}

int find_odd(int start)
{
  int i = start;
  do {
    if (degree[i] % 2 == 1)
      return i;
    i = (i + 1) % n;
  } while (i != start);
  return -1;
}

void change_set(int i)
{
  int m = graph[i].size();
  degree[i] = 0;
  for (int j = 0; j < m; ++j) {
    int k = graph[i][j];
    if (result[i] == result[k])
      --degree[k];
    else {
      ++degree[k];
      ++degree[i];
    }
  }
  result[i] = !result[i];
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

  result.resize(n, false);
  degree.resize(n);
  for (int i = 0; i < n; ++i)
    degree[i] = graph[i].size();

  int i = 0;
  while ((i = find_odd(rand() % n)) != -1)
    change_set(i);
  print_solution(result);
}
