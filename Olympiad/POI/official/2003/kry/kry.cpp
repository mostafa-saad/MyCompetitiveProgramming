/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Kryszta³                                       *
 *   Plik:                kry.cpp                                        *
 *   Autor:               Krzysztof Onak                                 *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>

/* interfejs komunikacji z aparatur± */
#include "krysztal.h"

using namespace std;

const int MAX_N = 10000;
typedef int Tablica[MAX_N];

// poni¿sze zmienne opisuj± aktualnie rozwa¿any prostok±t
int x, y, szer, wys; // wspó³rzêdne rogu i rozmiary prostok±ta
Tablica poziom1, poziom2, pion1, pion2, ciecie;
  // kolejno wszystkie boki + ciêcie

// wczytuje wszystkie dane na temat brzegu kwadratu
void wczytaj() {
  int n;

  n = rozmiar();

  for (int i = 0; i < n - 1; ++i) pion1[i] = zamroz(1, i+1);  
  for (int i = 0; i < n - 1; ++i) poziom2[i] = zamroz(i+1, n); 
  for (int i = n - 1; i > 0; --i) pion2[i] = zamroz(n, i+1);
  for (int i = n - 1; i > 0; --i) poziom1[i] = zamroz(i+1, 1);
  pion1[n - 1] = poziom2[0];
  poziom2[n - 1] = pion2[n - 1];
  pion2[0] = poziom1[n - 1];
  poziom1[0] = pion1[0];
  x = y = 1;
  szer = wys = n;
}


// oblicza, ile jest krawêdzi typu (1,2) na ¶cie¿ce kryszta³ów
int licz12(int *wsk, int roz) {
  int licznik = 0;
  for (int i = 1; i < roz; ++i)
    if (wsk[i] == 1 && wsk[i - 1] == 2 || wsk[i] == 2 && wsk[i - 1] == 1)
      ++licznik;
  return licznik;
}

// wybiera jeden z prostok±tów
// przyjmujemy, ¿e podzia³ jest pionowy,
// ale odpowiednio podaj±c parametry omijamy pó¼niej to ograniczenie
bool wybierz(int szer, int wys, int podzial, int *poziom1, int *poziom2,
             int *pion1, int *pion2, int *ciecie) {
  int ile12 = licz12(pion1, wys) + licz12(ciecie, wys)
            + licz12(poziom1, podzial + 1) + licz12(poziom2, podzial + 1);
  if (ile12 % 2 == 0) { // drugi prostokat
    for (int i = 0; i < wys; ++i) pion1[i] = ciecie[i];
    for (int i = podzial; i < szer; ++i) {
      poziom1[i - podzial] = poziom1[i];
      poziom2[i - podzial] = poziom2[i];
    }
    return true;
  } else { // pierwszy prostokat
    for(int i = 0; i < wys; ++i) pion2[i] = ciecie[i];
    return false;
  }
}

// dzieli aktualny prostok±t
void podziel() {
  if (szer > wys) { // podzia³ pionowy
    int podzial = szer / 2;
    // wyznaczamy ciecie
    for(int i = 1; i < wys - 1; ++i)
      ciecie[i] = zamroz(x + podzial, y + i);
    ciecie[0] = poziom1[podzial];
    ciecie[wys - 1] = poziom2[podzial];
    // dokonujemy wyboru
    if (wybierz(szer, wys, podzial, poziom1, poziom2, pion1, pion2, ciecie)) {
      szer -= podzial;
      x += podzial;
    } else {
      szer = podzial + 1;
    }
  } else { // podzia³ poziomy
    int podzial = wys / 2;
    // wyznaczamy ciecie
    for(int i = 1; i < szer - 1; ++i)
      ciecie[i] = zamroz(x + i, y + podzial);
    ciecie[0] = pion1[podzial];
    ciecie[szer - 1] = pion2[podzial];
    // dokonujemy wyboru
    if (wybierz(wys, szer, podzial, pion1, pion2, poziom1, poziom2, ciecie)) {
      wys -= podzial;
      y += podzial;
    } else {
      wys = podzial + 1;
    }
  }
}

void znajdzWynik() {
  int czworka[2][2];
  // kopiujemy informacje o stanie kryszta³ów
  for(int i = 0; i < 2; ++i) {
    czworka[0][i] = pion1[i];
    czworka[1][i] = pion2[i];
  }
  // szukamy niestabilnej pary
  for(int x1 = 0; x1 < 2; ++x1)
    for(int x2 = 0; x2 < 2; ++x2)
      for(int y1 = 0; y1 < 2; ++y1)
        for(int y2 = 0; y2 < 2; ++ y2)
	  if (czworka[x1][y1] == -czworka[x2][y2]) {
	    niestabilna(x + x1, y + y1, x + x2, y + y2);
	    return;
	  }
  fprintf(stderr,"kry.cpp: Nie znaleziono pary!\n");
  exit(1);
}

int main() {
  wczytaj();
  while (szer > 2 || wys > 2)
    podziel();
  znajdzWynik();
}
