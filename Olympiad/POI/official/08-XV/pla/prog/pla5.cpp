/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     pla5.cpp                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie autorskie - Find & Union.                     *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;

/* Struktura danych dla zbiorow rozlacznych.
 * Zlozonosc: O(n log*n) */
const int MAX_N = 250000 + 1; /* n+1 */
int p[MAX_N], rank[MAX_N];

inline void makeset(int x)
{
  p[x] = x;
  rank[x] = 0;
}

int findset(int x)
{
  if (x != p[x])
    p[x] = findset(p[x]);
  return p[x];
}

inline void link(int x, int y)
{
  if (rank[x] > rank[y])
    p[y] = x;
  else
  {
    p[x] = y;
    if (rank[x] == rank[y])
      rank[y]++;
  }
}

inline void unia(int x, int y)
{
  link(findset(x), findset(y));
}


/* Wlasciwe rozwiazanie */
int n;
pair<int, int> w[MAX_N];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    int d; /* ignorujemy */
    scanf("%d%d", &d, &(w[i].first));
    w[i].second = i;
  }
  /* Porzadek nierosnacy wysokosci */
  sort(w, w + n);
  reverse(w, w + n);

  /* Przetwarzamy na Find & Union */
  for (int i = 0; i < n + 1; i++)
    makeset(i);
  int i = 0, wynik = 0;
  while (i < n)
  {
    /* Przetwarzamy wszystkie budynki o wysokosci w[i].first */
    int i0 = i;
    /* Pierwszy raz - scalanie */
    while (i0 < n && w[i0].first == w[i].first)
    {
      if (findset(w[i0].second) != findset(w[i0].second + 1))
        unia(w[i0].second, w[i0].second + 1);
      i0++;
    }
    /* Drugi raz - wyznaczanie wyniku */
    int poprz = -1;
    i0 = i;
    while (i0 < n && w[i0].first == w[i].first)
    {
      /* Pozycje drzew o tej samej wysokosci rozwazamy od prawej do lewej */
      if (findset(w[i0].second) != poprz)
      {
        poprz = findset(w[i0].second);
        wynik++;
      }
      i0++;
    }
    i=i0;
  }
  printf("%d\n", wynik);
  return 0;
}
