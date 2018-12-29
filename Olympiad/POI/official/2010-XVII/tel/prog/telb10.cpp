/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Teleporty (TEL)                               *
 *   Plik:                 telb10.cpp                                    *
 *   Autorzy:              Łukasz Bieniasz-Krzywiec, Mirosław Michalski  *
 *   Opis:                 Rozwiazanie niepoprawne           .           *
 *                         "Popsute" rozwiązanie wzorcowe.               *
 *   Zlozonosc czasowa:    O(n + m)                                      *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *   Kodowanie znaków:     UTF-8                                         *
 *                                                                       *
 *************************************************************************/

#include <cstdlib>
#include <cstdio>

#include <vector>

using namespace std;

/*
 * DEKLARACJE STAŁYCH
 */

#define MAXN 40000
#define MAXM 1000000

#define INF MAXN


/*
 * DEKLARACJE TYPÓW:
 */

typedef vector<int> VI;
typedef vector<VI > VVI;


/*
 * DEKLARACJE ZMIENNYCH GLOBALNYCH:
 */

int n, m, w;  /* liczba wierzchołków, liczba krawędzi, wynik */
VVI g;        /* graf w postaci list sąsiedztwa */


/*
 * DEKLARACJE PODPROGRAMÓW:
 */

/* Funkcja dodaje do grafu krawędź {a,b}. */
void inline dodajKrawedz(int a, int b) {
  g[a].push_back(b);
  g[b].push_back(a);
}

/* Funkcja wczytuje dane. */
void wczytajDane() {
  int a, b, i;

  scanf("%d%d", &n, &m);

  g = VVI(n);
  for (i = 0; i < m; ++i) {
    scanf("%d%d", &a, &b);
    dodajKrawedz(a - 1, b - 1);
  }
}

/* Przeszukiwanie wszerz. */
void bfs(int v, VI &d) {
  int i, j, u, w;
  VI  q;

  for (i = 0; i < n; ++i) {
    d[i] = INF;
  }

  d[v] = 0; q.push_back(v);
  for (i = 0; i < (int)q.size(); ++i) {
    u = q[i];
    for (j = 0; j < (int)g[u].size(); ++j) {
      w = g[u][j];
      if (d[w] == INF) {
        d[w] = d[u] + 1;
        if (d[w] < 2) {
          q.push_back(w);
        }
      }
    }
  }
}

inline int min(int a, int b) {
  return a < b ? a : b;
}

/* 
 * Funkcja oblicza moc maksymalnego rozszerzenia grafu.
 * Algorytm wzorcowy.
 */
void obliczWynik() {
  int a = 0, b = 0, c = 0, d = 0, i;
  VI  t1(n), t2(n);

  bfs(0, t1);
  bfs(1, t2);

  for (i = 0; i < n; ++i) {
    switch (t1[i]) {
      case 1: a += 1; break;
      case 2: b += 1; break;
    }
    switch (t2[i]) {
      case 1: c += 1; break;
      case 2: d += 1; break;
    }
  }
  w = n*(n-1)/2-m-(n-1-a)-a*(1+c+d)-b*(1+c)-(n-1-c-1-a-b)-min(b,d)*(n-1-a-b-1-c-d);
}

/* Funkcja wypisuje wynik. */
void wypiszWynik() {
  printf("%d\n", w);
}


/*
 * PROGRAM GŁÓWNY:
 */

int main() {
  wczytajDane();
  obliczWynik();
  wypiszWynik();

  return 0;
}

