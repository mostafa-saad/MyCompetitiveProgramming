/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Arkanoid                                           *
 *   Autor programu:       Tomasz Idziaszek                                   *
 *   Zlozonosc czasowa:    O(mnk)                                             *
 *   Opis:                 rozwiazanie wolne                                  *
 *****************************************************************************/

#include <cstdio>
#include <tuple>
using namespace std;

const int MAX_N = 1000, MAX_K = 1000;

int m, n, k;
int xk[MAX_K+1], yk[MAX_K+1];
bool plansza[2*MAX_N+1][2*MAX_N+1];
int x, y, dx, dy;
int czas;

tuple<int, int> srodek_pola(int x, int y, int dx, int dy) {
  int sx, sy;
  if (x % 2 == 0) {
    sx = x + dx;
    sy = y;
  } else {
    sx = x;
    sy = y + dy;
  }
  return make_tuple(sx, sy);
}

bool sciana(int x, int y, int dx, int dy) {
  int sx, sy;
  tie(sx, sy) = srodek_pola(x, y, dx, dy);
  return (sx < 0 || sx > 2*m || sy < 0 || sy > 2*n);
}

void odbij() {
  if (x % 2 == 0) {
    dx = -dx;
  } else {
    dy = -dy;
  }
}

void ruszaj() {
  x += dx;
  y += dy;
  czas += 1;
  if (sciana(x, y, dx, dy)) {
    odbij();
  } else {
    int sx, sy;
    tie(sx, sy) = srodek_pola(x, y, dx, dy);
    if (plansza[sx][sy]) {
      plansza[sx][sy] = false;
      k--;
      odbij();
    }
  }
}

void wczytaj_dane() {
  scanf("%d%d%d", &m, &n, &k);
  for (int i = 1; i <= k; i++) {
    scanf("%d%d", &xk[i], &yk[i]);
  }
}

void inicjuj_plansze() {
  for (int sx = 1; sx <= 2*m-1; sx += 2) {
    for (int sy = 1; sy <= 2*n-1; sy += 2) {
      plansza[sx][sy] = false;
    }
  }
  for (int i = 1; i <= k; i++) {
    plansza[2*xk[i]-1][2*yk[i]-1] = true;
  }
}

void petla() {
  czas = 0;
  x = m; y = 0;
  dx = -1; dy = 1;
  while (k) {
    ruszaj();
  }
}

int main() {
  wczytaj_dane();
  inicjuj_plansze();
  petla();
  printf("%d\n", czas);
}
