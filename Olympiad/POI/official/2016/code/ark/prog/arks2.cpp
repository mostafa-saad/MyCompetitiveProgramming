/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Arkanoid                                           *
 *   Autor programu:       Tomasz Idziaszek                                   *
 *   Zlozonosc czasowa:    O(mn + (m+n)k)                                     *
 *   Opis:                 rozwiazanie wolne                                  *
 *****************************************************************************/

#include <cstdio>
#include <map>
#include <tuple>
using namespace std;

const int MAX_N = 1000, MAX_K = 1000;
enum pole_t { pole_puste, pole_klocek, pole_sciana };

int m, n, k;
int xk[MAX_K+1], yk[MAX_K+1];
bool plansza[2*MAX_N+1][2*MAX_N+1];
int x, y, dx, dy;
int czas;
map<tuple<int, int, int, int>, tuple<int, int, int> > graf_map;

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

tuple<int, int, int>& graf(int x, int y, int dx, int dy) {
  tuple<int, int, int, int> klucz = make_tuple(x, y, dx, dy);
  return graf_map[klucz];
}

void dodaj_krawedz(int x, int y, int dx, int dy) {
  int nx = x;
  int ny = y;
  while (!sciana(nx, ny, dx, dy)) {
    int sx, sy;
    tie(sx, sy) = srodek_pola(nx, ny, dx, dy);
    if (plansza[sx][sy]) {
      break;
    }
    nx += dx;
    ny += dy;
  }
  int len = abs(nx - x);
  graf(x, y, dx, dy) = make_tuple(nx, ny, len);
  graf(nx, ny, -dx, -dy) = make_tuple(x, y, len);
}

void inicjuj_graf() {
  for (int sx = 1; sx <= 2*m-1; sx += 2) {
    dodaj_krawedz(sx, 0, 1, 1);
    dodaj_krawedz(sx, 0, -1, 1);
  }
  for (int sy = 1; sy <= 2*n-1; sy += 2) {
    dodaj_krawedz(0, sy, 1, 1);
    dodaj_krawedz(2*m, sy, -1, 1);
  }
  for (int i = 1; i <= k; i++) {
    int sx = 2*xk[i]-1;
    int sy = 2*yk[i]-1;
    dodaj_krawedz(sx, sy+1, 1, 1);
    dodaj_krawedz(sx, sy+1, -1, 1);
    dodaj_krawedz(sx-1, sy, -1, 1);
    dodaj_krawedz(sx+1, sy, 1, 1);
  }
}

void scal_krawedz(int x, int y, int dx, int dy) {
  int xa, ya, la, xb, yb, lb;
  tie(xa, ya, la) = graf(x, y, dx, dy);
  tie(xb, yb, lb) = graf(x - dx, y - dy, -dx, -dy);
  int l = la + 1 + lb;
  graf(xa, ya, -dx, -dy) = make_tuple(xb, yb, l);
  graf(xb, yb, dx, dy) = make_tuple(xa, ya, l);
}

void usun_klocek(int x, int y, int dx, int dy) {
  int sx, sy;
  tie(sx, sy) = srodek_pola(x, y, dx, dy);
  plansza[sx][sy] = false;
  scal_krawedz(sx+1, sy, 1, 1);
  scal_krawedz(sx, sy+1, -1, 1);
  scal_krawedz(sx-1, sy, -1, -1);
  scal_krawedz(sx, sy-1, 1, -1);
}

void ruszaj() {
  int l;
  tie(x, y, l) = graf(x, y, dx, dy);
  czas += l;
  if (sciana(x, y, dx, dy)) {
    odbij();
  } else {
    usun_klocek(x, y, dx, dy);
    k--;
    odbij();
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
  inicjuj_graf();
  petla();
  printf("%d\n", czas);
}
