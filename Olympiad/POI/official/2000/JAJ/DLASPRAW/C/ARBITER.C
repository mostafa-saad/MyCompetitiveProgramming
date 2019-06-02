/* Program arbitra do zadania JAJKA */
/* Autor: Pawel Wolff */

#include "jajmod.h"
#include "jaj.h"
#include <stdio.h>

#define MAX_LOSOWYCH_ODP 100

static long int wysokosc1;
static int jajka1;
static long int min_wyt, max_wyt;
static long int liczba_pytan, wystarczy_pytan;
static long int n, k, n_po_k, t;
static int ile_rozbitych;

static long int min(long int a, long int b)
{
  return (a < b) ? a : b;
}

static void skroc(long int *pa, long int *pb)
{
  long int a = *pa, b = *pb, c;
  if (a > b) {
    c = a; a = b; b = c;
  }
  while (a > 0) {
    c = b%a;
    b = a;
    a = c;
  }
  *pa /= b;
  *pb /= b;
}

static void zwieksz_n(void)
/* zwi©ksza n o 1, aktualizuje zmienne t, n_po_k */
{
  t = 2*t+1-n_po_k;
  n++;
  if (n == k)
    n_po_k = 1;
  if (n > k) {
    long int a = n, b = n-k;
    skroc(&a, &b);
    n_po_k = (n_po_k/b)*a;
  }
}

static void zwieksz_k(void)
/* zwi©ksza k o 1, aktualizuje zmienne t, n_po_k */
{
  k++;
  if (n >= k-1) {
    long int a = n-k+1, b = k;
    skroc(&a, &b);
    n_po_k = (n_po_k/b)*a;
  }
  t = t+n_po_k;
}

static void zmniejsz_n(void)
/* zmniejsza n o 1, aktualizuje zmienne t, n_po_k; musi by† n > 0 */
{
  if (n >= k) {
    long int a = n-k, b = n;
    skroc(&a, &b);
    n_po_k = (n_po_k/b)*a;
  }
  n--;
  t = (t+n_po_k-1)/2;
}

static void zmniejsz_k(void)
/* zmniejsza k o 1, aktualizuje zmienne t, n_po_k; musi by† k > 0 */
{
  t = t-n_po_k;
  if (n >= k) {
    long int a = k, b = n-k+1;
    skroc(&a, &b);
    n_po_k = (n_po_k/b)*a;
  }
  if (n == k-1)
    n_po_k = 1;
  k--;
}

static void ile_pytan(void)
{
  k = jajka1;
  n = 0; n_po_k = 0; t = 0;
  while (t < wysokosc1)
    zwieksz_n();
}

