/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Drzewa (DRZ)                                               *}
{*   Plik:    drzs2.cpp                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie zbyt wolne: zlozonosc czasowa: O(n^2),         *}
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


int zm_wart(int wys, int poz)
/* Ta funkcja liczy zmianê warto¶ci wspó³czynnika nieporz±dku, kiedy drzewo
 * o wysoko¶ci wys zostaje umiejscowione na pozycji poz. */
{
  int wyn = 0;
  if (poz > 0)
    wyn += abs(wys - h[poz - 1]);
  if (poz < n - 1)
    wyn += abs(wys - h[poz + 1]);
  return wyn;
} /* zm_wart */

int zm_wart1(int poz)
/* Ta funkcja liczy zmianê warto¶ci wspó³czynnika nieporz±dku, kiedy drzewa
 * na pozycjach poz i poz+1 zostaj± zamienione miejscami. */
{
  int wyn = 0;
  if (poz > 0)
    wyn -= abs(h[poz] - h[poz - 1]) - abs(h[poz + 1] - h[poz - 1]);
  if (poz + 1 < n - 1)
    wyn -= abs(h[poz + 2] - h[poz + 1]) - abs(h[poz + 2] - h[poz]);
  return wyn;
} /* zm_wart1 */


int main()
{
  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%d", &h[i]);
  long long wyn[MAX_N];
  long long wyn0 = licz();
  for (i = 0; i < n; i++)
    wyn[i] = wyn0;
  for (i = 0; i < n; i++)
    for (j = i + 1; j < n; j++)
      if (j > i + 1)
      {
        wyn[i] = min(wyn[i], wyn0 - zm_wart(h[i], i) - zm_wart(h[j], j)
                                  + zm_wart(h[i], j) + zm_wart(h[j], i));
        wyn[j] = min(wyn[j], wyn0 - zm_wart(h[i], i) - zm_wart(h[j], j)
                                  + zm_wart(h[i], j) + zm_wart(h[j], i));
      } /* if */
      else
      {
        wyn[i] = min(wyn[i], wyn0 + zm_wart1(i));
        wyn[j] = min(wyn[j], wyn0 + zm_wart1(i));
      } /* else */
  for (i = 0; i < n; i++)
    printf("%lld\n", wyn[i]);
  return 0;
} /* main */
