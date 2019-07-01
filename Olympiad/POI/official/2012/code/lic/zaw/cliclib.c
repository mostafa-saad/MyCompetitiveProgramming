/*
  Przykladowa biblioteka licytacji dla zawodnikow
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "cliclib.h"

static int n;
static int zainicjowane = 0; // czy zostala juz wywolana funkcja inicjuj
static int stos, stawka;
static int kolej; // aktualny gracz

// Inicjuje gre pomiedzy Alojzym i Bajtazarem
int inicjuj() {
  if (zainicjowane) {
    fprintf(stderr, "ERROR: Ponowna inicjalizacja biblioteki :(\n");
    printf("ZLE\n");
    exit(0);
  }
  fprintf(stderr, "Inicjalizowanie: Podaj wartosc n\n");
  scanf("%d", &n);
  if (n < 1) {
    fprintf(stderr, "ERROR: Nieprawidlowa wartosc n :(\n");
    printf("ZLE\n");
    exit(0);
  }
  zainicjowane = 1;
  stos = 0;
  stawka = 1;
  kolej = 1;
  return n;
}

// Aktualizuje stos i stawke, biorac pod uwage ruch x
static void wykonaj_ruch(int x) {
  if (x == 1) {
    stos = stos + stawka;
    stawka = 1;
  }
  else if (x == 2) {
    stawka = stawka * 2;
  }
  else if (x == 3) {
    stawka = stawka * 3;
  }
}

// Wykonuje ruch Alojzego
void alojzy(int x) {
  if (!zainicjowane) {
    fprintf(stderr, "ERROR: Brak inicjalizacji biblioteki :(\n");
    printf("ZLE\n");
    exit(0);
  }
  if (kolej != 1) {
    fprintf(stderr, "ERROR: Ruch Alojzego bez wczesniejszego ruchu Bajtazara :(\n");
    printf("ZLE\n");
    exit(0);
  }
  fprintf(stderr, "Ruch Alojzego\n");
  fprintf(stderr, "Liczba kamykow na stosie: %d, aktualna stawka: %d\n", stos, stawka);
  if (stos + stawka >= n) {
    fprintf(stderr, "Wygrana Bajtazara - program zawodnika uzyskuje 0 punktow :(\n");
    printf("ZLE\n");
    exit(0);
  }
  if (x < 1 || x > 3) {
    fprintf(stderr, "ERROR: Nieprawidlowy ruch Alojzego :(\n");
    printf("ZLE\n");
    exit(0);
  }
  if (x == 1) fprintf(stderr, "Alojzy pasuje\n");
  if (x == 2) fprintf(stderr, "Alojzy podwaja stawke\n");
  if (x == 3) fprintf(stderr, "Alojzy potraja stawke\n");
  kolej = 2;
  wykonaj_ruch(x);
}

// Generuje i wykonuje ruch Bajtazara
int bajtazar() {
  if (!zainicjowane) {
    fprintf(stderr, "ERROR: Biblioteka nie zostala zainicjalizowana :(\n");
    printf("ZLE\n");
    exit(0);
  }
  if (kolej != 2) {
    fprintf(stderr, "ERROR: Pytanie o ruch Bajtazara przed wykonaniem ruchu Alojzego :(\n");
    printf("ZLE\n");
    exit(0);
  }
  fprintf(stderr, "Ruch Bajtazara\n");
  fprintf(stderr, "Liczba kamykow na stosie: %d, aktualna stawka: %d\n", stos, stawka);
  if (stos + stawka >= n) {
    fprintf(stderr, "Bajtazar pasuje, Alojzy wygral :)\n");
    printf("OK\n");
    exit(0);
  }
  fprintf(stderr, "Jaki ruch powinien wykonac Bajtazar? 1: Pas, 2: Podwojenie stawki, 3: Potrojenie stawki?\n");
  int x;
  scanf("%d", &x);
  if (x < 1 || x > 3) {
    fprintf(stderr, "ERROR: Nieprawidlowy ruch Bajtazara :(\n");
    printf("ZLE\n");
    exit(0);
  }
  kolej = 1;
  wykonaj_ruch(x);
  return x;
}
