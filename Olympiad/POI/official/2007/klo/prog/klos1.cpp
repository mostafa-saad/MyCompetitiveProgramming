/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Klocki (KLO)                                               *}
{*   Plik:    klos1.cpp                                                  *}
{*   Autor:   Pawel Parys                                                *}
{*   Opis:    Rozwiazanie: Poprawne, ale wolne: O(n^2), programowanie    *}
{*            dynamiczne bez drzewka licznikowego                        *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

#define REP(a, n) for (int a = 0; a<(n); ++a)
#define FOR(a, b, c) for (int a = (b); a<=(c); ++a)

int val[100000]; // wartosci na i-tym klocku (od 0)
int N;

int T[100000]; // wysokosc najwiekszej wiezy konczacej sie poprawnie tym klockiem
int prev[100000]; // poprzedni klocek na dobrej wysokosci
int best = 0, best_pos = -1;

int main()
{
  scanf("%d", &N);
  REP(a, N)
  {
    scanf("%d", &val[a]);
    --val[a];
    prev[a] = -1;
    T[a] = a-val[a]>=0 ? 1 : 0;
    REP(b, a)
      if (val[b]<val[a] && b-val[b]<=a-val[a] && T[b] && T[b]+1>T[a])
      {
        T[a] = T[b]+1;
        prev[a] = b;
      }
//    printf("a=%d val=%d T=%d prev=%d\n", a, val[a], T[a], prev[a]);
    if (T[a]>best)
    {
      best = T[a];
      best_pos = a;
    }
  }
  /// WYPISYWANIE WYNIKU
  if (best==0)  // nic sie nie da dopasowac, wiec nie trzeba nic usuwac
  {
    printf("0\n\n");
    return 0;
  }
  printf("%d\n", best_pos-val[best_pos]);
  int first = 1; // czy wypisywac spacjê?
  while (best_pos>=0)
  {
    int bpp = prev[best_pos];
    int diff = (best_pos-val[best_pos])-(bpp>=0 ? (bpp-val[bpp]) : 0);
    FOR(x, bpp+1, bpp+diff) // dla bpp==-1 tez jest ok
    {
      printf("%s%d", first ? "" : " ", 1+x);
      first = 0;
    }
    best_pos = bpp;
  }
  printf("\n");
}
