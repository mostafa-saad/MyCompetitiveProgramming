/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SUM (Sumy Fibbonacciego)                       *
 *   Plik:                sum.cpp                                        *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        z³o¿onosc O(n)                                 *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#define VAR(a,b) typeof(b) a=(b)
#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)

int slowo1[1000100];
int slowo2[1000100];
vector < int >wynik;
int n, m, dlugosc_wyniku;


int max(int x, int y)
{
  return (x > y ? x : y);
}


void wczytaj()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &slowo1[i]);
  }
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%d", &slowo2[i]);
  }
  return;
}

void dodaj()
{
  for (int i = 0; i < n; i++)
    wynik[i] = slowo1[i];
  for (int i = 0; i < m; i++)
    wynik[i] += slowo2[i];
  dlugosc_wyniku = max(n, m);
}



void eliminate_102_002(vector < int >&tab)
{
  // chcemy wyeliminowac sekwencje 102 i 002
  // ciag na wejsciu jest znormalizowany.
  // i kazda 2 jest "otoczona" zerami
  FORD(i, max(n, m) + 5, 2) {
    if (tab[i] == 2) {
      if ((tab[i - 1] == 0) && (tab[i - 2] == 1)) {
        // 102 -> 211
        tab[i - 2] = 2;
        tab[i - 1] = 1;
        tab[i] = 1;
        continue;
      }
      if ((tab[i - 1] == 0) && (tab[i - 2] == 0)) {
        // 002 -> 111
        tab[i - 2] = 1;
        tab[i - 1] = 1;
        tab[i] = 1;
      }
    }
  }
  if ((tab[1] == 2) && (tab[0] == 0)) {
    tab[1] = 1;
    tab[0] = 2;
  }
  // teraz po kazdej dwojce jest pewna (niezerowa) ilosc jedynek
  return;
}


// usuwa 2 z poczatku
void eliminate_front(vector < int >&tab)
{

  if ((tab[0] == 2) && (tab[1] == 0)) {
    tab[0] = 0;
    tab[1] = 1;
  }

  int i = 0;
  if (tab[i] == 2) {
    int ile_jedynek = 0;
    while (tab[i + ile_jedynek + 1] == 1)
      ile_jedynek++;
    if ((ile_jedynek != 0) && (ile_jedynek % 2 == 0)) {
      // 21^(2k)0 -> (01)^(k+1)
      REP(j, ile_jedynek + 2) {
        if (j % 2 == 0)
          tab[i + j] = 0;
        if (j % 2 == 1)
          tab[i + j] = 1;
      }
      i += ile_jedynek + 1;
    }
    if (ile_jedynek % 2 == 1) {
      // 21^(2k+1)0 -> 1(01)^(k+1)
      REP(j, ile_jedynek + 2) {
        if (j % 2 == 0)
          tab[i + j] = 1;
        if (j % 2 == 1)
          tab[i + j] = 0;
      }
      i += ile_jedynek + 1;
    }
  }
  // poniewaz w danych nie bylo 002 to w wyniku nie bedzie 102
}

void normalizuj(vector < int >&tab)
{
  // zajmuje sie usunieciem sasiednich jedynek

  int ile_jedynek = 0;

  REP(i, max(n, m) + 5) {
    if (tab[i] == 0) {
      if (ile_jedynek == 0) {
        ile_jedynek = 0;
        continue;
      }                         // 0 -> 0
      if (ile_jedynek == 1) {
        ile_jedynek = 0;
        continue;
      }                         // 010 -> 010
      if (ile_jedynek % 2 == 0) { // 01^(2k) -> 00 (01)^k
        FOR(j, 1, ile_jedynek) {
          tab[i - j] = 0;
          if (j % 2 == 0)
            tab[i - j] = 1;
        }
        tab[i - ile_jedynek] = 0;
        tab[i] = 1;
        ile_jedynek = 1;
        continue;
      }
      // 01^(2k+1) -> 010(01)^k
      FOR(j, 1, ile_jedynek) {
        tab[i - j] = 0;
        if (j % 2 == 0)
          tab[i - j] = 1;
      }
      tab[i] = 1;
      tab[i - ile_jedynek] = 1;
      tab[i - ile_jedynek + 1] = 0;
      ile_jedynek = 1;
      continue;
    }
    if (tab[i] == 1) {
      ile_jedynek++;
    }
    if (tab[i] == 2) {          // nastepna zawsze jest == 0
      if (ile_jedynek == 0) {
        continue;
      }
      if (ile_jedynek == 1) {
        tab[i - 1] = 0;
        tab[i] = 1;
        tab[i + 1] = 1;
        ile_jedynek = 1;
        // 0120 -> 0011
      }
      if (ile_jedynek == 2) {
        tab[i - 1] = 0;
        tab[i] = 1;
        tab[i + 1] = 1;
        ile_jedynek = 1;
        // 01120 -> 01011
      }

      // innych mozliwosci nie MA !!!
    }

  }
  return;
}


void wypisz_wynik()
{
  while ((wynik.size() > 1) && (wynik[wynik.size() - 1] == 0))
    wynik.pop_back();

  printf("%d", wynik.size());
  REP(i, wynik.size())
      printf(" %d", wynik[i]);
  printf("\n");
  return;
}


void eliminate_last(vector < int >&tab)
{
  // ostatnia eliminacja
  FOR(i, 2, max(n, m) + 5) {
    if (tab[i] == 2) {
      // 1102  -> 0012
      if ((tab[i - 1] == 0) && (tab[i - 2] == 1) && (tab[i - 3] == 1)) {
        tab[i - 3] = 0;
        tab[i - 2] = 0;
        tab[i - 1] = 1;
        tab[i] = 2;
        continue;
      }
    }
    if (tab[i - 1] == 2) {
      if (tab[i] == 0) {
        // 120 -> 011
        tab[i - 2] = 0;
        tab[i - 1] = 1;
        tab[i] = 1;
        continue;
      }
      if (tab[i] == 1) {
        // 121 --> 012
        tab[i - 2] = 0;
        tab[i - 1] = 1;
        tab[i] = 2;
        continue;
      }
    }
  }
}


int main()
{
  wczytaj();
  wynik.resize(max(n, m) + 10);
  REP(i, wynik.size())wynik[i] = 0;

  dodaj();
  normalizuj(wynik);
  eliminate_102_002(wynik);
  eliminate_front(wynik);
  eliminate_last(wynik);
  normalizuj(wynik);

  wypisz_wynik();
  return 0;
}
