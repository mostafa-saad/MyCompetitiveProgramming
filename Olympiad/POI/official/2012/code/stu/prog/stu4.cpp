/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * log(max{x_i}))                             *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000000;

int x[MAXN]; // grubosc warstwy piasku, dane z wejscia
int pom[MAXN]; // pomocniczna tablica z grubosciami warstw piasku, na ktorej beda wykonywane obliczenia

int n;
long long m; // liczba ruchow lopaty, na ktore Bajtazar ma sile

/* Funkcja rozwiazujaca podproblem wyrownania koryta rzeki bez dokopywania sie do wody,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p.
 * Zwraca potrzebna liczbe ruchow lopaty do osiagniecia tego celu */

long long wyrownaj(int p) {
  long long ruchy = 0;
  for (int i = 1; i < n; ++i)
    if (pom[i-1] + p < pom[i]) {
      ruchy += pom[i] - pom[i-1] - p;
      pom[i] = pom[i-1] + p;
    }
  for (int i = n-2; i >= 0; --i)
    if (pom[i+1] + p < pom[i]) {
      ruchy += pom[i] - pom[i+1] - p;
      pom[i] = pom[i+1] + p;
    }
  return ruchy;
}

/* oblicza tablice jednostronnych wyrownan terenu w danym punkcie
 * tab - tablica wynikowa
 * s - pozycja startowa
 * k - pozycja koncowa
 * d - strona ktora wyrownujemy
 * g - maksymalna dopuszczalna roznica wysokosci */

void policz_tablice_wyrownan(long long * out, int s, int k, int d, int g) {
  int size = 1, brzeg = s + d;
  out[s] = 0;
  while (brzeg != k && pom[brzeg] > size * g) {
    out[s] += pom[brzeg] - size * g;
    brzeg += d;
    ++size;
  }
  while (s + d != k) {
    s += d;
    --size;
    out[s] = out[s-d];
    if (brzeg != s)
      out[s] -= pom[s] - size * g;
    else {
      brzeg += d;
      ++size;
    }
    while (brzeg != k && pom[brzeg] > size * g) {
      out[s] += pom[brzeg] - size * g;
      brzeg += d;
      ++size;
    }
  }
}

/* Funkcja zwraca miejsce, w ktorym uda sie dokopac do poziomu 0,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p,
 * badz -1 jesli takiego miejsca nie ma. */

int gdzie_kopac(int p) {
  for (int i = 0; i < n; ++i) pom[i] = x[i];

  long long ruchy = wyrownaj(p);
  if (ruchy > m) return -1;

  long long lewo[MAXN], prawo[MAXN];
  policz_tablice_wyrownan(prawo, 0, n, 1, p);
  policz_tablice_wyrownan(lewo, n-1, -1, -1, p);

  for (int i = 0; i < n; ++i)
    if (ruchy + prawo[i] + lewo[i] + pom[i] <= m)
      return (i + 1);

  return -1;
}

int main() {
  scanf ("%d %lld", &n, &m);
  int max_h = 0;
  for (int i = 0; i < n; ++i) {
    scanf ("%d", x + i);
    max_h = max(max_h, x[i]);
  }

  int pozycja = 1;
  int a = 0, b = max_h;
  while (a < b) {
    int c = (a + b) >> 1;
    int pozycja2 = gdzie_kopac(c);
    if (pozycja2 != -1) {
      b = c;
      pozycja = pozycja2;
    } else
      a = c + 1;
  }
  printf ("%d %d\n", pozycja, a);
  return 0;
}
