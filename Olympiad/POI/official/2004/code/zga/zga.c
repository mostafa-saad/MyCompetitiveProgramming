/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Zgadywanka                                     *
 *   Plik:                zga.c                                          *
 *   Autor:               £ukasz Kowalik                                 *
 *************************************************************************/

/*
£ukasz Kowalik, 13.05.2003

strategia bardzo bliska optymalnej.
prawdopodobienstwa sukcesu dla k=2,3,..8 wyznaczone doswiadczalnie,
tzn. uruchomiono ten program 7 razy na 1.000.000 zestawach dla ILE_LICZB=2,3,..8.
Liczba sukcesów podzielona przez 1.000.000 da³a przybli¿one prawdopodobieñstwo.

dla ka¿dej mo¿liwej odpowiedzi program oblicza prawdopodobieñstwo sukcesu,
je¶li wybrana zostanie w³a¶nie ta odpowied¼. Wybiera tê odpowied¼, dla której prawdopo-
dobieñstwo by³o najwiêksze.
*/

#include <stdio.h>
#include "zga.h"

#define PUSTE -1.0

//newton[n][k] = symbol newtona; liczba podzbiorów k-elementowych zbioru n-elementowego.
int newton [ILE_LICZB+1][ILE_LICZB+1];

//pr_sukc[k] prawdopodobienstwo sukcesu naszej strategii dla k liczb
double pr_sukc [ILE_LICZB + 1] =
  {1, 1, 0.750432, 0.518525, 0.343103, 0.221183, 0.139890, 0.087850, 0.054212, 0.033015};


double t [ILE_LICZB + 2];


void gen_newton ()
{
  int i, j;
  for (i = 0; i <= ILE_LICZB; i++)
  {
    newton [i][0] = 1;
    newton [i][i] = 1;
    for (j = 1; j < i; j++)
      newton [i][j] = newton [i - 1][j - 1] + newton [i - 1][j];
  }
}

void inicjalizuj()
{
  gen_newton();
}

void nowa_rozgrywka ()
{
  int j;

  for (j=1; j <= ILE_LICZB; j++)
    t[j] = PUSTE;
  t [0] = 0.0;
  t [ILE_LICZB + 1] = 1.0;
}

int kolejna_liczba (double x)
{
  int max_pos;
  double max_pr, pr;
  int i, j, k, l, ile_pustych;
  double p, q, x_skalowany;

  i = 0;
  while (t [i+1] == PUSTE || x > t [i+1]) i++;
  //i = ostatni wolny

  if (t [i] != PUSTE)
    return 1; //pora¿ka

  j = ILE_LICZB + 1;
  while (t [j-1] == PUSTE || x < t [j-1]) j--;
  //j = pierwszy wolny

  p = t [j - 1];
  q = t [i + 1];
  x_skalowany = (x - p) / (q - p);
  x_skalowany = x_skalowany > 1 ? 1 : x_skalowany; //zabezpieczenie przed bledem obliczen

  ile_pustych = i - j + 1;
  max_pr = 0;
  max_pos = 0;
  for (k=1; k <= ile_pustych; k++)
  {
    pr = newton [ile_pustych - 1][k - 1] * pr_sukc [k - 1] * pr_sukc [ile_pustych - k];
    for (l = 0; l < k - 1; l++)
      pr *= x_skalowany;
    for (l = 0; l < ile_pustych - k; l++)
      pr *= 1 - x_skalowany;

    if (pr > max_pr)
    {
      max_pr = pr;
      max_pos = k;
    }
  }
  t [j + max_pos - 1] = x;
  return j + max_pos - 1;
}
