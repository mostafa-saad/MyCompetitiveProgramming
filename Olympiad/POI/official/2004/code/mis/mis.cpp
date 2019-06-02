/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Misie-Patysie                                  *
 *   Plik:                mis.cpp                                        *
 *   Autor:               £ukasz Kowalik                                 *
 *************************************************************************/

#include "mis.h"

#define UNDEF		-1

int _mpo;

int przegr_kol [MAX_MPO+1];
int przegr_prz [2*MAX_MPO+1];

void poczatek (int m, int p, int mpo)
{
  int kolumna, przekatna;
  int i;

  _mpo = mpo;

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


void ruch_bolka (int m, int p, int *bm, int *bp)
{
  int w, k;

  w = m % (_mpo + 1);
  k = p % (_mpo + 1);

  if ((przegr_kol [k] != UNDEF) && (w > przegr_kol [k]))
  {
    *bm = w - przegr_kol [k];
    *bp = 0;
  }
  else
  if ((przegr_kol [w] != UNDEF) && (k > /*przegr_wie [w] = */ przegr_kol [w]))
  {
    *bp = k - przegr_kol [w];
    *bm = 0;
  }
  else
  if ((przegr_prz [w - k + _mpo] != UNDEF) && (k > przegr_prz [w - k +  _mpo]))
  {
    *bm = k - przegr_prz [w - k + _mpo];
    *bp = *bm;
  }
  else {
    /* pozycja przegrywajaca, robimy cokolwiek */
	*bm=0; *bp=0;
    //if (m > 0) { *bm = 1; *bp = 0; } else { *bp = 1; *bm = 0; }
  }
}

