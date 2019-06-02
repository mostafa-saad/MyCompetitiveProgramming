/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Mafia (MAF)                                               *
 *   Plik:     maf3.cpp                                                  *
 *   Autor:    Marian Marek Kedzierski                                   *
 *   Opis:     Rozwiazanie alternatywne o zlozonosci czasowej O(n^2).    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cassert>
using namespace std;
#define MAX 1000000

int n, s[MAX], tmp[MAX], indeg[MAX];
bool visited[MAX];


int find_maximum() {
  int nlisci = 0, ncykli_niesamobojczych = 0;

  // zliczanie stopni wejściowych
  for (int i=0; i<n; ++i) indeg[i] = 0;
  for (int i=0; i<n; ++i) ++indeg[s[i]];

  // resetowanie tablicy visited[]
  for (int i=0; i<n; ++i) visited[i] = false;

  // zliczanie lisci lacznie z wykreslaniem wierzcholkow
  // z nich osiagalnych
  for (int i=0; i<n; ++i)
    if (indeg[i] == 0) {
      ++nlisci;
      for (int j=i; !visited[j]; j=s[j])
        visited[j] = true;
    }

  // teraz pozostaly juz tylko cykle proste

  // zliczanie cyklow dlugosci >= 2
  for (int i=0; i<n; ++i)
    if (!visited[i] && s[i] != i) {
      ++ncykli_niesamobojczych;
      for (int j=i; !visited[j]; j=s[j])
        visited[j] = true;
    }

  return n - nlisci - ncykli_niesamobojczych;
}


// znajduje w grafie tymczasowym liscia (tzn. wierzcholka o stopniu wejsciowym zero,
// ktory nie celuje do mafioza o nr -1) lub zwraca -1, jesli takiego nie ma
int find_leaf() {
  // obliczanie stopni wejsciowych
  for (int i=0; i<n; ++i) indeg[i] = 0;
  for (int i=0; i<n; ++i)
    if (tmp[i] != -1) ++indeg[tmp[i]];

  // znalezienie liscia
  for (int i=0; i<n; ++i)
    if (tmp[i] != -1 && indeg[i] == 0) return i;

  // jesli sie nie uda...
  return -1;
}


// dokonuje transformacji na wierzcholku v
void transform(int v) {
  // nigdy nie transformujemy tych, ktorzy juz celuja do manekina
  assert(tmp[v] != -1);
  tmp[tmp[v]] = tmp[v];
  tmp[v] = -1;
}


int find_minimum() {
  // przepisanie grafu s[] na graf tmp[] na ktorym bedziemy
  // dokonywac transformacji
  for (int i=0; i<n; ++i) tmp[i] = s[i];

  // transformacje do skutku
  while (true) {
    // znajdz kandydata do transformacji (najpierw szukaj liscia)
    int candidate = find_leaf();

    // jesli sie nie udalo to szukaj dowolnego niesamobojcy ...
    for (int j=0; j < n && candidate == -1; ++j)
      if (j != tmp[j] && tmp[j] != -1) candidate = j;

    // jesli nadal sie nie udalo to zakoncz
    if (candidate == -1) break;

    // w przeciwnym wypadku dokonaj transformacji
    transform(candidate);
  }

  // jako wynik zwroc liczbe samobojcow po wszystkich transformacjach
  int nsamobojcow = 0;
  for (int i=0; i<n; ++i) if (tmp[i] == i) ++nsamobojcow;

  return nsamobojcow;
}


int main() {
  scanf("%d", &n);
  for (int i=0; i<n; ++i) {
    scanf("%d", s+i);
    --s[i];
  }

  int minimum, maximum;

  maximum = find_maximum();
  minimum = find_minimum();

  printf("%d %d\n", minimum, maximum);

  return 0;
}
