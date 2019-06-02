/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Tetris attack (TET)                                        *}
{*   Plik:    tetb1.cpp                                                  *}
{*   Autor:   Pawel Parys                                                *}
{*   Opis:    Rozwiazanie bledne - po prostu wyciagamy na gore pare      *}
{*            najwy¿szego elementu.                                      *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,b,c) for (int a=(b); a<=(c); ++a)
#define FORD(a,b,c) for (int a=(b); a>=(c); --a)

using namespace std;

////////////////////////////////////////////

#define SIZE (2*50000)

int tab[SIZE], ile; // aktualna zawarto¶æ i rozmiar stosu

int mem[SIZE]; // pocz±tkowe u³o¿enie stosu
int N; // ile jest liczb
int ilew = 0; // ile bêdzie ruchów

void licz(bool wypisuj)
{
  ile = 2*N;
  REP(a, 2*N)
    tab[a] = mem[a];
  while (ile)
  {
    // najpierw znajdz pare do najwyzszego
    int pos = ile-2;
    while (tab[pos]!=tab[ile-1])
      --pos;
    // Przesuwamy go w gore i w razie czego robimy.  Jedyna
    // redukcja, jaka sie moze zdarzyc, to element, ktory
    // zjechal w dol moze sie zredukowac z tym, co byl nizej.
    int pos2 = pos-1; // ostatni element ponizej naszego (moze -1)
    while (pos!=ile-2)
    {
      ++ilew;
      if (wypisuj) // +1, bo u nas pozycje od 0
        printf("%d\n", pos2+1+1);
      ++pos;
      if (pos2>=0 && tab[pos2]==tab[pos])
        --pos2; // redukcja
      else
        tab[++pos2] = tab[pos]; // przepisanie
    }
    ile = pos2+1;
  }
}

int main()
{
  scanf("%d", &N);
  REP(a, 2*N)
  {
    scanf("%d", &mem[a]);
    --mem[a]; // u nas liczby bêd± od 0 do N-1
  }
  licz(false);
  printf("%d\n", ilew);
  licz(true);
}
