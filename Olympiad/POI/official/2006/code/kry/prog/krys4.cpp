/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                krys4.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Implementacja rozwi±zania autorskiego,         *
 *                        bez osobnego traktowania dla k<=4.             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 50

int n;
unsigned int a[MAX_N];
unsigned long long wynik;
int t[MAX_N], dlugosc[MAX_N];

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

void generuj(int dlug)
{
  sort(a, a + n);
  max_dlug();
  if (!dlug)
  {
    wynik++;
    return;
  } /* if */
  int k = n - 1;
  while (k >= 0 && dlugosc[k] >= dlug)
    k--;
  k++;
  if (k == n) /* nie ma nic do roboty na tym bicie */
  {
    generuj(dlug - 1);
    return;
  } /* if */
  for (int i = k; i < n; i++) // na pocz±tku zbiór pusty
    t[i] = 0;
  /* przechodzimy przez wszystkie podzbiory */
  unsigned long long pom = 1;
  for (int i = 0; i < k; i++)
    pom *= (a[i] + 1);
  
  int poz = n - 1, ile;
  while (1)
  {
    ile = 0;
    for (int i = k; i < n; i++)
      ile += t[i];
    if (ile % 2 == 0 && ile < n - k) // niepe³ny podzbiór parzystej mocy
    {
      for (poz = k; poz < n; poz++)
        if (!t[poz])
          break;
      unsigned long long tmp = pom;
      for (int i = k; i < n; i++)
        if (i != poz)
        {
          if (t[i])
            tmp *= a[i] - ((unsigned int)1 << (dlug - 1)) + 1;
          else
            tmp *= ((unsigned int)1 << (dlug - 1));
        } /* if */
      wynik += tmp;
    } /* if */
    if (ile == n - k && ile % 2 == 0)
    {
      for (int i = k; i < n; i++)
        a[i] ^= ((unsigned int)1 << (dlug - 1));
      generuj(dlug - 1);
      return;
    } /* if */
    t[n - 1]++;
    poz = n - 1;
    while (poz >= k && t[poz] == 2)
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
  wynik = 0;
  generuj(max_dlug());
  printf("%llu\n", wynik - 1);
  return 0;
} /* main */
