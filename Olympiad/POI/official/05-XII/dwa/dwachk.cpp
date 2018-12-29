/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DWA (Dwa przyjêcia)                            *
 *   Plik:                dwab1.pas                                      *
 *   Autor:               Krzysztof Onak                                 *
 *   Opis:                Weryfikator danych wyj¶ciowych                 *
 *                        u¿ycie:                                        *
 *                        dwachk dane.in wynik_prog.out odp_wzorc.out    *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <string>

using namespace std;

typedef vector < vector < bool > >Graph;

void error(int row, int col, string s)
{
  cout << "BLAD[w: " << row << ", k: " << col << "]: " << s << endl;
  exit(-1);
}

void read_graph(ifstream & input, Graph & graph)
{
  int n;
  input >> n;

  graph.resize(n);
  for (int i = 0; i < n; ++i)
    graph[i].resize(n, false);

  for (int i = 0; i < n; ++i) {
    int m;
    input >> m;
    for (int j = 0; j < m; ++j) {
      int a;
      input >> a;
      --a;
      graph[i][a] = true;
    }
  }
}

void wrong()
{
  cout << "WRONG" << endl;
  exit(0);
}

int main(int argc, char *argv[])
{
  if (argc < 3) {
    cerr << "Uzycie: ./dwachk.e plik.in plik.out" << endl;
    return -1;
  }

  ifstream input(argv[1]);
  ifstream output(argv[2]);

  Graph graph;
  read_graph(input, graph);

  int n = graph.size();

  int k;
  output >> k;
  if (!output)
    wrong();

  vector < bool > result(graph.size(), false);
  for (int i = 0; i < k; ++i) {
    int a;
    output >> a;
    if (!output)
      wrong();
    --a;
    if (result[a])
      wrong();
    result[a] = true;
  }

  for (int i = 0; i < n; ++i) {
    int degree = 0;
    for (int j = 0; j < n; ++j)
      if (graph[i][j] && result[i] == result[j])
        ++degree;
    if (degree % 2 == 1)
      wrong();
  }

  int a;
  output >> a;
  if (output)
    wrong();

  cout << "OK" << endl;
  return 0;
}
