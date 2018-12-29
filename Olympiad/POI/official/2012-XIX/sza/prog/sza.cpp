/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Szatnia                                          *
 *   Autor:             Jan Kanty Milczek                                *
 *   Zlozonosc czasowa: O(nlogn + plogp + n*maxK)                        *
 *   Opis:              Rozwiazanie autorskie                            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int MaxK = 100000, MaxN = 1000, MaxP = 1000000, INF = 2100000000;
int ss; // zmienna pobierajaca wartosc z scanf

struct przedmiot {
  int przyniesiony, zabrany, wartosc;
  void wczytaj() {
    ss = scanf("%d%d%d", &wartosc, &przyniesiony, &zabrany);
  }
};

bool operator < (przedmiot x, przedmiot y) {
  return x.przyniesiony < y.przyniesiony;
}

struct zapytanie {
  int kiedywlamanie, ilechcaukrasc, iletrwaucieczka, oryginalnynumer;
  void wczytaj(int numer) {
    oryginalnynumer = numer;
    ss = scanf("%d%d%d", &kiedywlamanie, &ilechcaukrasc, &iletrwaucieczka);
  }
};

bool operator < (zapytanie x, zapytanie y) {
  return x.kiedywlamanie < y.kiedywlamanie;
}

int kiedyktossiezorientuje[MaxK + 1], n, p;
bool odpowiedz[MaxP];
zapytanie zapytania[MaxP];
przedmiot przedmioty[MaxN];

void dodajprzedmiot(przedmiot x) {
  for (int i = MaxK - x.wartosc; i >= 0; --i)
    kiedyktossiezorientuje[i + x.wartosc] = max(kiedyktossiezorientuje[i + x.wartosc], min(kiedyktossiezorientuje[i], x.zabrany));
}

void czymaszansepowodzenia(zapytanie x) {
  odpowiedz[x.oryginalnynumer] = kiedyktossiezorientuje[x.ilechcaukrasc] > x.kiedywlamanie + x.iletrwaucieczka;
}

int main() {
  ss = scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    przedmioty[i].wczytaj();
  ss = scanf("%d", &p);
  for (int i = 0; i < p; ++i)
    zapytania[i].wczytaj(i);
  sort(przedmioty, przedmioty + n);
  sort(zapytania, zapytania + p);

  kiedyktossiezorientuje[0] = INF;

  int iter_n = 0, iter_p = 0;

  while (iter_n != n || iter_p != p) {
    if (iter_n != n && (iter_p == p || przedmioty[iter_n].przyniesiony <= zapytania[iter_p].kiedywlamanie))
      dodajprzedmiot(przedmioty[iter_n++]);
    else
      czymaszansepowodzenia(zapytania[iter_p++]);
  }

  for (int i = 0; i < p; ++i)
    printf(odpowiedz[i]? "TAK\n" : "NIE\n");
}
