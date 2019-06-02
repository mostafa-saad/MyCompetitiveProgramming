/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                kryb0.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie niepoprawne.                       *
 *                        Zak³ada, ¿e max(a_i) jest na tyle du¿e, ¿e     *
 *                        dowolnie wybieraj±c a_1,...,a_{n-1} otrzymamy  *
 *                        dok³adnie jedno dobre a_n.                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 50

int n;
unsigned int a[MAX_N];
unsigned long long wynik = 1;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%u", &a[i]);
  sort(a, a + n);
  for (int i = 0; i < n - 1; i++)
    wynik *= (long long) a[i] + 1;
  printf("%llu\n", wynik - 1);
  return 0;
} /* main */
