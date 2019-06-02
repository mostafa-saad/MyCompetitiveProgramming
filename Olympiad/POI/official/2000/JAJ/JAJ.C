/*************************************************************************/
/*                                                                       */
/*                   VII Olimpiada Informatyczna                         */
/*                                                                       */
/*   Rozwi•zanie zadania: JAJKA                                          */
/*   Plik:                JAJ.C                                          */
/*   Autor:               PAWEù WOLFF                                    */
/*************************************************************************/

#include "jajmod.h"
#include "jaj.h"

static long int n, k, n_po_k, t;
static long int min_wyt, max_wyt, aktualne_pietro;

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
/* zmniejsza n o 1, aktualizuje zmienne t, n_po_k; musi byÜ n > 0 */
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
/* zmniejsza k o 1, aktualizuje zmienne t, n_po_k; musi byÜ k > 0 */
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


void nowy_eksperyment(void)
{
  wiem = NIE;

  k = jajka;
  min_wyt = 0;
  max_wyt = wysokosc;

  n = 0; n_po_k = 0; t = 0;
  while (t < wysokosc)
    zwieksz_n();
}

void daj_pytanie(void)
{
  zmniejsz_n();
  zmniejsz_k();
  pietro = aktualne_pietro = min(min_wyt+t+1, max_wyt);
}

void analizuj_odpowiedz(void)
{
  if (odpowiedz == TAK) {
    min_wyt = aktualne_pietro;
    zwieksz_k();
  }
  else
    max_wyt = aktualne_pietro-1;

  if (min_wyt == max_wyt) {
    wiem = TAK;
    x = min_wyt;
  }
}
