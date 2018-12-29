/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Randka                                           *
 *   Autor:             Karol Pokorski                                   *
 *   Zlozonosc czasowa: O(n*log(n) + k * log^2(n))                       *
 *   Opis:              Rozwiazanie troche wolniejsze                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX_N = 1<<19;
const int MAX_K = 1<<19;
const int MAX_LOG_N = 19;

int n, k, p[MAX_N][MAX_LOG_N], d[MAX_N], compID[MAX_N], posCycle[MAX_N], cycleSize[MAX_N], numComp = 0;
bool visited[MAX_N], computed[MAX_N];

int FastWalk(int from, int steps) {
  // funkcja w czasie O(log n) wyznacza dla wierzcholka numer from
  // numer wierzcholka, do ktorego dojde po steps krokach

  for (int i = MAX_LOG_N-1; i >= 0; i--)
    if (1<<i <= steps) {
      from = p[from][i];
      steps -= 1<<i;
    }
  return from;
}

void SetCycle(int u) {
  // funkcja obsluguje cykl zaczynajacy sie w wierzcholku u

  int v = u, pos = 0;

  do {
    compID[v] = numComp; // numer spojnej
    d[v] = 0;             // odleglosc od cyklu
    computed[v] = true;  // wierzcholek obliczony
    posCycle[v] = pos++; // pozycja na cyklu
    v = p[v][0];
    cycleSize[u]++;       // dlugosc cyklu
  } while (v != u);
  do {
    cycleSize[v] = cycleSize[u];  // musimy zaznaczyc znana juz dlugosc cyklu wszystkim wierzcholkom
    v = p[v][0];
  } while (v != u);

  numComp++; // przechodzimy do kolejnego cyklu
}

void Dfs(int u) {
  // funkcja oblicza podstawowe informacje dla wierzcholka u

  visited[u] = true;

  if (!visited[p[u][0]]) // po raz pierwszy idziemy do tego wierzcholka
    Dfs(p[u][0]);
  else if (!computed[p[u][0]]) { // wlasnie znalezlismy cykl
    SetCycle(p[u][0]);
    return;
  }

  if (!computed[u]) {
    computed[u] = true;
    d[u] = d[p[u][0]]+1;
    compID[u] = compID[p[u][0]];
  }
}

pair<int,int> CompareSolutions(int a, int b, int c, int d) {
  // funkcja porownuje, ktore rozwiazanie jest lepsze (a,b) czy moze (c,d)
  // jako wynik zwracajac odpowiednia pare

  if (max(a, b) < max(c, d))
    return make_pair(a, b);
  if (max(a, b) > max(c, d))
    return make_pair(c, d);
  if (min(a, b) < min(c, d))
    return make_pair(a, b);
  if (min(a, b) > min(c, d))
    return make_pair(c, d);
  if (a > c)
    return make_pair(a, b);
  return make_pair(c, d);
}

int main() {
  int ret;

  ret = scanf("%d%d", &n, &k);

  for (int i = 0; i < n; i++) {
    ret = scanf("%d", &p[i][0]);
    p[i][0]--;
  }

  // obliczam sciezki o dlugosci 1, 2, 4, 8, 16, 32, ..., 262144
  for (int i = 1; i < MAX_LOG_N; i++)
    for (int j = 0; j < n; j++)
      p[j][i] = p[p[j][i-1]][i-1];

  // obliczam podstawowe informacje dla kazdego wierzcholka
  for (int i = 0; i < n; i++)
    if (!visited[i])
      Dfs(i);

  while (k--) {
    int u, v, stepsU = 0, stepsV = 0;

    ret = scanf("%d%d", &u, &v);
    u--;
    v--;

    if (compID[u] != compID[v]) {
      printf("-1 -1\n");
      continue;
    }

    // wyrownuje odleglosc od cyklu
    if (d[u] > d[v]) {
      stepsU = d[u]-d[v];
      u = FastWalk(u, stepsU);
    }
    if (d[u] < d[v]) {
      stepsV = d[v]-d[u];
      v = FastWalk(v, stepsV);
    }

    // ide w gore drzewa - to jest zrobione nieoptymalnie, w czasie O(log^2 n)
    int fromSearch = 0, toSearch = d[u];

    while (fromSearch != toSearch) {
      int centSearch = (fromSearch+toSearch+1)/2;

      //printf("fromSearch = %d, toSearch = %d, centSearch = %d\n", fromSearch, toSearch, centSearch);

      if (FastWalk(u, centSearch) != FastWalk(v, centSearch))
        fromSearch = centSearch;
      else
        toSearch = centSearch-1;
    }
    u = FastWalk(u, fromSearch);
    v = FastWalk(v, fromSearch);
    stepsU += fromSearch;
    stepsV += fromSearch;

    if ((d[u] >= 1) && (u != v)) {
      stepsU++;
      stepsV++;
      u = p[u][0];
      v = p[v][0];
    }

    if (u != v) { // niestety, rozwiazanie jest dopiero na cyklu
      pair<int,int> sol;

      if (posCycle[u] < posCycle[v])
        sol = CompareSolutions(stepsU+(posCycle[v]-posCycle[u]), stepsV, stepsU, stepsV+(cycleSize[u]-(posCycle[v]-posCycle[u])));
      if (posCycle[u] > posCycle[v])
        sol = CompareSolutions(stepsU, stepsV+(posCycle[u]-posCycle[v]), stepsU+(cycleSize[v]-(posCycle[u]-posCycle[v])), stepsV);

      stepsU = sol.first;
      stepsV = sol.second;
    }

    printf("%d %d\n", stepsU, stepsV);
  }

  return 0;
}
