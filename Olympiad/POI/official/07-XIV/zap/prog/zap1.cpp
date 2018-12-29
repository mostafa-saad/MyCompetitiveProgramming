/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Zapytania (ZAP)                                            *}
{*   Plik:    zap1.cpp                                                   *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Algorytm o zlozonosci czasowej O(n*sqrt(m)+m*logm),        *}
{*            wyznaczajacy odpowiedzi na kolejne zapytania pojedynczo.   *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

typedef vector<pair<int, int> > Podzial;

int n;
const int m = 50000;

bool pierwsza[m + 1]; /* czy liczba jest pierwsza? */
int min_dzielnik[m + 1]; /* najmniejszy dzielnik pierwszy */

/* Implementacja Sita Eratostenesa */
void sito()
{
  for (int i = 2; i <= m; i++)
    pierwsza[i] = true;
  for (int i = 2; i < m; i++)
    if (pierwsza[i])
    {
      if ((long long)i * i > (long long)m)
        break;
      int j = i * i;
      while (j <= m)
      {
        pierwsza[j] = false;
        if (!min_dzielnik[j])
          min_dzielnik[j] = i;
        j += i;
      }
    }
}

int miu[m + 1]; /* spamietane wartosci funkcji Mobiusa */
int F[m + 1]; /* sumy prefiksowe dla funkcji Mobiusa */

/* Wyznaczanie wartosci funkcji Mobiusa oraz sum prefiksowych */
void Mobius()
{
  for (int i = 1; i <= m; i++)
  {
    int x = i, ostatni = 0, dz_pierwsze = 0;
    bool jest_kwadrat = false;
    while (x > 1)
    {
      int dzielnik = min_dzielnik[x];
      if (pierwsza[x])
        dzielnik = x;
      if (dzielnik == ostatni)
      {
        jest_kwadrat = true;
        break;
      }
      dz_pierwsze++;
      ostatni = dzielnik;
      x /= dzielnik;
    }
    if (jest_kwadrat)
      miu[i] = 0;
    else
      miu[i] = (dz_pierwsze % 2 ? -1 : 1);
  }
  F[0] = 0; /* pusta suma prefiksowa */
  for (int i = 1; i <= m; i++)
    F[i] = F[i - 1] + miu[i];
}

/* Znajdowanie podzialu odpowiadajacego a, poczynajac od punktu start. */
Podzial podziel(int a, int start)
{
  Podzial podzial;
  int pierw = int(floor(sqrt(double(a))));
  for (int i = 1; i <= pierw; i++)
    /* Wzor przepisany prosto z opracowania */
    podzial.push_back(make_pair(a / (i + 1) + 1, a / i));
  /* Techniczne machinacje wykonywane na podziale */
  while (!podzial.empty() && podzial.back().second < start)
    podzial.pop_back();
  if (!podzial.empty())
    podzial.back().first = max(podzial.back().first, start);
  reverse(podzial.begin(), podzial.end());
  return podzial;
}

/* Najbardziej techniczna funkcja, w ktorej nastepuje scalenie podzialow,
 * odpowidajacych a oraz b. */
Podzial scal(Podzial p_a, Podzial p_b)
{
  Podzial podzial;
  int i = 0, j = 0;
  while (i < (int)p_a.size() && j < (int)p_b.size())
  {
    /* W petli utrzymywany jest niezmiennik, ze a[i].first=b[j].first.
     * Ze wzgledu na odpowiednia implementacje funkcji podziel,
     * niezmniennik ten jest zachowany przed pierwszm wejsciem do petli. */
    int koniec = min(p_a[i].second, p_b[j].second);
    podzial.push_back(make_pair(p_a[i].first, koniec));

    /* Skracamy przedzialy. */
    p_a[i].first = koniec + 1;
    if (p_a[i].first > p_a[i].second)
      i++;
    p_b[j].first = koniec + 1;
    if (p_b[j].first > p_b[j].second)
      j++;
  }
  return podzial;
}

/* Wyznaczanie odpowiedzi na zapytanie Z(a,b). Mozna pokazac (np.
 * eksperymentalnie dla zapytania Z(50000,50000)), ze wynik tej funkcji
 * zawsze zmiesci sie w typie 32-bitowym ze znakiem. */
int Z(int a,int b)
{
  if (a < b)
    swap(a, b);
  /* Odtad mozemy zalozyc, ze a>=b. */
  int pierw = int(floor(sqrt(double(a))));
  int wynik = 0;
  for (int i = 1; i <= pierw; i++)
    wynik += miu[i] * (a / i) * (b / i);
  
  Podzial podzial = scal(podziel(a, pierw + 1), podziel(b, pierw + 1));
  for (int i = 0; i < (int)podzial.size(); i++)
    wynik += (F[podzial[i].second] - F[podzial[i].first - 1]) * 
      (a / podzial[i].first) * (b / podzial[i].first);
  return wynik;
}

int main()
{
  sito();
  Mobius();
  scanf("%d", &n);
  while (n--)
  {
    int a, b, d;
    scanf("%d%d%d", &a, &b, &d);
    printf("%d\n", Z(a / d, b / d));
  }
  return 0;
}
