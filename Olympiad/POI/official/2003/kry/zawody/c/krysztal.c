/* Program sprawdzaj±cy dla zawodników.
// Pozwala na korzystanie z nieco mniejszej maksymalnej warto¶ci N
// Nale¿y skompilowaæ w³asny plik z tym modu³em (krysztal.h / krysztal.cpp)
// Pobiera dane ze standrdowego wej¶cia
// U¿ycie: ./kry < nazwa_pliku
// Format pliku:
// n
// [1;1] [2;1] ... [n;1]
// [1;2] [2;2] ... [n;2]
// ...
// [1;n] [2;n] ... [n;n]
// gdzie [x;y] oznacza stan kryszta³u o wspó³rzêdnych (x,y)
*/
#include <stdio.h>
#include <stdlib.h>

#include "krysztal.h"

#define MAX_PROG 1000 
/* Uwaga: W zadaniu ograniczenie wynosi MAX_N. */
#define MAX_N 10000 

static int kry[MAX_PROG+1][MAX_PROG+1]; /* indeksujemy od 1 do n */
static int n;

static int wczytajLiczbe() {
  int pom;
  if (scanf("%d", &pom) != 1) {
    fprintf(stderr, "Blad odczytu wejscia!\n");
    exit(1);
  }
  return pom;
}

static void wczytaj() {
  int pom, i, j;
  n = wczytajLiczbe();
  if (n < 3 || n > MAX_N) {
    fprintf(stderr, "Niepoprawna wartosc n.\n");
    exit(1);
  }
  if (n > MAX_PROG) {
    fprintf(stderr, "Poprawna wartosc n, ale za duza dla tego programu.\n");
    exit(1);
  }
  for (i = 1; i <= n; ++i)
    for (j = 1; j <= n; ++j) {
      pom = kry[j][i] = wczytajLiczbe();
      if (pom != -1 && pom != 1 && pom != -2 && pom != 2) {
        fprintf(stderr, "Wczytano niepoprawna wartosc (%d) stanu atomu (%d, %d).\n", pom, j, i);
        exit(1);
      }
    }
}

static int ile;

int zamroz(int x, int y) {
  if (x<1 || x>n || y<1 || y>n) {
    fprintf(stderr, "Wspolrzedne atomu poza zakresem");
    exit(1);
  }
  if (x>1 && x<n && y>1 && y<n) ile++;
  return kry[x][y];
}

void niestabilna(int x1, int y1, int x2, int y2) {
  if (x1<1 || x1>n || y1<1 || y1>n || x2<1 || x2>n || y2<1 || y2>n) {
    fprintf(stderr, "Wspolrzedne atomu poza zakresem");
    exit(1);
  }

  fprintf(stderr, "Program dokonal %d zamrozen (limit=%d).\n", ile, 3*n);

  if (abs(x2-x1) <= 1 && abs(y2-y1) <= 1 && kry[x1][y1] == -kry[x2][y2]) {
    fprintf(stdout, "Poprawna odpowiedz.\n");
    exit(0);
  } else {
    fprintf(stdout, "Niepoprawna odpowiedz.\n");
    exit(1);
  }
}

static int initialized = 0;

int rozmiar() {
  if (!initialized) {
    wczytaj(); /* z stdin */
    initialized = 1;
    ile = 0;
  } else {
    fprintf(stderr, "Funkcja rozmiar() mo¿e byæ wywolana najwyzej raz"); 
  }
  return n;
}

