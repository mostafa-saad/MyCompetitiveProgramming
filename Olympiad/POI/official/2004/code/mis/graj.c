// Zadanie MIS
// program generujacy rozgrywke i zwracajacy jej wynik, wersja C/C++
// Gracz Lolek gra optymalnie, gracz Bolek jest testowany
// Lukasz Kowalik, 14.02.2004
// Poprawki: Rafal Rusin, 2004.03.16

#include "mis.h"
#include <stdio.h>
#include <stdlib.h>

#define UNDEF -1

static int m, p, mpo;
static int bm, bp, lm, lp;

static int przegr_kol [MAX_MPO+1];
static int przegr_prz [2*MAX_MPO+1];

void inicjuj (int m, int p, int mpo)
{
  int kolumna, przekatna;
  int i;

  for (kolumna = 0; kolumna <= mpo; kolumna++)
    przegr_kol [kolumna] = UNDEF;

  for (i = -mpo; i <= mpo; i++)
    przegr_prz [i + mpo] = UNDEF;

  przegr_kol [0] = 0;
  przegr_prz [0 + mpo] = 0;
  przekatna = 1;

  kolumna = 1;

  while (kolumna + przekatna <= mpo)
  {
    if (przegr_kol [kolumna] == UNDEF)
    {
      przegr_kol [kolumna] = kolumna + przekatna;
      przegr_kol [kolumna + przekatna] = kolumna;
      przegr_prz [przekatna + mpo] = kolumna;
      przegr_prz [-przekatna + mpo] = kolumna + przekatna;
      przekatna++;
    }
    kolumna++;
  }
}

void ruch_lolka (int m, int p, int *lm, int *lp)
{
  int w, k;

  w = m % (mpo + 1);
  k = p % (mpo + 1);

  if ((przegr_kol [k] != UNDEF) && (w > przegr_kol [k]))
  {
    *lm = w - przegr_kol [k];
    *lp = 0;
  }
  else
  if ((przegr_kol [w] != UNDEF) && (k > /*przegr_wie [w] = */ przegr_kol [w]))
  {
    *lp = k - przegr_kol [w];
    *lm = 0;
  }
  else
  if ((przegr_prz [w - k + mpo] != UNDEF) && (k > przegr_prz [w - k + mpo]))
  {
    *lm = k - przegr_prz [w - k + mpo];
    *lp = *lm;
  }
  else
    /* pozycja przegrywajaca, robimy cokolwiek */
    if (m > 0) { *lm = 1; *lp = 0; } else { *lp = 1; *lm = 0; }
}



int main ()
{
  scanf("%d%d%d", &m, &p, &mpo);

  poczatek (m, p, mpo);
  inicjuj (m, p, mpo);

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
      printf ("WRONG\nNiepoprawny ruch!\n");
      exit(0);
    }

    if ((m == 0) && (p == 0))
    {
      printf ("OK\n");
      exit(0);
    }

    //optymalna strategia Lolka
    ruch_lolka (m, p, &lm, &lp);

    m -= lm;
    p -= lp;

    if ((m == 0) && (p == 0))
    {
      printf ("WRONG\nPrzegrana Bolka!\n");
      exit(0);
    }
  }
}


