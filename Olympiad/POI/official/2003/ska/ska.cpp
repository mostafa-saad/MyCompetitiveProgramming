/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Skarb                                          *
 *   Plik:                ska.cpp                                        *
 *   Autor:               Krzysztof Onak                                 *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <utility>
using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)

const int MAXN = 100;
const int MAXK = 100;
const int MAXL = 100;
const int MAXDL = 100;

int n, k, l;
int dokad[MAXN][MAXN]; // idziemy a -> b -> dokad[a][b]
int odl[MAXN][MAXN]; // d³ugo¶æ korytarza pomiêdzy komnatami a i b
bool inf[MAXK][MAXL]; // informacje posiadane przez stra¿nika
int start[MAXK]; // komnaty startowe dla stra¿ników
int nast[MAXK]; // drugie w kolejno¶ci komnaty
vector<int> wizyty[MAXK][MAXN]; // pierwsze wizyty w danym wierzcho³ku
int dlugosc[MAXK]; // d³ugo¶æ cyklu
vector<int> odwiedzone[MAXK]; // odwiedzane komnaty

// zbiory roz³±czne
int stopien[MAXK], rep[MAXK];

void inicjuj_zbiory() {
  REP(i, k) {
    stopien[i] = 0;
    rep[i] = i;
  }
}

int znajdz(int v) {
  if (rep[v] != v)
    rep[v] = znajdz(rep[v]);
  return rep[v];
}

void polacz(int a, int b) {
  a = znajdz(a);
  b = znajdz(b);
  if (a != b) {
    if (stopien[a] < stopien[b]) swap(a, b);
    else if (stopien[a] == stopien[b]) ++stopien[a];
    rep[b] = a;
    REP(i, l)
      inf[a][i] = inf[a][i] || inf[b][i];
  }
}

void wczytaj() {
  scanf("%d", &n);
  // korytarze
  REP(i, n) {
    int ile, sasiedzi[MAXN];
    scanf("%d", &ile);
    REP(j, ile) {
      int s, d;
      scanf("%d%d", &s, &d);
      sasiedzi[j] = --s;
      odl[i][s] = d;
    }
    REP(j, ile)
      dokad[sasiedzi[j]][i] = sasiedzi[(j != 0 ? j : ile) - 1];
  }
  // stra¿nicy
  scanf("%d%d", &k, &l);
  REP(i, k) {
    int ile;
    scanf("%d%d%d", &start[i], &nast[i], &ile);
    --start[i];
    --nast[i];
    REP(j, l) inf[i][j] = false;
    REP(j, ile) {
      int nr;
      scanf("%d", &nr);
      inf[i][--nr] = true;
    }
  }
}

void oblicz_wizyty() {
  REP(i, k) {
    int d = 0, a = start[i], b = nast[i];
    do {
      if (wizyty[i][a].empty()) {
	odwiedzone[i].push_back(a);
      }
      wizyty[i][a].push_back(d);
      d += odl[a][b];
      int c = dokad[a][b];
      a = b;
      b = c;
    } while (a != start[i] || b != nast[i]);
    dlugosc[i] = d;
  }
}

int NWD(int a, int b) {
  return (b == 0 ? a : NWD(b, a % b));
}

bool spotkanie(int a, int b, bool *tablica) {
  if (odwiedzone[a].size() > odwiedzone[b].size()) swap(a, b);
  int d = NWD(dlugosc[a], dlugosc[b]);
  int rozmiar = odwiedzone[a].size();
  REP(i, rozmiar) {
    int w = odwiedzone[a][i];
    int wizA = wizyty[a][w].size(), wizB = wizyty[b][w].size();
    if (wizB > 0) {
      bool spot = false;
      REP(j, wizA) {
	tablica[wizyty[a][w][j] % d] = true;
      }
      REP(j, wizB)
	if (tablica[wizyty[b][w][j] % d]) {
	  spot = true;
	  break;
	}
      REP(j, wizA) {
	tablica[wizyty[a][w][j] % d] = false;
      }
      if (spot) return true;
    }
  }
  return false;
}

void lacz() {
  const int rozmiar = MAXN * MAXN * MAXDL;
  bool tablica[rozmiar];
  REP(i, rozmiar) tablica[i] = false;
  inicjuj_zbiory();
  REP(i, k)
    for(int j = i + 1; j < k; ++j) {
      int a = znajdz(i), b = znajdz(j);
      if (a != b && spotkanie(i, j, tablica))
	polacz(a, b);
    }
}

void zapisz() {
  int kto[MAXK], ile = 0;
  REP(i, k) {
    bool wszystko = true;
    int rep = znajdz(i);
    REP(j, l)
      if (!inf[rep][j])
	wszystko = false;
    if (wszystko)
      kto[ile++] = i;
  }
  printf("%d\n", ile);
  REP(i, ile) printf("%d\n", kto[i] + 1);
}

int main() {
  wczytaj();
  oblicz_wizyty();
  lacz();
  zapisz();
}
