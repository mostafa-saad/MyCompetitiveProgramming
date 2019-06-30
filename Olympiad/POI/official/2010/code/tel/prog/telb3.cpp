/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Teleporty (TEL)                               *
 *   Plik:                 telb3.cpp                                     *
 *   Autor:                Łukasz Bieniasz-Krzywiec                      *
 *   Opis:                 Rozwiazanie niepoprawne.                      *
 *                         Tylko krawędzie zmniejszające odległość 1 i 2.*
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *   Kodowanie znaków:     UTF-8                                         *
 *                                                                       *
 *************************************************************************/

#include <cstdlib>
#include <cstdio>

#include <vector>

using namespace std;

/*
 * Rozwiązanie niepoprawne 4.
 * Złożoność czasowa:     O(n^2)
 * Złożoność pamięciowa:  O(n + m)
 */

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

/* 
 * Funkcja oblicza moc maksymalnego rozszerzenia grafu.
 */
void obliczWynik() {
  int i, j, k;
  VI  t1(n), t2(n);

  bfs(0, t1);
  bfs(1, t2);

  k = 0;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < i; ++j) {
      if (t1[i] + t2[j] <= 4 || t1[j] + t2[i] <= 4) {
        k += 1;
      }
    }
  }

  w = n * (n - 1) / 2 - m - k;
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

