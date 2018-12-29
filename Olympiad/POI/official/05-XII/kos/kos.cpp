/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KOS (Kosci)                                    *
 *   Plik:                kos.cpp                                        *
 *   Autor:               Marcin Stefaniak                               *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        (szukanie ¶cie¿ki liniowe)                     *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define REP(i,n) for(int i=0,_LL=(n);i<_LL;++i)
#define FOR(i,a,b) for(int i=(a),_LL=(b);i<=_LL;++i)
#define FORD(i,a,b) for(int i=(a),_LL=(b);i>=_LL;--i)

const int MAX_N = 10000;
const int MAX_M = 10000;

int N, M;
int e[MAX_M][2];                // rozegrane partie (krawêdzie grafu)

bool fwd[MAX_M];                // orientacja krawêdzi (true iff e[][0] --> e[][1])
int deg[MAX_N];                 // stopieñ wychodz±cy wierzcho³ka

/* listy krawêdzi 
 * g[v][koniec] = numery krawêdzi, o danym koñcu w v */
vector < int >g[MAX_N][2];

void wczytaj_dane()
{
  cin >> N >> M;
  REP(i, M) {
    int u, v;
    cin >> u >> v;
    e[i][0] = u - 1;
    e[i][1] = v - 1;
  };
}

void inicjuj_orientacje()
{
  REP(i, M) fwd[i] = true;
}

void inicjuj_graf()
{
  REP(i, N) REP(j, 2) g[i][j].clear();
  REP(i, M) REP(j, 2) g[e[i][j]][j].push_back(i);
}

void oblicz_poczatkowe_stopnie()
{
  REP(i, N) deg[i] = 0;
  REP(i, M) deg[e[i][(fwd[i] ? 0 : 1)]]++;
}

vector < int >sciezka;
int sciezka_first, sciezka_last;

void odwroc_sciezke()
{
  REP(i, sciezka.size()) {
    int j = sciezka[i];
    fwd[j] = !fwd[j];
  }
  deg[sciezka_first]--;
  deg[sciezka_last]++;
}

bool visited[MAX_N];
int dfs_max_deg;

bool dfs(int v)
{
  if (visited[v])
    return false;
  visited[v] = true;
  if (deg[v] <= dfs_max_deg) {
    sciezka_last = v;
    return true;
  }
  REP(k, 2) REP(i, g[v][k].size()) {
    int j = g[v][k][i];
    if ((k == 1) ^ fwd[j]) {
      sciezka.push_back(j);
      if (dfs(e[j][1 - k]))
        return true;
      sciezka.pop_back();
    }
  }
  return false;
}

int cnt[MAX_M];
int order[MAX_N];

void countsort_by_deg()
{
  REP(j, M) cnt[j] = 0;
  REP(i, N) cnt[deg[i]]++;
  REP(j, M - 1) cnt[j] += cnt[j - 1];
  FORD(i, N - 1, 0) order[--cnt[deg[i]]] = i;
}

bool znajdz_sciezke()
{
  sciezka.clear();
  countsort_by_deg();
  REP(j, N) visited[j] = false;
  FORD(i, N - 1, 0) {
    int v = order[i];
    sciezka_first = v;
    dfs_max_deg = deg[v] - 2;
    if (dfs(v))
      return true;
  }
  return false;
}

void obliczaj()
{
  inicjuj_orientacje();
  oblicz_poczatkowe_stopnie();
  inicjuj_graf();
  while (znajdz_sciezke()) {
    odwroc_sciezke();
  }
}

void wypisz_wynik()
{
  int k = 0;
  REP(i, N) k = max(k, deg[i]);
  cout << k << endl;
  REP(i, M) cout << (fwd[i] ? 1 : 0) << endl;
}

int main(void)
{
  wczytaj_dane();
  obliczaj();
  wypisz_wynik();
  return 0;
}
