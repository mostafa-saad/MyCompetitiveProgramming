/* Uproszczony program grajacy z trywialna strategia Lolka (wersja dla zawodnika) */
#include "mis.h"
#include <stdio.h>
#include <stdlib.h>

int m, p, mpo;
int bm, bp, lm, lp;

int main ()
{
  scanf("%d%d%d", &m, &p, &mpo);

  poczatek (m, p, mpo);

  while (1)
  {
    ruch_bolka (m, p, &bm, &bp);

    m -= bm;
    p -= bp;

    if ((m < 0) || (p < 0) ||
       ((bm > 0) && (bp > 0) && (bm != bp)) ||
       (bm > mpo) || (bp > mpo) ||
       ((bm == 0) && (bp == 0)))
    {
      printf ("Niepoprawny ruch!\n");
      exit(0);
    }

    if ((m == 0) && (p == 0))
    {
      printf ("Wygrana Bolka!\n");
      exit(0);
    }

    //trywialna strategia Lolka
    lm = 0; lp = 0;
    if (m > 0) lm = 1; else lp = 1;

    m -= lm;
    p -= lp;

    if ((m == 0) && (p == 0)) 
    {
      printf ("Przegrana Bolka!\n");
      exit(0);
    }
  }
}


