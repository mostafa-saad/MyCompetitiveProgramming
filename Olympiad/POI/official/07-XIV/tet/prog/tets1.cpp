/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Tetris attack (TET)                                        *}
{*   Plik:    tets1.cpp                                                  *}
{*   Autor:   Pawel Parys                                                *}
{*   Opis:    Rozwi±zanie podobne do wzorcowego, z tym ¿e:               *}
{*             - Szukanie pierwszego od góry elementu, który nie ma pary *}
{*               wy¿ej, za ka¿dym razem odbywa siê od nowa.              *}
{*             - Podobnie w przypadku redukcji wszystkie nastêpne        *}
{*               elementy s± przesuwane wstecz.                          *}
{*             - Czas dzia³ania jest wiêc O(n^3).                        *}
{*             - Jednak je¶li ¿adna redukcja nie wyst±pi³a w okolicy     *}
{*               zamiany, to nie przegl±damy wszystkich elementów        *}
{*               w poszukiwaniu redukcji.                                *}
{*             - Tutaj odwrotnie ni¿ w rozw. wzorcowym zamiany zaczynamy *}
{*               od góry, a nie od do³u, co trochê optymalizuje, bo mniej*}
{*               elementów trzeba przesuwaæ (tylko te powy¿ej).          *}
{*             - Do wyliczenia liczby ruchów zliczamy ile jest inwersji. *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <algorithm>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,b,c) for (int a=(b); a<=(c); ++a)
#define FORD(a,b,c) for (int a=(b); a>=(c); --a)

using namespace std;

///////////////////////////////////////////

#define SIZE (2*50000)

int tab[SIZE], ile; // aktualna zawarto¶æ i rozmiar stusu

int jest[SIZE], jest_nr = 1; // je¶li dana liczba wystêpuje powy¿ej bie¿±cej
  // pozycji, to na jej pozycji bêdzie jest_nr (dla kolejnych
  // przebiegów bêd± ró¿ne jest_nr).

int N; // ile jest liczb
int ilew = 0; // ile jest inwersji (ile potrzeba ruchów)

int gdzie[SIZE][2]; // gdzie znajduje siê dana liczba (dotyczy pocz±tkowego stosu)
int ile_gdzie[SIZE]; // ile razy juz wczytali¶my dan± liczbê

void licz_ruchy()
{
  REP(a, N)
    REP(b, N)
      if (gdzie[a][0]<gdzie[b][0] 
          && gdzie[b][0]<gdzie[a][1] 
          && gdzie[a][1]<gdzie[b][1])
        ++ilew;
}

void wypisuj()
{
  while (ile)
      FORD(pos, ile-1, 0)
      {
    int A = tab[pos];
    if (jest[A]==jest_nr)
    {
      // znale¼li¶my pozycjê
      printf("%d\n", pos+1); // +1 tylko dlatego,
                 // ze liczymy od 0
      swap(tab[pos], tab[pos+1]);
      int old_ile = ile, cel = pos;
      FOR(zr, pos, old_ile-1)
      {
        if (cel && tab[cel-1]==tab[zr])
          ile -= 2, --cel; // redukcja
        else
          tab[cel++] = tab[zr];
        if (ile==old_ile && zr>=pos+2)
          break; // jesli ani pos-1 z pos, ani
          // pos+1 z pos+2 siê nie zredukowali,
          // to nic wiêcej siê nie zredukuje
      }
      ++jest_nr;
      break; // i jedziemy od nowa
    }
    else
      jest[A] = jest_nr;
      }
}

int main()
{
  scanf("%d", &N);
  ile = 2*N;
  REP(a, ile)
  {
    scanf("%d", &tab[a]);
    --tab[a];
    gdzie[tab[a]][ile_gdzie[tab[a]]++] = a;
  }
  licz_ruchy();
  printf("%d\n", ilew);
  wypisuj();
}
