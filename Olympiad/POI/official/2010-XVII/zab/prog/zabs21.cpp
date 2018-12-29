/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs21.cpp                                                *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n * k).               *
 *             Skakanie zabki symulujemy w czasie O(n * m).              *
 *                                                                       *
 *************************************************************************/ 

#include <cstdio>
#include <assert.h>

using namespace std;

const int MAX_N = 1000000;

int n, k;
long long m;
long long p[MAX_N];
int kty[MAX_N];

void oblicz_kte() {
  for (int i = 0; i < n; ++i) {
    int a = i, b = i;
    int nr = 0;
    while (nr < k) {
      if (a == 0) b++;
      else if (b == n - 1) a--;
      else if (p[i] - p[a - 1] <= p[b + 1] - p[i]) a--;
      else b++;
      nr++;
    }

    if (a < 0) kty[i] = b;
    else if (b >= n) kty[i] = a;
    else if (p[i] - p[a] >= p[b] - p[i]) kty[i] = a;
    else kty[i] = b;
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

