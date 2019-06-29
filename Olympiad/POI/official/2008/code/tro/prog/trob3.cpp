/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Trojkaty (TRO)                                            *
 *   Plik:     trob3.cpp                                                 *
 *   Autor:    Marian Marek Kedzierski                                   *
 *   Opis:     Rozwiazanie niepoprawne, rozszerzamy tylko zbior po       *
 *             jednej stronie miotly.                                    *
 *                                                                       *
 *************************************************************************/

 #include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define MAXN 3000
#define LITTLE 0.00000000001LF

typedef long long ll;
typedef long double ld;

ll x[MAXN], y[MAXN], n;
int srt[MAXN]; // tablica sluzaca do sortowan
ll wynik; // dwukrotnosc sumy pol

ll ll_abs(ll x) {
  if (x < 0) return -x;
  return x;
}

ld alfa(ll x, ll y) {
  ld d = ll_abs(x) + ll_abs(y);
  // podzial na kolejne cwiartki
  if (x >= 0 && y >=0) return y / d; // I
  if (x <= 0) return 2. - y / d; // II i III
  return 4. - y / d; // IV
}

// komparator punktow do sortowania biegunowego
// zaklada, ze wszystkie rozwazane punkty zostaly juz wysrodkowane (x := x - x_center)
class Cmp {
  public: bool operator()(int a, int b) {
    return alfa(x[a], y[a]) < alfa(x[b], y[b]);
  }
} cmp;


int main() {
  scanf("%lld", &n);
  for (int i=0; i<n; ++i)
    scanf("%lld %lld", x+i, y+i);

  for (int center=0; center<n; ++center) {
    // wysrodkowanie punktow
    for (int j=center+1; j<n; ++j) {
      x[j] -= x[center];
      y[j] -= y[center];
    }

    // sortujemy wszystkie punkty o indeksach wiekszych od center
    // te o indeksach mniejszych od center uwazamy za juz usuniete
    for (int j=center+1; j<n; ++j) srt[j] = j;
    sort(srt + center + 1, srt + n, cmp);

    // przygotowanie do zamiatania - obliczenie wstepnej sumy y-ow
    ll y_sum = 0;
    for (int j=center+2; j<n; ++j) y_sum += y[srt[j]];

    // zamiatanie
    for (int i=center+1; i<n; ++i)  {
      // trojkaty rozpiete na v_center, v_i oraz ...
      wynik += x[srt[i]] * y_sum;

      // aktualizacja y_sum
      y_sum -= y[srt[i+1]];
      y_sum -= y[srt[i]];
    }

    // powrot z wysrodkowania punktow
    for (int j=center+1; j<n; ++j) {
      x[j] += x[center];
      y[j] += y[center];
    }
  }

  printf("%.1Lf\n", (ld) wynik / 2.0);
  return 0;
}
