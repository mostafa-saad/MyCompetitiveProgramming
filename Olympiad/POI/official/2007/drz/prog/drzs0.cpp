/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Drzewa (DRZ)                                               *}
{*   Plik:    drzs0.cpp                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie zbyt wolne: zlozonosc czasowa: O(n^3),         *}
{*            zlozonosc pamieciowa: O(n)                                 *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAX_N 50000

int n, i, j;
int h[MAX_N];

long long licz()
/* Liczy wspó³czynnik nieporz±dku. */
{
  long long wyn = 0LL;
  for (int i = 0; i < n - 1; i++)
    wyn += abs(h[i] - h[i + 1]);
  return wyn;
} /* licz */

int main()
{
  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%d", &h[i]);
  long long wyn, wsp = licz();
  for (i = 0; i < n; i++)
  {
    wyn = wsp;
    for (j = 0; j < n; j++)
    {
      swap(h[i], h[j]);
      wyn = min(wyn, licz());
      swap(h[i], h[j]);
    } /* for */
    printf("%lld\n", wyn);
  } /* for */
  return 0;
} /* main */
