/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Arkanoid                                           *
 *   Autor programu:       Tomasz Idziaszek                                   *
 *   Zlozonosc czasowa:    O(m+n+klog(m+n+k))                                 *
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

int idz_do_sciany(int x, int y, int dx, int dy) {
  int len = 2*MAX_N+1;
  int kand[] = { -x/dx, (2*m-x)/dx, -y/dy, (2*n-y)/dy };
  for (int i = 0; i < 4; ++i) {
    if (kand[i] >= 0 and sciana(x + kand[i]*dx, y + kand[i]*dy, dx, dy)) {
      len = min(len, kand[i]);
    }
  }
  return len;
}

map<tuple<int, int, int, int>, int> przek;
tuple<int, int, int, int> przek_poz[MAX_N*4];
long long przek_num[MAX_N*4];
set<long long> zbior_numerow;

long long numer(int x, int y, int dx, int dy) {
  int len = idz_do_sciany(x, y, -dx, -dy);
  tuple<int, int, int, int> klucz = make_tuple(x - dx*len, y - dy*len, dx, dy);
  return przek_num[przek[klucz]] + len;
}


tuple<int, int, int, int> pozycja(long long t) {
  int indeks = upper_bound(przek_num, przek_num + 2*(m+n), t) - przek_num;
  indeks--;
  int x, y, dx, dy;
  tie(x, y, dx, dy) = przek_poz[indeks];
  long long len = t - przek_num[indeks];
  return make_tuple(x + dx*len, y + dy*len, dx, dy);
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

void inicjuj_numery() {
  x = m; y = 0;
  dx = -1; dy = 1;
  long long t = 0;

  for (int i = 0; i < 2*(m+n); ++i) {
    tuple<int, int, int, int> klucz = make_tuple(x, y, dx, dy);
    przek[klucz] = i;
    przek_poz[i] = make_tuple(x, y, dx, dy);
    przek_num[i] = t;
    int len = idz_do_sciany(x, y, dx, dy);
    t += len;
    x += dx * len;
    y += dy * len;
    odbij();
  }
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
  inicjuj_numery();
  inicjuj_zbior();
  petla();
  printf("%lld\n", czas);
}
