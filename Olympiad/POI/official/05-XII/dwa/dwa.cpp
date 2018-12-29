/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DWA (Dwa przyjecia)                            *
 *   Plik:                dwa.cpp                                        *
 *   Autor:               Krzysztof Onak                                 *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Jezyk: C++                                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

typedef vector < vector < bool > >Graph;  // reprezentacja macierzowa grafu

// znajduje wierzcho³ek stopnia nieparzystego
int find_odd(Graph & graph)
{
  int n = graph.size();
  for (int i = 0; i < n; ++i) {
    int degree = 0;
    for (int j = 0; j < n; ++j)
      if (graph[i][j])
        ++degree;
    if (degree % 2 == 1)
      return i;
  }

  return -1;
}

// dzieli graf na dwie czê¶ci, tak aby ka¿dy wierzcho³ek mia³ parzyst± liczbê s±siadów w swoim zbiorze
void divide(Graph & graph, vector < bool > &result)
{
  int n = graph.size();

  int i = find_odd(graph);
  if (i == -1)
    return;

  // graph to graf G z dowodu

  vector < bool > neigh = graph[i]; // S - zbiór s±siadów wierzcho³ka i

  // usuwam wierzcho³ek i z grafu
  for (int j = 0; j < n; ++j)
    if (neigh[j]) {
      graph[i][j] = false;
      graph[j][i] = false;
    }

  // odwracam krawêdzie w podgrafie indukowanym przez S (s±siedzi wierzcho³ka i)
  for (int j = 0; j < n; ++j)
    if (neigh[j]) {
      for (int k = j + 1; k < n; ++k)
        if (neigh[k]) {
          graph[j][k] = !graph[j][k];
          graph[k][j] = !graph[k][j];
        }
    }

  // teraz graph to graf H z dowodu
  // wykonujê rekurencyjnie podzia³ tego grafu
  divide(graph, result);

  // do³±czam wierzcho³ek i do zbioru, w którym ma on parzyst± liczbê s±siadów
  int count_A = 0;
  int count_B = 0;
  for (int j = 0; j < n; ++j)
    if (neigh[j])
      if (!result[j])
        ++count_A;
      else
        ++count_B;

  if (count_A % 2 == 0)
    result[i] = false;
  else
    result[i] = true;
}

void print_solution(vector < bool > &result)
{
  int n = result.size();
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

int main()
{
  // wczytujê graf z wej¶cia
  int n;
  scanf("%d", &n);
  Graph graph(n);
  for (int i = 0; i < n; ++i)
    graph[i].resize(n, false);
  for (int i = 0; i < n; ++i) {
    int m;
    scanf("%d", &m);
    for (int j = 0; j < m; ++j) {
      int k;
      scanf("%d", &k);
      --k;
      graph[i][k] = true;
    }
  }

  // obliczam podzia³ zbioru
  vector < bool > result(n, false);
  divide(graph, result);

  // wypisujê wynik - jeden ze zbiorów
  print_solution(result);
}
