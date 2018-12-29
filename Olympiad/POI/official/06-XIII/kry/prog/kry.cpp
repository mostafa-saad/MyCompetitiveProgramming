/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                kry.cpp                                        *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;

#define MAX_N 50

int n;
unsigned int a[MAX_N];
unsigned long long wynik;
int t[MAX_N], dlugosc[MAX_N];
unsigned long long dwum[MAX_N + 1][MAX_N + 1];

void licz_dwum() // liczy wspó³czynniki dwumianowe
{
  dwum[0][0] = 1;
  for (int i = 1; i <= n; i++)
  {
    dwum[i][0] = dwum[i][i] = 1;
    for (int j = 1; j < i; j++)
      dwum[i][j] = dwum[i - 1][j - 1] + dwum[i - 1][j];
  } /* for */
} /* licz_dwum */

int max_dlug() // liczy max d³ugo¶æ binarn± liczb a_i
{
  int maxlen = 0;
  for (int i = 0; i < n; i++)
  {
    unsigned int m = a[i];
    int akt = 0;
    while (m)
    {
      akt++;
      m /= 2;
    } /* while */
    maxlen = max(maxlen, akt);
    dlugosc[i] = akt;
  } /* for */
  return maxlen;
} /* max_dlug */

pair<unsigned int, int> nowe[MAX_N];
int ilen;

void zrob_nowe() // grupuje te same liczby
{
  int i = 0, i0;
  ilen = 0;
  while (i < n)
  {
    i0 = i;
    while (i0 < n && a[i0] == a[i])
      i0++;
    nowe[ilen++] = make_pair(a[i], i0 - i);
    i = i0;
  } /* while */
} /* zrob_nowe */

void max_dlug1() // liczy max d³ugo¶æ binarn± liczb nowe_i
{
  for (int i = 0; i < ilen; i++)
  {
    unsigned int m = nowe[i].first;
    int akt = 0;
    while (m)
    {
      akt++;
      m /= 2;
    } /* while */
    dlugosc[i] = akt;
  } /* for */
} /* max_dlug1 */


void generuj(int dlug) // g³ówna funkcja
{
  sort(a, a + n);
  zrob_nowe();
  max_dlug1();
  if (!dlug)
  {
    wynik++;
    return;
  } /* if */
  int k = ilen - 1;
  while (k >= 0 && dlugosc[k] >= dlug)
    k--;
  k++;
  if (k == ilen) /* nie ma nic do roboty na tym bicie */
  {
    generuj(dlug - 1);
    return;
  } /* if */
  for (int i = k; i < ilen; i++) // na pocz±tku zbiór pusty
    t[i] = 0;
  unsigned long long pom = 1;
  for (int i = 0; i < k; i++)
    for (int j = 0; j < nowe[i].second; j++)
      pom *= (nowe[i].first + 1);
  
  int poz = ilen - 1, ile;
  int suma = 0;
  for (int i = k; i < ilen; i++)
    suma += nowe[i].second;

  /* przechodzimy przez wszystkie podzbiory */
  while (1)
  {
    ile = 0;
    for (int i = k; i < ilen; i++)
      ile += t[i];
    if (ile % 2 == 0 && ile < suma) // niepe³ny podzbiór parzystej mocy
    {
      for (poz = k; poz < ilen; poz++)
        if (t[poz] < nowe[poz].second)
          break;
      unsigned long long tmp = pom;
      for (int i = k; i < ilen; i++)
      {
        for (int j = 0; j < t[i]; j++)
          tmp *= nowe[i].first - (1U << (dlug - 1)) + 1;
        for (int j = 0; j < nowe[i].second - t[i] - (i == poz ? 1 : 0); j++)
          tmp *= (1U << (dlug - 1));
        tmp *= dwum[nowe[i].second][t[i]];
      } /* for */
      wynik += tmp;
    } /* if */
    if (ile == suma && ile % 2 == 0)
    {
      for (int i = 0; i < n; i++)
        a[i] &= (unsigned int)((1LL << dlug) - 1 - (1U << (dlug - 1)));
      generuj(dlug - 1);
      return;
    } /* if */

    /* Zwiêkszamy podzbiór */
    t[ilen - 1]++;
    poz = ilen - 1;
    while (poz >= k && t[poz] > nowe[poz].second)
    {
      t[poz] = 0;
      poz--;
      if (poz >= k)
        t[poz]++;
    } /* while */
    if (poz < k)
      break;
  } /* while */
} /* generuj */

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%u", &a[i]);
  licz_dwum();
  wynik = 0;
  generuj(max_dlug());
  printf("%llu\n", wynik - 1);
  return 0;
} /* main */