static void daj_odpowiedz(int losowa_odp)
/* musi byc k > 0 */
{
  if (n == 0) {
    /* moduˆ zawodnika ju¾ zadaˆ wi©cej pytaä ni¾ potrzeba */
    if (pietro > max_wyt)
      odpowiedz = NIE;
    if (pietro <= min_wyt)
      odpowiedz = TAK;
    if (min_wyt < pietro && pietro <= max_wyt)
      /* mo¾na odpowiedzie† TAK lub NIE */
      odpowiedz = losowa_odp ? TAK : NIE;
  }
  else {
    zmniejsz_n();

    if (pietro > max_wyt) {
      odpowiedz = NIE;
      zmniejsz_k();
    }
    if (pietro <= min_wyt)
      odpowiedz = TAK;
    if (min_wyt < pietro && pietro <= max_wyt)
      /* mo¾na odpowiedzie† TAK lub NIE */

      if (t < max_wyt-pietro)
	/* zbyt nisko zrzucone jajko */
	odpowiedz = TAK;
      else {
	zmniejsz_k();
	if (t < pietro-min_wyt-1)
	  /* zbyt wysoko zrzucone jajko */
	  odpowiedz = NIE;
	else {
	  /* przy obu odpowiedziach moduˆ zawodnika zachowuje szanse na
	     wygranie */
	  if (n == 0)
	    /* to byˆo ostatnie 'dozwolone' pytanie */
	    if (losowa_odp) {
	      odpowiedz = TAK;
	      zwieksz_k();
	    }
	    else
	      odpowiedz = NIE;
	  else {
	    /* zostaˆo jeszcze najmniej 1 'dozwolone' pytanie */
	    zmniejsz_n();
	    if (t >= pietro-min_wyt-1) {
	      /* odpowied« NIE umo¾liwiˆaby moduˆowi zawodnika zadanie
		 mniejszej liczby pytaä ni¾ wystarczy_pytaä */
	      odpowiedz = TAK;
	      zwieksz_k();
	    }
	    else {
	      zwieksz_k();
	      if (t >= max_wyt-pietro) {
		/* odpowied« TAK umozliwiˆaby moduˆowi zawodnika zadanie
		   mniejszej liczby pytaä ni¾ wystarczy_pytan */
		odpowiedz = NIE;
		zmniejsz_k();
	      }
	      else
		/* obie odpowiedzi mog¥ wymusi† na module zawodnika zadanie
		   dokˆadnie wystarczy_pytan pytaä */
		if (losowa_odp)
		  odpowiedz = TAK;
		else {
		  odpowiedz = NIE;
		  zmniejsz_k();
		}
	    }
	    zwieksz_n();
	  }
	}
      }
  }

  /* aktualizacja zmiennych: rozbitych, min_wyt, max_wyt */
  if (odpowiedz == NIE) {
    ile_rozbitych++;
    if (pietro <= max_wyt)
      max_wyt = pietro-1;
  }
  else
    if (pietro > min_wyt)
      min_wyt = pietro;
}

int main(void)
{
  int i, liczba_prob;
  FILE *fin, *fout;

  fin = fopen("JAJ.IN", "rt");
  fout = fopen("JAJ.OUT", "wt");

  fscanf(fin, "%d\n", &liczba_prob);
  for(i = 0; i < liczba_prob; i++) {
    int j, blad;
    int losowych_odp, losowe_odp[MAX_LOSOWYCH_ODP];

    fscanf(fin, "%ld%d%ld%ld\n", &wysokosc1, &jajka1, &min_wyt, &max_wyt);
    wysokosc = wysokosc1;
    jajka = jajka1;
    fscanf(fin, "%d", &losowych_odp);
    for(j = 0; j < losowych_odp; j++)
      fscanf(fin, "%d", losowe_odp+j);
    fscanf(fin, "\n");

    wiem = NIE;

    ile_pytan();
    wystarczy_pytan = n;

    liczba_pytan = 0;
    ile_rozbitych = 0;
    nowy_eksperyment();
    blad = 0;
    do {
      if (ile_rozbitych < jajka1) {
	daj_pytanie();
	liczba_pytan++;
      }

      if (pietro < 0 || pietro > wysokosc1 || ile_rozbitych == jajka1)
	blad = 1;
      else {
	daj_odpowiedz(losowe_odp[(liczba_pytan-1)%losowych_odp]);
	analizuj_odpowiedz();
      }
    } while (wiem != TAK && !blad);

    if (wiem == TAK && !blad && min_wyt == x && x == max_wyt &&
	liczba_pytan <= wystarczy_pytan)
      fprintf(fout, "OK\n");
    else {
      fprintf(fout, "ZLE:");
      if (blad)
	if (ile_rozbitych == jajka1)
	  fprintf(fout, " za duzo rozbitych jajek!\n");
	else
	  fprintf(fout, " proba zrzucenia jajka z pietra spoza zakresu!\n");
      else {
	if (liczba_pytan > wystarczy_pytan)
	  fprintf(fout, " za duzo pytan o wytrzymalosc jajka!");
	if (min_wyt != max_wyt || x != min_wyt)
	  fprintf(fout, " zle wyznaczona wytrzymalosc!");
	fprintf(fout, "\n");
      }
    }
  }

  fclose(fin);
  fclose(fout);
  return 0;
}

#undef MAX_LOSOWYCH_ODP
