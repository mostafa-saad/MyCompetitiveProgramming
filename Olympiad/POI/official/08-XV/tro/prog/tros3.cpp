/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Trojkaty (TRO)                                            *
 *   Plik:     tros3.cpp                                                 *
 *   Autor:    Marian Marek Kedzierski                                   *
 *   Opis:     Rozwiazanie nieoptymalne.                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define MAXN 3000

typedef long long ll;
typedef long double ld;

ll x[MAXN], y[MAXN], n;
ll wynik; // dwukrotnosc sumy pol
ll ll_abs(ll x) {
  if (x < 0) return -x;
  return x;
}

ll vector_product(int c, int a, int b) {
  ll x1 = x[a] - x[c];
  ll x2 = x[b] - x[c];
  ll y1 = y[a] - y[c];
  ll y2 = y[b] - y[c];

  return x1 * y2 - x2 * y1;
}

int main() {
  scanf("%lld", &n);
  for (int i=0; i<n; ++i)
    scanf("%lld %lld", x+i, y+i);

  for (int i=0; i<n; ++i)
    for (int j=i+1; j<n; ++j)
      for (int k=j+1; k<n; ++k) {
        wynik += ll_abs(vector_product(i, j, k));
      }

  printf("%.1Lf\n", (ld) wynik / 2.0);
  return 0;
}
