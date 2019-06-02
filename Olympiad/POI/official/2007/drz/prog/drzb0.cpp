/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Drzewa (DRZ)                                               *}
{*   Plik:    drzb0.cpp                                                  *}
{*   Autor:   Szymon Wasik                                               *}
{*   Opis:    Rozwi±zanie niepoprawne,                                   *}
{*            Z³o¿ono¶æ czasowa: O(n logn n*LEN),                        *}
{*            Z³o¿ono¶æ pamiêciowa: O(n).                                *}
{*            Najpierw sortujemy wszystkie drzewa po wysoko¶ciach.       *}
{*            Nastêpnie dla ka¿dego drzewa próbujemy przesadziæ ko³o     *}
{*            niego jedno z LEN drzew, poprzedzaj±cych je lub            *}
{*            nastêpuj±cych po nim w ci±gu posortowanym. Parametr LEN    *}
{*            zosta³ dobrany tak, aby dla maksymalnych danych program    *}
{*            dzia³a³ podobnie d³ugo jak wzorcówka.                      *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAX_N 50000
#define LEN 80

int n, i, j;
int h[MAX_N];
pair<int, int> sh[MAX_N];
long long wsp, wyn[MAX_N];

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

int zm_wart2(int a, int b)
/* Ta funkcja liczy zmianê warto¶ci wspó³czynnika nieporz±dku w momencie,
 * kiedy zamienimy drzewa a oraz b miejscami. */
{
  return -zm_wart(h[a], a) - zm_wart(h[b], b) +
          zm_wart(h[a], b) + zm_wart(h[b], a);
} /* zm_wart2 */

void try_swap(int a, int b)
{
  if (a < 0 || b < 0 || a >= n || b >= n || a == b)
    return;
  int dif;
  if (a == b - 1)
    dif = zm_wart1(a);
  else if (a == b + 1)
    dif = zm_wart1(b);
  else
    dif = zm_wart2(a, b);
  wyn[a] = min(wyn[i], wsp + dif);
  wyn[b] = min(wyn[b], wsp + dif);
} /* try_swap */

int main()
{
  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%d", h+i);
    sh[i] = make_pair(h[i], i);
  } /* for */
  wsp = licz();
  sort(sh, sh+n);
  for (i = 0; i < n; i++)
    wyn[i] = wsp;
  for (i = 0; i < n; i++)
    for (j = i - LEN; j <= i + LEN; j++)
      if (i - j && j >= 0 && j < n)
      {
        try_swap(sh[i].second, sh[j].second + 1);
        try_swap(sh[i].second, sh[j].second - 1);
      } /* if */
  for (i = 0; i < n; i++)
    printf("%lld\n", wyn[i]);
  return 0;
} /* main */
