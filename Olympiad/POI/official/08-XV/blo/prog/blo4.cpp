/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Blokada (BLO)                                             *
 *   Plik:     blo4.cpp                                                  *
 *   Autor:    Marian Marek Kêdzierski                                   *
 *   Opis:     Rozwiazanie alternatywne, zlozonosc O(n + m).             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cassert>
#include <list>
using namespace std;
#define MAXN 100000
#define MAXM 500000

// *** typy

typedef list<int>::iterator LItor;
typedef long long ll;

// *** zmienne

int n, m;
list<int> sasiedzi[MAXN];
list<int> odcinane[MAXN]; // lista synow v, ktorych poddrzewa sa spojnymi skladowymi po usunieciu v
ll wynik[MAXN];  // szukane wyniki dla poszczegolnych wierzcholkow
ll low[MAXN];    // funkcja low, liczona w algorytmie dwuspojnych skladowych
ll size[MAXN];   // wielkosc poddrzewa w przejsciu DFS-em
ll visit[MAXN];  // czas odwiedzenia wierzcholka (0 jesli nieodwiedzony)
ll the_time = 1;     // czas w algorytmie DFS


// *** funkcje pomocnicze

/* funkcja wyznaczajaca punkty artykulacji standardowym
 * algorytmem dwuspojnych skladowych oraz dla kazdego wierzcholka v
 * znajduje wielkosc jego poddrzewa (size[v]), ktora wykorzystuje
 * do znalezienia liczby par miast, ktore po usunieciu miasta v
 * nie beda polaczone krawedzia
 */
void dwuspojne(ll v = 0, ll father = -1) {
  assert(!visit[v]);
  low[v] = visit[v] = the_time++;
  size[v] = 1;

  for (LItor itor = sasiedzi[v].begin(); itor != sasiedzi[v].end(); ++itor)
    if (!visit[*itor]) { // krawedz w dol - drzewowa
      dwuspojne(*itor, v);
      // low[*itor] oraz size[*itor] juz obliczone
      low[v] = min(low[v], low[*itor]);
      size[v] += size[*itor];

      // jesli v jest punktem artykulacji, ktory oddziela poddrzewo
      // wierzcholka *itor od reszty grafu to zaktualizuj wynik[v]
      // przy czym przyjmuje, ze korzen jest zawsze specjalnym pktem artykulacji
      if (low[*itor] >= visit[v])
        odcinane[v].push_back(*itor);
    }
    else if (*itor != father) {  // krawedz powracajaca z lub do wierzcholka v
      low[v] = min(low[v], visit[*itor]);
    }

  // ostateczne obliczenie wynik[v] na podstawie odcinane[v]

  // obliczmy rozmiar drzewa po usunieciu v oraz poddrzew wierzcholkow z odcinane[v]
  ll rest_size = n - 1;
  for (LItor it = odcinane[v].begin(); it != odcinane[v].end(); ++it) rest_size -= size[*it];

  // znajdzmy liczbe spotkan uniemozliwionych przez usuniecie v
  for (LItor it = odcinane[v].begin(); it != odcinane[v].end(); ++it) {
    // podroze z poddrzewa *itor do wszystkich niedostepnych wierzcholkow
    wynik[v] += size[*it] * (n - 1 - size[*it]);
    // podroze do poddrzewa *itor z niedostepnych wierzcholkow ze zbioru "rest"
    // tzn. spoza rodziny poddrzew wierzcholkow z odcinane[v]
    wynik[v] += size[*it] * rest_size;
  }
}


// *** funkcja main

int main() {
  // input
  scanf("%d %d", &n, &m);
  int a, b;
  for (int i=0; i<m; ++i) {
    scanf("%d %d", &a, &b);
    a--; b--;
    sasiedzi[a].push_back(b);
    sasiedzi[b].push_back(a);
  }

  // uwzglednienie spotkan z mieszkancami blokowanych miast
  for (int i=0; i<n; ++i)
    wynik[i] = 2 * (n - 1);

  // uwzglednienie spotkan pomiedzy mieszkancami nieblokowanych miast
  // - tzn. miedzy mieszkancami miast z roznych spojnych skladowych
  // po usunieciu danego zablokowanego miasta
  dwuspojne();

  // output
  for (int i=0; i<n; ++i)
    printf("%lld\n", wynik[i]);

  return 0;
}
