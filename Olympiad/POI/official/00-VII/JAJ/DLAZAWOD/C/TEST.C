/* Przykˆadowy program nadzoruj¥cy przybieg eksperymentu
   (korzysta z modulu jaj.c / jaj.cpp). */
/* Autor: Pawel Wolff */

#include "jajmod.h"
#include "jaj.h"
#include <stdio.h>

int main(void)
{
  int ile_rozbitych = 0;
  long int liczba_pytan = 0, wyt;

  printf("Podaj wysokosc drapacza: ");
  scanf("%ld", &wysokosc);
  printf("Podaj liczbe jajek: ");
  scanf("%d", &jajka);
  printf("Podaj wytrzymalosc jajka: ");
  scanf("%ld", &wyt);

  nowy_eksperyment();
  do {
    if (ile_rozbitych < jajka) {
      daj_pytanie();
      liczba_pytan++;
    }
    else {
      printf("Wszystkie jajka zostaly juz rozbite!\n");
      return 1;
    }

    if (pietro < 0 || pietro > wysokosc) {
      printf("Pietro poza zakresem!\n");
      return 1;
    }

    odpowiedz = (pietro <= wyt) ? TAK : (ile_rozbitych++, NIE);

    analizuj_odpowiedz();

  } while (wiem != TAK);

  if (x == wyt)
    printf("OK\n");
  else
    printf("ZLE\n");
  printf("liczba pytan = %ld, wyznaczona wytrzymalosc = %ld\n",
         liczba_pytan, x);

  return 0;
}
