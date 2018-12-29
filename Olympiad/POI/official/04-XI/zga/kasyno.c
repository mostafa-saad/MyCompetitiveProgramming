#ifdef __cpluslus
#include <cstdio>
#include <cstdlib>
#else
#include <stdio.h>
#include <stdlib.h>
#endif

#include "zga.h"

#define PREC 12
#define ILE_ZESTAWOW 1000000L
#define PUSTE -1.0

#define MIN_LICZB 2

#define WYPLATA 423.99
#define DOPLATA 13.53

double daj_losowa()
{
  int i;
  double x = 0.0;
  do
/*    for (i=0; i++ < PREC; )
      x = (x + (int) (10.0*rand()/(RAND_MAX+1.0))) / 10;*/
    for (i=0; i < 2; i++)
      x = (x + rand() % 1000000) / 1000000;
  while (x == 0.0);
  return x;
}

int main ()
{
  long int wygrane = 0;
  long int i;
  int j, k, powtorzyl, wygrana, pozycja;
  double t [ILE_LICZB], s [ILE_LICZB + 1];
  double pkt_d;
  int pkt;

  srandom (5);

  inicjalizuj();

  for (i=0; i < ILE_ZESTAWOW; i++)
  {
    nowa_rozgrywka();

    s [0] = 0;
    for (j=1; j <= ILE_LICZB; j++)
      s [j] = PUSTE;

    for (j=0; j < ILE_LICZB; j++)
    {
      do
      {
        t[j] = daj_losowa ();
        powtorzyl = 0;
        for (k=0; k < j; k++)
          if (t [j] == t [k])
            powtorzyl = 1;
      }
      while (powtorzyl);

      pozycja = kolejna_liczba (t [j]);
      if (pozycja >= 1 && pozycja <= ILE_LICZB)
        s [pozycja] = t [j];
    }

    //sprawdzanie, czy tablica s jest posortowana
    wygrana = 1;
    for (j=1; j <= ILE_LICZB; j++)
      if (s[j] == PUSTE || s [j] <= s [j-1])
        wygrana = 0;

    if (wygrana)
      wygrane++;

  }

  pkt_d = 1e-4 * (((double)wygrane) * WYPLATA - ((double)(ILE_ZESTAWOW - wygrane)) * DOPLATA);
  pkt = pkt_d - (double)((int) pkt_d) < 0.5 ? (int) pkt_d : (int) pkt_d + 1; //zaokraglenie

  if (pkt < 0) pkt = 0;
  if (pkt > 100) pkt = 100;

  printf ("OK\n");
  printf ("%ld\n", wygrane);
  printf ("%d\n", pkt);

  return 0;
}
