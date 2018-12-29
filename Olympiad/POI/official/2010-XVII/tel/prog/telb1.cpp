/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Teleporty (TEL)                               *
 *   Plik:                 telb1.cpp                                     *
 *   Autor:                Łukasz Bieniasz-Krzywiec                      *
 *   Opis:                 Rozwiazanie niepoprawne.                      *
 *                         Używa algorytmu aproks. dla Set Cover.        *
 *   Zlozonosc czasowa:    O(n^4)                                        *
 *   Zlozonosc pamieciowa: O(n^3)                                        *
 *   Kodowanie znaków:     UTF-8                                         *
 *                                                                       *
 *************************************************************************/

#include <cstdlib>
#include <cstdio>

#include <vector>
#include <set>
#include <algorithm>

using namespace std;
/*
 * DEKLARACJE STAŁYCH
 */

#define MAXN 40000
#define MAXM 1000000


/*
 * DEKLARACJE TYPÓW:
 */

typedef vector<int>   VI;
typedef vector<bool>  VB;
typedef set<int>      SI;
typedef vector<SI>    VSI;
typedef vector<VI>    VVI;
typedef vector<VB>    VVB;


/*
 * DEKLARACJE ZMIENNYCH GLOBALNYCH:
 */

int n, m, w;  /* liczba wierzchołków, liczba krawędzi, wynik */
VVB g;        /* graf w postaci macierzy sąsiedztwa */

VSI s;        /* tablica pomocnicza */


/*
 * DEKLARACJE PODPROGRAMÓW:
 */

/* Funkcja dodaje do grafu krawędź {a,b}. */
void inline dodajKrawedz(int a, int b) {
  g[a][b] = true;
  g[b][a] = true;
}

/* Funkcja wczytuje dane. */
void wczytajDane() {
  int a, b, i, j;

  scanf("%d%d", &n, &m);

  g = VVB(n);
  for (i = 0; i < n; ++i) {
    g[i] = VB(n);
    for (j = 0; j < n; ++j) {
      g[i][j] = false;
    }
  }

  for (i = 0; i < m; ++i) {
    scanf("%d%d", &a, &b);
    dodajKrawedz(a - 1, b - 1);
  }
}

/* Funkcja przekształca krawędź {a,b} w jej unikalny numer. */
inline int hash(int a, int b) {
  if (b <= a) {
    return a * n + b;
  } else {
    return b * n + a;
  }
}

bool cmp(int k1, int k2) {
  return s[k1].size() > s[k2].size();
}

/* 
 * Funkcja oblicza moc maksymalnego rozszerzenia grafu.
 * Algorytm niepoprawny.
 */
void obliczWynik() {
  int           i, j, k, l;
  VVI           t;
  SI::iterator  ii;
  VI::iterator  jj;
  VSI::iterator kk, p;

  s = VSI(n * n);
  t = VVI(n * n * n);

  /* Ścieżki długości 1. */
  l = 0;
  s[hash(0,1)].insert(l);
  t[l].push_back(hash(0,1));

  /* Ścieżki długości 2. */
  l = 1;
  for (i = 2; i < n; ++i) {
    l += 1;
    if (!g[0][i]) {
      s[hash(0,i)].insert(l);
      t[l].push_back(hash(0,i));
    }
    if (!g[i][1]) {
      s[hash(i,1)].insert(l);
      t[l].push_back(hash(i,1));
    }
  }

  /* Ścieżki długości 3. */
  for (i = 2; i < n; ++i) {
    for (j = 2; j < n; ++j) {
      if (i != j) {
        l += 1;
        if (!g[0][i]) {
          s[hash(0,i)].insert(l);
          t[l].push_back(hash(0,i));
        }
        if (!g[i][j]) {
          s[hash(i,j)].insert(l);
          t[l].push_back(hash(i,j));
        }
        if (!g[j][1]) {
          s[hash(j,1)].insert(l);
          t[l].push_back(hash(j,1));
        }
      }
    }
  }

  /* Ścieżki długości 4. */
  for (i = 2; i < n; ++i) {
    for (j = 2; j < n; ++j) {
      for (k = 2; k < n; ++k) {
        if (i != j && i != k && j != k) {
          l += 1;
          if (!g[0][i]) {
            s[hash(0,i)].insert(l);
            t[l].push_back(hash(0,i));
          }
          if (!g[i][j]) {
            s[hash(i,j)].insert(l);
            t[l].push_back(hash(i,j));
          }
          if (!g[j][k]) {
            s[hash(j,k)].insert(l);
            t[l].push_back(hash(j,k));
          }
          if (!g[k][1]) {
            s[hash(k,1)].insert(l);
            t[l].push_back(hash(k,1));
          }
        }
      }
    }
  }

  /* Zachłannie wybieramy krawędzie do usunięcia. */
  for (k = 0; l > 0; ++k) {
    for (p = kk = s.begin(); kk != s.end(); ++kk) {
      if ((*kk).size() > (*p).size()) {
        p = kk;
      }
    }
    l -= (*p).size();
    for (ii = (*p).begin(); ii != (*p).end(); ++ii) {
      for (jj = t[*ii].begin(); jj != t[*ii].end(); ++jj) {
        s[*jj].erase(*ii);
      }
    }
    (*p).clear();
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

