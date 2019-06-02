/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Klocki (KLO)                                               *}
{*   Plik:    klo5.cpp                                                   *}
{*   Autor:   Pawel Parys                                                *}
{*   Opis:    Rozwiazanie: Poprawne w O(n*log(n)), wykorzystuje          *}
{*            wyszukiwanie binarne                                       *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

#define REP(a, n) for (int a = 0; a<(n); ++a)
#define FOR(a, b, c) for (int a = (b); a<=(c); ++a)

#define INF 1000000000

int val[100000]; // wartosci na i-tym klocku (od 0)
int N;

pair<int, int> posortuj[100000]; // pary (val[i], -i)

int tab[100002]; 
// przy ustalonym i=wysokosci stosu po wyjeciu, tab[c] jest to
// (minimalna wysokosc oryginalnej wie¿y)-i potrzebnej do uzyskania 
// wie¿y wysoko¶ci i z c poprawnymi klockami

pair<int, int> historia[100005]; // pary (c, h) do odtworzenia co usuwano
int ileh = 0;

int wynik[100000]; // usuwane klocki
int ilew = 0;

int main()
{
  scanf("%d", &N);
  REP(a, N)
  {
    scanf("%d", &val[a]);
    --val[a];
    posortuj[a] = make_pair(val[a], -a);
  }
  REP(c, N+2)
    tab[c] = INF;
  tab[0] = 0;
  sort(posortuj, posortuj+N);

  int best = 0;
  REP(p, N)
  {
    int h = -posortuj[p].second;
    int ah = posortuj[p].first;
    int i = ah+1; // wysokosc wynikowej wiezy
    int c0 = lower_bound(tab, tab+N+2, h+1-(i-1))-tab;
//    printf("klocek %d (%d)\n", h+1, ah+1);
    if (h-ah<tab[c0] && c0)
    {
//      printf("Poprawiam dla c0=%d na %d (%d)\n", c0, h+1-i, h+1);
      tab[c0] = h+1-i;
      historia[ileh++] = make_pair(c0, h);
    }
    best >?= c0;
  }
//  printf("%d\n", best);

  /// WYPISYWANIE WYNIKU
  int poprz = -1; // poprzedni (wyzszy) klocek na swojej pozycji (na poczatku nieznany)
  while (best)
  {
    while (historia[ileh-1].first!=best)
      --ileh;
    int cur = historia[ileh-1].second;
//    printf("%d (%d)\n", cur+1, val[cur]+1);
    if (poprz>=0)
    {
      int diff = (poprz-val[poprz])-(cur-val[cur]);
      FOR(u, cur+1, cur+diff)
        wynik[ilew++] = u;
    }
    poprz = cur;
    --best;
  }
  if (poprz>=0) // ponizej najnizszego
  {
    int diff = (poprz-val[poprz]);
    FOR(u, 0, diff-1)
      wynik[ilew++] = u;
  }
  printf("%d\n", ilew);
  REP(a, ilew)
    printf("%s%d", a ? " " : "", 1+wynik[a]);
  printf("\n");
}
