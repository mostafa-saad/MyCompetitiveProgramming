/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kinoman                                            *
 *   Autor programu:       Tomasz Idziaszek                                   *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Autorskie rozwiazanie wzorcowe                     *
 *                                                                            *
 *****************************************************************************/


#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)

const int N = 1000005;
int m,f[N],ww[N],a[N],b[N];
long long best;

/* Drzewo przedziałowe wklejone z kodu Jakuba Radoszewskiego
 * źródło: http://was.zaa.mimuw.edu.pl/sites/default/files/file/s2008-w02/koleje.cpp
 */
#define f1(x, y) (x + y)
#define f2(x, y) max(x, y)
#define wiele(x, n) (x)
#define PUSTY 0

#define MAX_N 1000005
#define LOG_MAX_N 25 /* stala nieco wieksza od log(MAX_N) */

long long w[4 * MAX_N], W[4 * MAX_N]; /* wartosci w i W */
int n; /* Zakres wartosci punktow to: [0,n-1]. */
int ile; /* najmniejsza potega dwojki >=n */


/* [a,b] - przedzial, c - ustawiana wartosc */
inline void insert(int a, int b, long long c) {
  if (a > b) return;
  /* Operacje w lisciach. W przypadku niektorych kombinacji operacji
   * "if (a != b)" jest istotne, a dla innych nie szkodzi. */
  int va = ile + a, vb = ile + b;
  w[va] = f1(w[va], c);
  if (a != b) w[vb] = f1(w[vb], c);

  /* Spacer wskazniczkami va i vb do korzenia, polaczony z aktualizacjami
   * odpowiednich wartosci w i W. */
  int d = 0; /* odleglosc od najblizszego liscia (=wysokosc-glebokosc) */
  while (va != 1) {
    if (va / 2 != vb / 2) {
      if (va %2 == 0) w[va + 1] = f1(w[va + 1], c);
      if (vb %2 == 1) w[vb - 1] = f1(w[vb - 1], c);
    }
    va /= 2; vb /= 2;
    W[va] = f2(f1(W[2 * va],wiele(w[2 * va], (1 << d))),
               f1(W[2 * va + 1],wiele(w[2 * va + 1], (1 << d))));
    W[vb] = f2(f1(W[2 * vb],wiele(w[2 * vb], (1 << d))),
               f1(W[2 * vb + 1],wiele(w[2 * vb + 1], (1 << d))));
    d++;
  }
}


/* Makro pomocnicze do pierwszego spaceru do korzenia w zapytaniu. Jest ono
 * interesujace samo w sobie, gdyz l parametryzuje NAZWY zmiennych (dlatego
 * to musi byc makro, a nie np. funkcja). */
#define droga(l) do { \
  int w##l = 0, v##l = ile + l; \
  while (v##l != 0) { \
    pom##l[w##l++] = w[v##l]; \
    v##l /= 2; \
  } \
  for (int j = w##l - 2; j >= 0; j--) \
    pom##l[j] = f1(pom##l[j], pom##l[j + 1]); \
} while (0)

/* [a,b] - przedzial */
inline long long query(int a, int b) {
  if (a > b) return 0;

  /* W przypadku zapytania chec uzyskania nierekurencyjnej implementacji sporo
   * utrudnia. Wykonujemy przez to dwa przebiegi od lisci do korzenia.
   * W pierwszym wyznaczamy sumy czesciowe sumarycznych wkladow (tablice poma
   * i pomb) wartosci w na sciezkach od wezlow do korzenia do wyniku (sa to
   * albo maksima, albo sumy). */
  long long poma[LOG_MAX_N], pomb[LOG_MAX_N];
  droga(a); droga(b);
  int va = ile + a, vb = ile + b;

  /* W drugim przebiegu wyznaczamy wynik na podstawie wynikow dla przedzialow
   * bazowych z rozkladu [a,b]. */
  long long wynik = ((va != vb) ? f2(poma[0], pomb[0]) : poma[0]);
  int d = 0; /* odleglosc od najblizszego liscia (=wysokosc-glebokosc) */
  while (va / 2 != vb / 2) {
    if (va % 2 == 0) wynik = f2(wynik, f1(wiele(f1(poma[d + 1], w[va + 1]), (1 << d)), W[va + 1]));
    if (vb % 2 == 1) wynik = f2(wynik, f1(wiele(f1(pomb[d + 1], w[vb - 1]), (1 << d)), W[vb - 1]));
    va /= 2; vb /= 2;
    d++;
  }
  return wynik;
}

void init() {
  ile = 2;
  while (ile < n) ile *= 2;
  for (int i = 1; i < 2*ile; i++) w[i] = W[i] = PUSTY;
}

/* Koniec wklejonego drzewa */


int main() {
  scanf("%d%d",&n,&m);
  REP(i,n) { scanf("%d",&f[i]); --f[i]; }
  REP(i,m) scanf("%d",&ww[i]);
  REP(i,m) a[i] = b[i] = -1;
  
  init();
  
  REP(i,n) {
    const int F = f[i], W = ww[F];
    insert(a[F]+1, i, W);
    best = max(best, query(a[F]+1, i));
    insert(b[F]+1, a[F], -W);
    best = max(best, query(b[F]+1, a[F]));
    b[F] = a[F];
    a[F] = i;
  }

  printf("%lld\n", best);
}
