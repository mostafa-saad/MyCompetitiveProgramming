/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Mafia (MAF)                                               *
 *   Plik:     maf5.cpp                                                  *
 *   Autor:    Marian Marek Kedzierski                                   *
 *   Opis:     Rozwiazanie alternatywne o zlozonosci czasowej O(n).      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cassert>
#include <queue>
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


// kolejka wierzcholkow czekajacych na transformacje w algorytmie
// znajdowania minimum
queue<int> q;


/* dokonuje transformacji na wierzcholku v - jednoczesnie
 * wrzucajac do kolejki wierzcholki, ktore w jej wyniku
 * staly sie liscmi
 * zalozenie pre i post: indeg[] odzwierciedla aktualny stan stopni wejściowych
 * wierzcholkow w przetworzonym grafie
 */
void transform(int v) {
  // zapamietajmy dziadka v, bo tylko ten dziadek może zostać nowym lisciem
  int dziadek = tmp[tmp[v]];

  // nigdy nie transformujemy tych, ktorzy juz celuja do manekina
  assert(tmp[v] != -1);

  // zmiana postaci grafu
  --indeg[dziadek];
  tmp[tmp[v]] = tmp[v];
  tmp[v] = -1;

  // dodaj w razie potrzeby dziadka v do kolejki
  if (indeg[dziadek] == 0 && tmp[dziadek] != -1) q.push(dziadek);
}



int find_minimum() {
  // przepisanie grafu s[] na graf tmp[] na ktorym bedziemy
  // dokonywac transformacji
  for (int i=0; i<n; ++i) tmp[i] = s[i];

  // obliczenie stopni wejsciowych
  for (int i=0; i<n; ++i) indeg[i] = 0;
  for (int i=0; i<n; ++i) ++indeg[tmp[i]];

  // przygotowanie kolejki wiercholkow do transformacji
  // - wrzucenie do niej lisci
  for (int i=0; i<n; ++i) if (indeg[i] == 0) q.push(i);


  // transformacje do skutku
  while (true) {
    // znajdz kandydata do transformacji (najpierw szukaj liscia)
    int candidate = -1;
    if (!q.empty()) {
      candidate = q.front();
      q.pop();
    }

    // jesli sie nie udalo to zakoncz te petle
    if (candidate == -1) break;

    // w przeciwnym wypadku dokonaj transformacji
    transform(candidate);
  }
  assert(q.empty());

  // teraz na kazdym cyklu dlugosci >= 2
  // wybierz dowolny wierzcholek i wrzuc go do kolejki
  for (int i=0; i<n; ++i) visited[i] = false;
  for (int i=0; i<n; ++i)
    if (!visited[i] && i != tmp[i] && tmp[i] != -1) {
      q.push(i);
      for (int j=i; !visited[j]; j=tmp[j])
        visited[j] = true;
    }

  // ... i powtorz wszystko dla nowej kolejki
  while (!q.empty()) {
    int candidate = q.front();
    transform(candidate);
    q.pop();
  }
  // Hurra! Koniec wszystkich transformacji!

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
