/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KOS (Kosci)                                    *
 *   Plik:                koschk.cpp                                     *
 *   Autor:               Marcin Stefaniak                               *
 *   Opis:                Weryfikator danych wyj¶ciowych                 *
 *                        u¿ycie:                                        *
 *                        koschk dane.in wynik_prog.out odp_wzorc.out    *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
#define REP(i,n) for(int i=0,_LL=(n);i<_LL;++i)
#define FOR(i,a,b) for(int i=(a),_LL=(b);i<=_LL;++i)
#define FORD(i,a,b) for(int i=(a),_LL=(b);i>=_LL;--i)

const int MAX_N = 10000;
const int MAX_M = 10000;

int N, M, k, hint_k;
int e[MAX_M][2];                // rozegrane partie (krawêdzie grafu)
bool fwd[MAX_M];                // orientacja krawêdzi (true iff e[][0] --> e[][1])
int deg[MAX_N];                 // stopieñ wychodz±cy wierzcho³ka

void wczytaj_wejscie(istream & is)
{
  is >> N >> M;
  REP(i, M) {
    int u, v;
    is >> u >> v;
    e[i][0] = u - 1;
    e[i][1] = v - 1;
  };
}

void wczytaj_wyjscie(istream & is)
{
  is >> k;
  REP(i, M) {
    int dir;
    is >> dir;
    if (dir == 1)
      fwd[i] = true;
    else if (dir == 0)
      fwd[i] = false;
    else {
      cout << "WRONG\n" << "oczekiwano 0 lub 1\n";
      exit(0);
    }
  }
}

void wczytaj_podpowiedz(istream & is)
{
  is >> hint_k;
}

void oblicz_stopnie()
{
  REP(i, N) deg[i] = 0;
  REP(i, M) deg[e[i][(fwd[i] ? 0 : 1)]]++;
}

int main(int argc, char *argv[])
{
  ifstream wejscie(argv[1]);
  wczytaj_wejscie(wejscie);
  ifstream wyjscie(argv[2]);
  wczytaj_wyjscie(wyjscie);
  ifstream podpowiedz(argv[3]);
  wczytaj_podpowiedz(podpowiedz);
  oblicz_stopnie();
  int max_d = -1;
  REP(i, N) if (deg[i] > max_d)
    max_d = deg[i];
  if (max_d != k) {
    cout << "WRONG\n"
        << "dla takiego uk³adu partii k wynosi " << max_d
        << ", a nie " << k << '\n';
    return 0;
  }
  if (k > hint_k) {
    cout << "WRONG\n"
        << "podane k nie jest najmniejsze mo¿liwe, k=" << k
        << ", prawid³owe rozwi±zanie k=" << hint_k << '\n';
    return 0;
  }
  if (k < hint_k) {
    cerr << "Ooops... rozwi±zanie lepsze od wzorcowego?\n";
  }
  cout << "OK\n";
  return 0;
}
