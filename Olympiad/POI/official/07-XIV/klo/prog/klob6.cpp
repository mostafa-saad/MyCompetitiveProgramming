/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Klocki (KLO)                                               *}
{*   Plik:    klob6.cpp                                                  *}
{*   Autor:   Pawel Parys                                                *}
{*   Opis:    Rozwiazanie: Niepoprawne, zachlanne, stara sie ustawic     *}
{*            wieze z klockow o najmniejszych wartosciach.               *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

#define REP(a, n) for (int a = 0; a<(n); ++a)
#define FOR(a, b, c) for (int a = (b); a<=(c); ++a)

int wynik[100000]; // ktore usuwamy
int ile = 0; // ile usuwamy

int N;
pair<int, int> val[100000]; // pary (a_i,i)

int main()
{
  scanf("%d", &N);
  REP(a, N)
  {
    int v;
    scanf("%d", &v);
    --v;
    val[a] = make_pair(v, a);
  }
  sort(val, val+N);
  int poprz_ust = -1; // na jakiej wysokosci jest ostatni ustalony klocek
  int poprz_skad = -1; // skad jest ten klocek
  REP(p, N)
  {
    int a = val[p].second;
    int v = val[p].first;
    int diff = (a-v)-(poprz_skad-poprz_ust); // ile trzeba usunac klockow
    if (poprz_ust<v && poprz_skad<a && diff>=0)
    {
      FOR(x, poprz_skad+1, poprz_skad+diff)
        wynik[ile++] = x;
      poprz_ust = v;
      poprz_skad = a;
    }
  }
  /// WYPISYWANIE WYNIKU
  printf("%d\n", ile);
  REP(a, ile)
    printf("%s%d", a ? " " : "", 1+wynik[a]);
  printf("\n");
}
