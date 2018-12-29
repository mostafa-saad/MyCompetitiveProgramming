/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Klocki (KLO)                                              *
 *   Plik:     klob2.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Program o zlozonosci O(nlogn), zapisany z uzyciem         *
 *             multiset'ow z STL-a, ale zapominajacy, ze wynik moze byc  *
 *             wiekszy niz 32-bitowy.                                    *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <set>
using namespace std;

#define MAX_N 100000

int n, k;
int h[MAX_N];

/* Obsluga wyszukiwania median */
multiset<int> mniejsze, wieksze;
int suma_mniejsze, suma_wieksze;
int mediana;

void rownowaz()
{
  unsigned int s1 = mniejsze.size(), s2 = wieksze.size();
  if (s2 > s1)
  {
    /* wieksze -> mniejsze */
    int elt = *(wieksze.begin());
    wieksze.erase(wieksze.begin());
    suma_wieksze -= elt;
    mniejsze.insert(elt);
    suma_mniejsze += elt;
    mediana = elt;
  }
  else if (s1 > s2 + 1)
  {
    /* mniejsze -> wieksze */
    multiset<int>::iterator it = mniejsze.end();
    it--;
    int elt = *it;
    it--; mediana = *it; it++;
    mniejsze.erase(it);
    suma_mniejsze -= elt;
    wieksze.insert(elt);
    suma_wieksze += elt;
  }
  else if (s1)
  {
    /* po prostu pobieramy mediane */
    multiset<int>::iterator it = mniejsze.end();
    it--;
    mediana = *it;
  }
}

void wstaw(int wys)
{
  if (wys <= mediana)
  {
    mniejsze.insert(wys);
    suma_mniejsze += wys;
  } else
  {
    wieksze.insert(wys);
    suma_wieksze += wys;
  }
  rownowaz();
}

void usun(int wys)
{
  if (wys <= mediana)
  {
    suma_mniejsze -= wys;
    mniejsze.erase(mniejsze.find(wys));
  } else
  {
    suma_wieksze -= wys;
    wieksze.erase(wieksze.find(wys));
  }
  rownowaz();
}

int minimum;
int min_i, min_mediana;

int main()
{
  /* Odczyt */
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++)
    scanf("%d", h + i);

  /* Poczatek */
  mediana = -1;
  for (int i = 0; i < k - 1; i++)
    wstaw(h[i]);

  /* Obliczanie wyniku */
  minimum = 2000000000;
  for (int i = k - 1; i < n; i++)
  {
    wstaw(h[i]);
    int akt = (int)mediana * mniejsze.size() - suma_mniejsze +
              suma_wieksze - (int)mediana * wieksze.size();
    if (akt < minimum)
    {
      minimum = akt;
      min_i = i - k + 1;
      min_mediana = mediana;
    }
    usun(h[i - k + 1]);
  }

  /* Wypisywanie wyniku */
  printf("%d\n", minimum);
  for (int i = 0; i < min_i; i++)
    printf("%d\n", h[i]);
  for (int i = min_i; i < min_i + k; i++)
    printf("%d\n", min_mediana);
  for (int i = min_i + k; i < n; i++)
    printf("%d\n", h[i]);
  return 0;
}
