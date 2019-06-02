/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Klocki (KLO)                                               *}
{*   Plik:    klob4.cpp                                                  *}
{*   Autor:   Pawel Parys                                                *}
{*   Opis:    Rozwiazanie: Niepoprawne, zachlanne, bierze pierwszy klocek*}
{*            ktory moze byc jeszcze na dobrym miejscu i go ustala       *}
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

int main()
{
  scanf("%d", &N);
  int poprz_ust = -1; // na jakiej wysokosci jest ostatni ustalony klocek
  int poprz_skad = -1; // skad jest ten klocek
  REP(a, N)
  {
    int val;
    scanf("%d", &val);
    --val;
    int diff = (a-val)-(poprz_skad-poprz_ust); // ile trzeba usunac klockow
    if (poprz_ust<val && diff>=0)
    {
      FOR(x, poprz_skad+1, poprz_skad+diff)
        wynik[ile++] = x;
      poprz_ust = val;
      poprz_skad = a;
    }
  }
  /// WYPISYWANIE WYNIKU
  printf("%d\n", ile);
  REP(a, ile)
    printf("%s%d", a ? " " : "", 1+wynik[a]);
  printf("\n");
}
