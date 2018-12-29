/*
  Implementacja przyk³adowego modulu HSM dla zawodnika w C/C++
  Autor: Tomek Czajka
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hsm.h"

static int zainicjowany = 0;

static int zaszyfrowany[4];
static int zapytania = 0;

static void inicjuj() {
  int i,x;
  char buf[100];
  
  printf("Podaj zaszyfrowany numer karty (szesnastkowo): ");
  scanf("%s",buf);
  if(strlen(buf)<4) {
    printf("Za krotki\n");
    exit(1);
  }
  for(i=0;i<4;++i) {
    if(buf[i]>='0' && buf[i]<='9') x=buf[i]-'0';
    else if(buf[i]>='a' && buf[i]<='f') x=buf[i]-'a'+10;
    else if(buf[i]>='A' && buf[i]<='F') x=buf[i]-'A'+10;
    else {
      printf("Zla litera\n");
      exit(1);
    }
    zaszyfrowany[i] = x;
  }
  zainicjowany = 1;
}

int sprawdz(int p[], int a[]) {
  int i;
  
  if(!zainicjowany) inicjuj();
  
  ++zapytania;

  for(i=0;i<4;++i) {
    if(p[i]<0 || p[i]>9) {
      printf("PIN spoza zakresu\n");
      exit(1);
    }
  }
  for(i=0;i<16;++i) {
    if(a[i]<0 || a[i]>9) {
      printf("element tablicy konwersji spoza zakresu\n");
      exit(1);
    }
  }
  
  for(i=0;i<4;++i) {
    if(p[i] != a[zaszyfrowany[i]])
      return 0;
  }
  return 1;
}

void wynik(int p[]) {
  int i;
  int a[16];
  
  for(i=0;i<16;++i) a[i]=i%10;
  if(sprawdz(p,a)) printf("OK\n");
  else printf("ZLE\n");
  --zapytania;
  printf("Liczba zapytan: %d\n", zapytania);
  exit(0);
}
