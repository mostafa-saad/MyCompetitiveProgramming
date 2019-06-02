/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Arkanoid                                           *
 *   Autor programu:       Tomasz Idziaszek                                   *
 *   Zlozonosc czasowa:    O((m+n+k)log(m+n) + (m+n)k)                        *
 *   Opis:                 rozwiazanie wolne                                  *
 *****************************************************************************/

#include <algorithm>
#include <cstdio>
#include <map>
#include <tuple>
#include <vector>
using namespace std;

const int MAX_N = 1000, MAX_K = 100000;

int m, n, k;
int xk[MAX_K+1], yk[MAX_K+1];
int x, y, dx, dy;
long long czas;
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

bool porownuj_przekatna_1(const tuple<int, int>& a, const tuple<int, int>& b) {
  return get<0>(a) - get<1>(a) < get<0>(b) - get<1>(b);
}

bool porownuj_przekatna_2(const tuple<int, int>& a, const tuple<int, int>& b) {
  return get<0>(a) + get<1>(a) < get<0>(b) + get<1>(b);
}

void inicjuj_graf() {
  vector<tuple<int, int> > v;
  for (int sx = 1; sx <= 2*m-1; sx += 2) {
    v.push_back(make_pair(sx, 0));
    v.push_back(make_pair(sx, 2*n));
  }
  for (int sy = 1; sy <= 2*n-1; sy += 2) {
    v.push_back(make_pair(0, sy));
    v.push_back(make_pair(2*m, sy));
  }
  for (int i = 1; i <= k; i++) {
    int sx = 2*xk[i]-1;
    int sy = 2*yk[i]-1;
    v.push_back(make_pair(sx, sy+1));
    v.push_back(make_pair(sx, sy-1));
    v.push_back(make_pair(sx-1, sy));
    v.push_back(make_pair(sx+1, sy));
  }
  sort(v.begin(), v.end());
  stable_sort(v.begin(), v.end(), porownuj_przekatna_1);
  for (int i = 0; i < int(v.size()); i += 2) {
    int xa, ya, xb, yb;
    tie(xa, ya) = v[i];
    tie(xb, yb) = v[i+1];
    int len = xb - xa;
    graf(xa, ya, 1, 1) = make_tuple(xb, yb, len);
    graf(xb, yb, -1, -1) = make_tuple(xa, ya, len);
  }
  sort(v.begin(), v.end(), greater<tuple<int, int> >());
  stable_sort(v.begin(), v.end(), porownuj_przekatna_2);
  for (int i = 0; i < int(v.size()); i += 2) {
    int xa, ya, xb, yb;
    tie(xa, ya) = v[i];
    tie(xb, yb) = v[i+1];
    int len = xa - xb;
    graf(xa, ya, -1, 1) = make_tuple(xb, yb, len);
    graf(xb, yb, 1, -1) = make_tuple(xa, ya, len);
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
  inicjuj_graf();
  petla();
  printf("%lld\n", czas);
}
