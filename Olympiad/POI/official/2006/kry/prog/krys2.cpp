/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                krys2.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Najmniejsze n-1 liczb a_i wybiera dowolnie,    *
 *                        ostatnia jest wyznaczona jednoznacznie.        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 50

int n;
unsigned int a[MAX_N], t[MAX_N];
unsigned long long wynik;

void sprawdz()
{
  unsigned int w = 0;
  for (int i = 0; i < n - 1; i++)
    w ^= t[i];
  if (w <= a[n - 1])
    wynik++;
} /* sprawdz */

void brutalny(int poz)
{
  if (poz == n - 1)
    sprawdz();
  else
  for (unsigned int i = 0; i <= a[poz]; i++)
  {
    t[poz] = i;
    brutalny(poz + 1);
  } /* for */
} /* brutalny */

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%u", &a[i]);
  sort(a, a + n);
  wynik = 0;
  brutalny(0);
  printf("%llu\n", wynik - 1);
  return 0;
} /* main */
