/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Waga Czworkowa (WAG)                                       *}
{*   Plik:    wagb8.cpp                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Iterujemy sie po wszystkich sumach wag odwaznikow, ktore   *}
{*            jest sens umieszczac na szalce wraz ze zlotem.             *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <cstring>

long long n;
int wyn, ile;
int akt, poz;

inline int licz(long long x)
{
  poz = akt = 0;
  while (x)
  {
    akt += int(x & 3);
    x >>= 2;
  }
  return akt;
}

int main()
{
  scanf("%lld", &n);
  wyn = 1000000; /* duzo */
  for (long long i = 0; i <= n; i++)
  {
    int x = licz(i) + licz(n + i);
    if (x < wyn)
    {
      wyn = x;
      ile = 1;
    }
    else if (x == wyn)
      ile++;
  }
  printf("%d\n", ile);
  return 0;
}
