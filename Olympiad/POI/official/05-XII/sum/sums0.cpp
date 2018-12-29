/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SUM (Sumy Fibbonacciego)                       *
 *   Plik:                sums0.cpp                                      *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                        Program za kazdym spotkaniem 2 eliminuje ja    *
 *                        i zaczyna od poczatku. Czas: o(n^3)            *
 *                                                                       *
 *************************************************************************/

#include<stdio.h>
#include<iostream>
using namespace std;

int slowo1[1000100];
int slowo2[1000100];
int wynik[1000100];
int n, m, dlugosc_wyniku;


int max(int x, int y)
{
  return (x > y ? x : y);
}

void czysc()
{
  for (int i = 0; i < 1000; i++)
    wynik[i] = 0;
}

void wczytaj()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &slowo1[i]);
  }
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%d", &slowo2[i]);
  }
  return;
}

void dodaj()
{
  for (int i = 0; i < n; i++)
    wynik[i] = slowo1[i];
  for (int i = 0; i < m; i++)
    wynik[i] += slowo2[i];
  dlugosc_wyniku = max(n, m);
}

void normalizuj()
{
  bool zmiana = true;
  if (wynik[0] == 2) {
    wynik[0] = 0;
    wynik[1]++;
  }
  dlugosc_wyniku += 5;
  while (zmiana) {
    zmiana = false;
    for (int i = 1; i < dlugosc_wyniku; i++) {
      while ((wynik[i - 1] > 0) && (wynik[i] > 0)) {
        wynik[i - 1]--;
        wynik[i]--;
        wynik[i + 1]++;
      }
      if (wynik[i] >= 2) {
        wynik[i] -= 2;
        wynik[i + 1]++;
        if (i >= 2) {
          wynik[i - 2]++;
        }
        if (i == 1) {
          wynik[i - 1]++;
        }
        zmiana = true;
        i = dlugosc_wyniku;
      }
    }
  }
  while ((dlugosc_wyniku != 0) && (wynik[dlugosc_wyniku - 1] == 0))
    dlugosc_wyniku--;
  return;
}


void wypisz_wynik()
{
  printf("%d", dlugosc_wyniku);
  for (int i = 0; i < dlugosc_wyniku; i++)
    printf(" %d", wynik[i]);
  printf("\n");
  return;
}



int main()
{
  wczytaj();
  dodaj();
  normalizuj();
  wypisz_wynik();
  return 0;
}
