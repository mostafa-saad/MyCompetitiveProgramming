/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LOT (Lot na Marsa)                             *
 *   Plik:                lot.cpp                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie niepoprawne (heurystyczne)         *
 *                        Wpierw sprawdza warunek suma p_i>=suma d_i     *
 *                        Nastepnie wypisuje TAK tym wierzcholkom,       *
 *                        z ktorych idac w jedna ze stron, dojdzie sie   *
 *                        dalej niz do 10 wierzcholka                    *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

// n - wielkosc tablicy
// p,d - paliwa i drogi
int n;
int p[MAX_N], d[MAX_N];

// Wczytywanie
void wczyt(void)
{
  int i;
  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%d%d", &(p[i]), &(d[i]));
}

// Sprawdzenie, czy suma p >= suma d
int sumuj(void)
{
  int suma = 0, i;
  for (i = 0; i < n; i++)
    suma += p[i] - d[i];
  return suma;
}

// Funkcja przechodzaca od wierzcholka w lewo - tak na pale
int przejdz_lewo(int start)
{
  int suma = 0, i, ilejuz = 0;
  for (i = start; i < n; i++) {
    suma += p[i] - d[i];
    if (suma < 0)
      return 0;
    if (ilejuz++ > 10)
      break;
  }
  ilejuz = 0;
  for (i = 0; i < start; i++) {
    suma += p[i] - d[i];
    if (suma < 0)
      return 0;
    if (ilejuz++ > 10)
      break;
  }
  return 1;
}

// I w druga strone
int przejdz_prawo(int start)
{
  int suma = 0, i, ilejuz = 0;;
  for (i = start; i > 0; i--) {
    suma += p[i] - d[i - 1];
    if (suma < 0)
      return 0;
    if (ilejuz++ > 10)
      break;
  }
  ilejuz = 0;
  suma += p[0] - d[n - 1];
  if (suma < 0)
    return 0;
  for (i = n - 1; i > start; i--) {
    suma += p[i] - d[i - 1];
    if (suma < 0)
      return 0;
    if (ilejuz++ > 10)
      break;
  }
  return 1;
}

// Rozwiazywanie zadania 
void rozwiaz(void)
{
  int i;
  if (sumuj() < 0) {
    for (i = 0; i < n; i++)
      printf("NIE\n");
  }
  else {
    for (i = 0; i < n; i++) {
      if (przejdz_lewo(i) + przejdz_prawo(i) > 0)
        printf("TAK\n");
      else
        printf("NIE\n");
    }
  }
}

// MAIN
int main(void)
{
  wczyt();
  rozwiaz();
  return 0;
}
