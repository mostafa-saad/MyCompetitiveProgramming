/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                krys0.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Algorytm brutalny.                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

#define MAX_N 50

int n;
unsigned int a[MAX_N], t[MAX_N];
unsigned long long wynik;

void sprawdz()
{
  unsigned int w = 0;
  for (int i = 0; i < n; i++)
    w ^= t[i];
  if (!w)
    wynik++;
} /* sprawdz */

void brutalny(int poz)
{
  if (poz == n)
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
  wynik = 0;
  brutalny(0);
  printf("%llu\n", wynik - 1);
  return 0;
} /* main */
