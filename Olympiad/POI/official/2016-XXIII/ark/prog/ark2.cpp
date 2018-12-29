/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Arkanoid                                           *
 *   Autor programu:       Tomasz Idziaszek                                   *
 *   Zlozonosc czasowa:    O(log(m+n) + klogk)                                *
 *   Opis:                 rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
#include <tuple>
using namespace std;

const int MAX_N = 100000, MAX_K = 100000;

int m, n, k;
int xk[MAX_K+1], yk[MAX_K+1];
int x, y, dx, dy;
long long czas;
long long alfa, beta;

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

void odbij() {
  if (x % 2 == 0) {
    dx = -dx;
  } else {
    dy = -dy;
  }
}

tuple<int, int> torusuj(int x, int y, int dx, int dy) {
  int X, Y;
  if (dx == -1) {
    X = x;
  } else {
    X = 4*m - x;
  }
  if (dy == 1) {
    Y = y;
  } else {
    Y = 4*n - y;
  }
  return make_tuple(X, Y);
}

tuple<int, int, int, int> odtorusuj(int X, int Y) {
  if (X == 0) {
    X = 4*m;
  }
  if (X <= 2*m) {
    if (Y < 2*n) { return make_tuple(X, Y, -1, 1); }
    else { return make_tuple(X, 4*n - Y, -1, -1); }
  } else {
    if (Y < 2*n) { return make_tuple(4*m - X, Y, 1, 1); }
    else { return make_tuple(4*m - X, 4*n - Y, 1, -1); }
  }
}

set<long long> zbior_numerow;

long long modulo(long long a, long long b) {
  if (a < 0) {
    a = b - (-a % b);
  }
  return a % b;
}

tuple<int, int, int, int> pozycja(long long t) {
  int X = modulo(m - t, 4*m);
  int Y = modulo(t, 4*n);
  return odtorusuj(X, Y);
}

long long numer(int x, int y, int dx, int dy) {
  int X, Y;
  tie(X, Y) = torusuj(x, y, dx, dy);
  long long t = modulo((m - modulo(X, m)) * beta * 4*n + Y * alfa * m, 4LL*m*n);
  return t;
}

set<long long> numery_klocka(int sx, int sy) {
  set<long long> zbior;
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
    long long num = numer(x, y, dx, dy);
    zbior.insert(num);
  }
  return zbior;
}

void usun_klocek(int x, int y, int dx, int dy) {
  int sx, sy;
  tie(sx, sy) = srodek_pola(x, y, dx, dy);

  set<long long> zbior = numery_klocka(sx, sy);
  for (set<long long>::iterator it = zbior.begin(); it != zbior.end(); ++it)
    zbior_numerow.erase(*it);
}

void ruszaj() {
  long long t = numer(x, y, dx, dy);
  set<long long>::iterator it = zbior_numerow.lower_bound(t);
  long long nast_t;
  if (it != zbior_numerow.end()) {
    nast_t = *it;
    czas += nast_t - t;
  } else {
    nast_t = *zbior_numerow.begin();
    czas += 4LL*n*m - (t - nast_t);
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

tuple<int, int> rozszerzony_euklides(int a, int b) {
  if (b == 0) {
    return make_tuple(1, 0);
  } else {
    int na, nb;
    tie(na, nb) = rozszerzony_euklides(b, a % b);
    return make_tuple(nb, na - a/b*nb);
  }
}

void inicjuj_euklides() {
  int a, b;
  tie(a, b) = rozszerzony_euklides(m, 4*n);
  alfa = a;
  beta = b;
}

void inicjuj_zbior() {
  for (int i = 1; i <= k; i++) {
    set<long long> zbior = numery_klocka(2*xk[i] - 1, 2*yk[i] - 1);
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
  inicjuj_euklides();
  inicjuj_zbior();
  petla();
  printf("%lld\n", czas);
}
