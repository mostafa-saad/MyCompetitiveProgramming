/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Klocki (KLO)                                               *}
{*   Plik:    klob8.cpp                                                  *}
{*   Autor:   Pawel Parys                                                *}
{*   Opis:    Rozwiazanie: Niepoprawne, klocki o tej samej wartosci sa   *}
{*            rozwa¿ane w b³êdnej kolejno¶ci                             *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

#define REP(a, n) for (int a = 0; a<(n); ++a)
#define FOR(a, b, c) for (int a = (b); a<=(c); ++a)

#define SIZE (1<<17) // ponad 100000

int tab[2*SIZE]; // drzewko licznikowe:
  // maksimum z wysokosci wiezy po i-val[i]
  // tzn. li¶cie s± indeksowane i-val[i]
  // w kazdym korzeniu jest maksimum dla poddrzewa
int gdzie_max[2*SIZE]; // dla ktorego i jest to maksimum

int find_max(int next, int &gdzie)
{   // szuka maksimum wsrod pozycji <next,
    // w gdzie zwraca numer klocka, dla ktorego jest to maksimum
  int size = SIZE;
  int pos = 1;
  int wyn = 0;
  while (size>1)
  {
    size /= 2;
    pos *= 2;
    if (next>=size)  // idz do prawego syna - wez maksimum z lewego
    {
      if (tab[pos]>wyn)
      {
        wyn = tab[pos];
        gdzie = gdzie_max[pos];
      }
      ++pos;
      next -= size;
    }
  }
  return wyn;
}

void wstaw(int cel, int val, int gdzie)
{   // wstawia now± warto¶æ val na pozycji cel, 
    // o ktorej wiadomo, ze pochodzi od klocka gdzie
  int size = SIZE;
  int pos = 1;
  while (size)
  {
    if (val>tab[pos])
    {
      tab[pos] = val;
      gdzie_max[pos] = gdzie;
    }
    size /= 2;
    pos *= 2;
    if (cel>=size)
    {
      ++pos;
      cel -= size;
    }
  }
}

int val[100000]; // wartosci na i-tym klocku (od 0)
int N;

int prev[100000]; // poprzedni klocek na dobrej wysokosci

pair<int, int> posortuj[100000]; // pary (val[i], i)

int main()
{
  scanf("%d", &N);
  REP(a, N)
  {
    scanf("%d", &val[a]);
    --val[a];
    posortuj[a] = make_pair(val[a], a);
    prev[a] = -1;
  }
  sort(posortuj, posortuj+N);
  int best = 0, best_pos = -1;
  REP(p, N)
  {
    int a = posortuj[p].second;
//    printf("Liczê dla %d, val=%d\n", a, val[a]);
    if (val[a]>a)
      continue; // ten klocek nie moze byc na swoim miejscu, musialby podskoczyc
    int wyn = 1+find_max(a-val[a]+1, prev[a]);
//    printf("   wyn=%d poprz=%d (poz=%d)\n", wyn, prev[a], a-val[a]);
    wstaw(a-val[a], wyn, a);
    if (wyn>best)
    {
      best = wyn;
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
