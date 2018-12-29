/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Klocki (KLO)                                              *
 *   Plik:     klob3.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Wybieramy fragment ciagu, w ktorym roznica maksymalnej i  *
 *             minimalnej wartosci ciagu jest minimalna.                 *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

#define MAX_N 100000

int n, k;
int h[MAX_N];

multiset<int> zb;

int main()
{
  /* Odczyt */
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++)
    scanf("%d", h + i);

  int best = 2000000010; /* duzo */
  int besti = 0;
  for (int i = 0; i < k - 1; i++)
    zb.insert(h[i]);
  for (int i = k - 1; i < n; i++)
  {
    zb.insert(h[i]);
    multiset<int>::iterator it = zb.end();
    it--;
    int akt = *it - *(zb.begin());
    if (akt < best)
    {
      best = akt;
      besti = i - (k - 1);
    }
    zb.erase(zb.find(h[i - (k - 1)]));
  }

  /* Wypisywanie wyniku */
  nth_element(h + besti, h + besti + k / 2, h + besti + k);
  long long wynik = 0LL;
  for (int i = besti; i < besti + k; i++)
    wynik += abs(h[i] - h[besti + k / 2]);
  printf("%lld\n", wynik);
  for (int i = 0; i < besti; i++)
    printf("%d\n", h[i]);
  for (int i = besti; i < besti + k; i++)
    printf("%d\n", h[besti + k / 2]);
  for (int i = besti + k; i < n; i++)
    printf("%d\n", h[i]);
  return 0;
}
