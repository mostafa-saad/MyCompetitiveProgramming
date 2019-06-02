/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *   Opis:              Rozwiazanie bledne (zakladamy, ze graf jest      *
 *                      spojny)                                          *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <cstdio>
using namespace std;

#define MAXN 1000001
typedef pair<int, int> PII;

vector<int> krawedzie[MAXN]; /* podgraf indukowany wierzcholkow k+1..n */
vector<PII> kandydaci; /* krawedzie o jednym koncu o numerze <=k */
vector<bool> uzyte; /* czy kandydat zostal uzyty */
vector<PII> zablokowane; /* krawedzie, ktore zostana zablokowane */
int spojna[MAXN]; /* do jakich spojnych naleza wierzcholki (bez kandydatow) */
int spojna2[MAXN]; /* do jakich spojnych naleza wierzcholki (caly graf) */
int n, m, k;

void wczytaj_dane() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) spojna[i] = i;
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a > k) {
      krawedzie[a].push_back(b);
      krawedzie[b].push_back(a);
    } else {
      kandydaci.push_back(make_pair(a, b));
      uzyte.push_back(false);
    }
  }
}

void wyznacz_spojne() {
  vector<int> wierzcholki;
  for (int i = k+1; i <= n; ++i) {
    wierzcholki.push_back(i);
    while (!wierzcholki.empty()) {
      int v = wierzcholki.back();
      wierzcholki.pop_back();
      while (!krawedzie[v].empty()) {
        int w = krawedzie[v].back();
        krawedzie[v].pop_back();
        if (spojna[w] != i) {
          spojna[w] = i;
          wierzcholki.push_back(w);
        }
      }
    }
  }
}

void wybierz_zablokowane() {
  /* konwertujemy liste krawedzi do list sasiedztwa */
  for (size_t i = 0; i < kandydaci.size(); ++i) {
    PII p = kandydaci[i];
    krawedzie[p.first].push_back(i);
    krawedzie[spojna[p.second]].push_back(-i); /* ujemny numer oznacza odwrocona krawedz */
  }
  /* budujemy drzewo, pozostale krawedzie wrzucamy do zablokowanych */
  for (int i = 1; i <= n; ++i) spojna2[i] = i;
  vector<int> wierzcholki;
  wierzcholki.push_back(1);
  while (!wierzcholki.empty()) {
    int v = wierzcholki.back();
    wierzcholki.pop_back();
    while (!krawedzie[v].empty()) {
      int x, z = krawedzie[v].back();
      krawedzie[v].pop_back();
      if (z >= 0) /* jezeli ujemny to odwracamy krawedz */
        x = kandydaci[z].second;
      else {
        z = -z;
        x = kandydaci[z].first;
      }
      if (spojna2[spojna[x]] != 1) {
        wierzcholki.push_back(spojna[x]);
        spojna2[spojna[x]] = 1;
      } else
        if (!uzyte[z]) zablokowane.push_back(kandydaci[z]);
      uzyte[z] = true;
    }
  }
}

int main() {
  wczytaj_dane();
  wyznacz_spojne();
  wybierz_zablokowane();
  /* wypisujemy wynik */
  printf("%d\n", (int)zablokowane.size());
  for (size_t i = 0; i < zablokowane.size(); ++i)
    printf("%d %d\n", zablokowane[i].first, zablokowane[i].second);
  return 0;
}
