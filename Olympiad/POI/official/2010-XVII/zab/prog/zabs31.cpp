/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs31.cpp                                                *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n * log Z * log m).   *
 *             Skakanie zabki symulujemy w czasie O(n * m).              *
 *                                                                       *
 *************************************************************************/ 

#include <cstdio>
#include <assert.h>

using namespace std;

const int MAX_N = 1000000;
const long long MIN_P = 0;
const long long MAX_P = (long long)1000000 * 1000000 * 1000000;

int n, k;
long long m;
long long p[MAX_N];
int kty[MAX_N];

/* Zwraca najmniejsze j (0 <= j < n), takie �e p[i] - p[j] <= d. */
int na_lewo(int i, long long d) {
  int l = 0, r = i;
  while (l < r) {
    int s = (l + r) / 2;
    if (p[i] - p[s] > d) l = s + 1; else r = s;
  }
  return l;
}

/* Zwraca najwi�ksze j (0 <= j < n), takie �e p[j] - p[i] <= d. */
int na_prawo(int i, long long d) {
  int l = i, r = n - 1;
  while (l < r) {
    int s = (l + r + 1) / 2;
    if (p[s] - p[i] > d) r = s - 1; else l = s;
  }
  return l;
}

void oblicz_kte() {
  for (int i = 0; i < n; ++i) {
    int a, b;
    long long l = MIN_P, r = p[n - 1];
    while (l < r) {
      long long s = (l + r) / 2;
      a = na_lewo(i, s);
      b = na_prawo(i, s);
      if (b - a + 1 <= k) l = s + 1; else r = s;
    }
    a = na_lewo(i, l);
    b = na_prawo(i, l);
    if (p[i] - p[a] >= p[b] - p[i]) {
      kty[i] = a;
    } else {
      kty[i] = b;
    }
  }
}

void skacz() {
  for (int i = 0; i < n; ++i) {
    int m0 = m, poz = i;
    while (m0--) {
      poz = kty[poz];
    }
    printf("%d", poz + 1);
    if (i < n - 1) {
      putchar(' ');
    } else {
      puts("");
    }
  }
}

int main() {
  assert(scanf("%d%d%lld", &n, &k, &m) == 3);
  for (int i = 0; i < n; ++i) {
    assert(scanf("%lld", p + i) == 1);
  }
  oblicz_kte();
  skacz();
  return 0;
}

