/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DWA (Dwa przyjêcia)                            *
 *   Plik:                dwas4.pas                                      *
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

void check_solution()
{
  for (int i = 0; i < n; ++i) {
    int degree = 0;
    int m = graph[i].size();
    for (int j = 0; j < m; ++j)
      if (result[i] == result[graph[i][j]])
        ++degree;
    if (degree % 2 == 1)
      return;
  }

  print_solution(result);
  exit(0);
}

void check(int i)
{
  if (i >= n) {
    check_solution();
    return;
  }
  result[i] = false;
  check(i + 1);
  result[i] = true;
  check(i + 1);
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
  check(0);
}
