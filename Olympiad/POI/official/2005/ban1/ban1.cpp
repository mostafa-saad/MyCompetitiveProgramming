/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: BAN (Bankomat)                                 *
 *   Plik:                ban1.cpp                                       *
 *   Autor:               Piotr Stañczyk                                 *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
char ciag[1010001];             // lista sekwencji (jedna za druga ze straznikami pomiedzy)
int poczatki[10001];            // Wskazniki na poczatek kolejnych sekwencji
int sekwencje;                  // Ilosc sekwencji
short int wyst[10][1010001];    // Tablica wystapien poszczegolnych cyfr

void Wczytaj_Dane()
{
  scanf("%d\n", &sekwencje);
  int poz = 0, len;
  for (int x = 0; x < sekwencje; x++) {
    poczatki[x] = poz;
    scanf("%d ", &len);
    scanf("%s", &ciag[poz]);
    poz += len;
    ciag[poz++] = 'k';          // Straznik
  }
  poczatki[sekwencje] = poz - 1;
}

void Generuj_Wyst()
{
  int liczniki[10];
  int poz = poczatki[sekwencje], x;
  while (poz >= 0) {
    if (ciag[poz] == 'k') {
      for (x = 0; x < 10; x++) {
        wyst[x][poz] = 0;
        liczniki[x] = poz;
      }
    }
    else {
      liczniki[ciag[poz] - '0'] = poz;
      for (x = 0; x < 10; x++)
        wyst[x][poz] = liczniki[x] - poz;
    }
    poz--;
  }
}

bool CheckPIN(int x)
{
  short int p1, p2, p3, p4;
  int p, y;
  p4 = x % 10;
  x /= 10;
  p3 = x % 10;
  x /= 10;
  p2 = x % 10;
  x /= 10;
  p1 = x;
  for (y = 0; y < sekwencje; y++) {
    p = poczatki[y];
    p += wyst[p1][p];
    p += wyst[p2][p];
    p += wyst[p3][p];
    p += wyst[p4][p];
    if (ciag[p] == 'k')
      return false;
  }
  return true;
}

int main()
{
  Wczytaj_Dane();
  Generuj_Wyst();
  int PIN_OK = 0;
  for (int x = 0; x < 10000; x++)
    if (CheckPIN(x)) {
      PIN_OK++;
    }
  printf("%d\n", PIN_OK);
  return 0;
}
