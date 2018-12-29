/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LOT (Lot na Marsa)                             *
 *   Plik:                lot.cpp                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                                                                       *
 *************************************************************************/
#include <stdio.h>

// Maksymalne N
#define MAX_N 1000000

// Dane: n - liczba stacji
int n;
// Tablice danych p[i] - paliwo, d[i] - drogi
int p[MAX_N], d[MAX_N];

// Tablica czyok - tablica, w ktorej sa odhaczane te miejsca startowe
// z ktorych mozna przejechac cale kolko. Na poczatek jest inicjalizowana
// samymi zerami, jedynka oznacza, ze jest ok.
char czyok[MAX_N];

// Wczytywanie wejscia
void wczyt(void)
{
  int i;

  // Wczytanie N
  scanf("%d", &n);
  // Oraz liczb p[i] i d[i]
  for (i = 0; i < n; i++) {
    scanf("%d%d", &(p[i]), &(d[i]));
    czyok[i] = 0;
  }
}

// Zamiast przepisywac latwiej jest napisac +- to samo dwa razy
// Funkcje wylicz_lewo i wylicz_prawo szukaja startowego pola
// Przy poruszaniu sie zgodnie z numeracja i przeciwnie do numeracji
// Oraz, nastepnie, odpowiednio wyszukuja dobre pola
// Funkcja lewo w dodatku zwraca -1, jesli suma paliw < sumy drog
int wylicz_lewo(void)
{
  int i;
  int szuk_b, szuk_pal, pal;    // Do szukania punktu startowego.
  int suma;                     // Do patrzenia, ktore sa ok do ladowania.

  // Na poczatek nalezy znalezc punkt startowy, czyli tam, gdzie paliwo bylo minimalne.
  szuk_b = 0;
  szuk_pal = 0;
  pal = 0;
  for (i = 0; i < n; i++) {
    pal += p[i] - d[i];         // teraz bedzie stan paliwa przy dojezdzie do i+1 miejsca
    if (pal < szuk_pal) {
      szuk_b = i + 1;
      szuk_pal = pal;
    }
  }
  if (pal < 0)
    return -1;
  if (szuk_b == n)
    szuk_b = 0;

  // Teraz wiemy, ze ruszywszy z szuk_b dojedziemy. Cofamy sie od szuk_b i patrzymy, skad sie da dojechac do szuk_b.
  suma = 0;
  czyok[szuk_b] = 1;
  for (i = szuk_b - 1; i >= 0; i--) {
    suma += p[i] - d[i];
    if (suma >= 0) {
      czyok[i] = 1;
      suma = 0;
    }
  }
  for (i = n - 1; i > szuk_b; i--) {
    suma += p[i] - d[i];
    if (suma >= 0) {
      czyok[i] = 1;
      suma = 0;
    }
  }
  return 0;
}

// +- to samo co powyzej, tylko ze w druga strone.
void wylicz_prawo(void)
{
  int i;
  int szuk_b, szuk_pal, pal;
  int suma;

  // Szukanie startowego punktu.
  szuk_b = 0;
  szuk_pal = 0;
  pal = 0;
  pal += p[0] - d[n - 1];
  if (pal < szuk_pal) {
    szuk_pal = pal;
    szuk_b = n - 1;
  }
  for (i = n - 1; i > 0; i--) {
    pal += p[i] - d[i - 1];
    if (pal < szuk_pal) {
      szuk_pal = pal;
      szuk_b = i - 1;
    }
  }

  // I nastepnie jechanie do tylu od szuk_b;
  suma = 0;
  czyok[szuk_b] = 1;
  for (i = szuk_b + 1; i < n; i++) {
    suma += p[i] - d[i - 1];
    if (suma >= 0) {
      czyok[i] = 1;
      suma = 0;
    }
  }
  suma += p[0] - d[n - 1];
  if (suma >= 0) {
    czyok[0] = 1;
    suma = 0;
  }
  for (i = 1; i < szuk_b; i++) {
    suma += p[i] - d[i - 1];
    if (suma >= 0) {
      czyok[i] = 1;
      suma = 0;
    }
  }
}

// Funkcja rozwiazujaca zadanie
void rozwiaz(void)
{
  int i;

  // Sprawdzamy, czy sumy paliw sie zgadzaja - paliwa > drogi.
  // Jesli tak, wyliczamy, ktore starty sa dobre.
  if (wylicz_lewo() == 0)
    wylicz_prawo();

  // Wypisywanie wyniku
  for (i = 0; i < n; i++)
    if (czyok[i])
      printf("TAK\n");
    else
      printf("NIE\n");
}

int main(void)
{
  // Wczytanie wejscia
  wczyt();
  // Rozwiazanie 
  rozwiaz();
  return 0;
}
