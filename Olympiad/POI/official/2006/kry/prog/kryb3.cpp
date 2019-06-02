/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                kryb3.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Algorytm o z³o¿ono¶ci O(n*max(a_i)^2).         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 50
#define MAX_K 2000000

int n;
unsigned int a[MAX_N];
unsigned long long wynik;
unsigned long long tab[MAX_K], tab1[MAX_K];

void dynamik()
{
  unsigned int wlk = 1;
  tab[0] = 1;
  for (int i = 0; i < n - 1; i++)
  {
    unsigned int wlk1 = wlk;
    for (unsigned int j = 0; j < wlk; j++)
      tab1[j] = 0;
    for (unsigned int ile = 0; ile <= a[i]; ile++)
      for (unsigned int j = 0; j < wlk; j++)
      {
        unsigned int x = j ^ ile;
        if (x >= wlk1)
        {
          for (unsigned int k = wlk1; k < x + 1; k++)
            tab1[k] = 0;
          wlk1 = x + 1;
        } /* if */
        tab1[x] += tab[j];
      } /* for */
    wlk = wlk1;
    for (unsigned int j = 0; j < wlk; j++)
      tab[j] = tab1[j];
  } /* for */
  for (unsigned int j = 0; j < min(wlk, a[n - 1] + 1); j++)
    wynik += tab[j];
} /* dynamik */

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%u", &a[i]);
  sort(a, a + n);
  wynik = 0;
  dynamik();
  printf("%llu\n", wynik - 1);
  return 0;
} /* main */
