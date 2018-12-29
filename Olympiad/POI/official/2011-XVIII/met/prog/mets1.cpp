/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O(k * m)                                         *
 *   Opis:              Rozwiazanie powolne, silowe                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
using namespace std;

int __abc;
#define scanf __abc=scanf

const int N = 300007;

int n, m, lo;
int pot[N], wl[N], wyn[N]; 
/*
   pot[i] - zapotrzebowanie i-tego pañstwa na meteoryty
   wl[i]  - wla¶ciciel i-tej stacji
   wyn[i] - odpowied¼ dla i-tego pañstwa
*/
// Funkcja symuluje upadek po w meteorytów na pola l..r w ruchu nr.
void zrzuc(int nr, int l, int r, int w){
  for (int i = l; i <= r; i++)
    if (pot[wl[i]] > 0) {
      pot[wl[i]] -= w;
      if (pot[wl[i]] <= 0)
        wyn[wl[i]] = nr;
    }
}

int main()
{
  // Wczytanie danych.
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    int a;
    scanf("%d",&a);
    wl[i] = a-1;
  }
  for (int i = 0; i < n; i++) {
    scanf("%d",&pot[i]);
  }

  // Wczytywanie i przetwarzanie opadów. 
  scanf("%d", &lo);
  for (int nr = 1; nr <= lo; nr++) {
    int l, r, w;
    scanf("%d %d %d",&l, &r, &w);
    l--;
    r--;
    if (l <= r)
      zrzuc(nr, l, r, w);
    else {
      zrzuc(nr, 0, r, w);
      zrzuc(nr, l, m-1, w);
    }
  }

  // Wypisanie wyniku.
  for (int i = 0; i < n; i++){
    if(wyn[i] > 0)
      printf("%d\n", wyn[i]);
    else
      printf("NIE\n");
  }
  return 0;
}
