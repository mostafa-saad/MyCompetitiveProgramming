/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KOS (Kosci)                                    *
 *   Plik:                kosb1.cpp                                      *
 *   Autor:               Marcin Stefaniak                               *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                        (heureza: odwracamy pojedyncze krawêdzie)      *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define REP(i,n) for(int i=0,_LL=(n);i<_LL;++i)
#define FOR(i,a,b) for(int i=(a),_LL=(b);i<=_LL;++i)

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

int sciezka_krawedz, sciezka_first, sciezka_last;

void odwroc_sciezke()
{
  int j = sciezka_krawedz;
  fwd[j] = !fwd[j];
  deg[sciezka_first]--;
  deg[sciezka_last]++;
}

bool znajdz_sciezke()
{
  REP(v, N) {
    REP(k, 2) REP(i, g[v][k].size()) {
      int j = g[v][k][i];
      if ((k == 1) ^ fwd[j]) {
        int u = e[j][1 - k];
        if (deg[u] <= deg[v] - 2) {
          sciezka_krawedz = j;
          sciezka_first = v;
          sciezka_last = u;
          return true;
        }
      }
    }
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
