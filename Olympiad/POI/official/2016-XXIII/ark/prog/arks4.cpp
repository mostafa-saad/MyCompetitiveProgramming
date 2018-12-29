/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Arkanoid                                           *
 *   Autor programu:       Tomasz Idziaszek                                   *
 *   Zlozonosc czasowa:    O(mn + klogk)                                      *
 *   Opis:                 rozwiazanie wolne                                  *
 *****************************************************************************/

#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
#include <tuple>
using namespace std;

const int MAX_N = 1000, MAX_K = 1000;

int m, n, k;
int xk[MAX_K+1], yk[MAX_K+1];
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

map<tuple<int, int, int, int>, int> numery;
tuple<int, int, int, int> pozycje[4*MAX_N*MAX_N];
set<int> zbior_numerow;

int numer(int x, int y, int dx, int dy) {
  tuple<int, int, int, int> klucz = make_tuple(x, y, dx, dy);
  return numery[klucz];
}

tuple<int, int, int, int> pozycja(int t) {
  return pozycje[t];
}

set<int> numery_klocka(int sx, int sy) {
  set<int> zbior;
  tuple<int, int, int, int> klucze[] = {
    make_tuple(sx-1, sy, 1, 1),
    make_tuple(sx-1, sy, 1, -1),
    make_tuple(sx+1, sy, -1, -1),
    make_tuple(sx+1, sy, -1, 1),
    make_tuple(sx, sy-1, -1, 1),
    make_tuple(sx, sy-1, 1, 1),
    make_tuple(sx, sy+1, 1, -1),
    make_tuple(sx, sy+1, -1, -1)
  };
  int skret = ((sx/2) ^ (sy/2) ^ (m/2)) & 1;
  for (int i = skret; i < 8; i += 2) {
    int x, y, dx, dy;
    tie(x, y, dx, dy) = klucze[i];
    int t = numer(x, y, dx, dy);
    zbior.insert(t);
  }
  return zbior;
}

void usun_klocek(int x, int y, int dx, int dy) {
  int sx, sy;
  tie(sx, sy) = srodek_pola(x, y, dx, dy);

  set<int> zbior = numery_klocka(sx, sy);
  for (set<int>::iterator it = zbior.begin(); it != zbior.end(); ++it)
    zbior_numerow.erase(*it);
}

void ruszaj() {
  int t = numer(x, y, dx, dy);
  set<int>::iterator it = zbior_numerow.lower_bound(t);
  int nast_t;
  if (it != zbior_numerow.end()) {
    nast_t = *it;
    czas += nast_t - t;
  } else {
    nast_t = *zbior_numerow.begin();
    czas += 4*n*m - (t - nast_t);
  }
  tie(x, y, dx, dy) = pozycja(nast_t);
  usun_klocek(x, y, dx, dy);
  k--;
  odbij();
}

void wczytaj_dane() {
  scanf("%d%d%d", &m, &n, &k);
  for (int i = 1; i <= k; i++) {
    scanf("%d%d", &xk[i], &yk[i]);
  }
}

void inicjuj_numery() {
  x = m; y = 0;
  dx = -1; dy = 1;
  for (int t = 0; t < 4*n*m; ++t) {
    tuple<int, int, int, int> klucz = make_tuple(x, y, dx, dy);
    numery[klucz] = t;
    pozycje[t] = klucz;
    x += dx;
    y += dy;
    if (sciana(x, y, dx, dy)) {
      odbij();
    }
  }
}

void inicjuj_zbior() {
  for (int i = 1; i <= k; i++) {
    set<int> zbior = numery_klocka(2*xk[i] - 1, 2*yk[i] - 1);
    zbior_numerow.insert(zbior.begin(), zbior.end());
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
  inicjuj_numery();
  inicjuj_zbior();
  petla();
  printf("%d\n", czas);
}
