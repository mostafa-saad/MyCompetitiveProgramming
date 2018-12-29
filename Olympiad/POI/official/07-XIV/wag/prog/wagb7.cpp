/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Waga Czworkowa (WAG)                                       *}
{*   Plik:    wagb7.cpp                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Iterujemy sie po wszystkich sumach wag odwaznikow, ktore   *}
{*            jest sens umieszczac na szalce wraz ze zlotem (uwaga:      *}
{*            obcinamy liczbe krokow petli). Plus robimy spamietywanie   *}
{*            malych wartosci.                                           *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>

long long n;
int wyn, ile;
int akt;
char t[65535]; /* tyz sie miesci w cache'u */

inline int licz(long long x)
{
  akt = 0;
  while (x > 65534)
  {
    akt += int(x & 3);
    x >>= 2;
  }
  return akt + (int)t[x];
}

void poczatek()
{
  for (int i = 1; i < 65535; i++)
    t[i] = (i & 3) + t[i >> 2];
}

int main()
{
  poczatek();
  scanf("%lld", &n);
  wyn = 1000000; /* duzo */
  /* Obciecie */
  long long petla = n;
  if (n > 5000000)
    petla = 5000000;
  for (long long i = 0; i <= petla; i++)
  {
    int x = licz(n + i);
    if (x > wyn)
      continue;
    x += licz(i);
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
