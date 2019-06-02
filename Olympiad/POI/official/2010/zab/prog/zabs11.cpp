/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs11.cpp                                                *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n^2 * log n).         *
 *             Skakanie zabki symulujemy w czasie O(n * m).              *
 *                                                                       *
 *************************************************************************/ 

#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <assert.h>

using namespace std;

const int MAX_N = 1000000;

int n, k;
long long m;
long long p[MAX_N];
int kty[MAX_N];

inline long long ABS(long long x) {
  return x < 0 ? -x : x;
}

void oblicz_kte() {
  for (int i = 0; i < n; ++i) {
    vector<pair<long long, int> > pom;
    for (int j = 0; j < n; ++j) {
      pom.push_back(make_pair(ABS(p[i] - p[j]), j));
    }
    sort(pom.begin(), pom.end());
    if (pom[k].first == pom[k - 1].first) {
      pom[k].second = pom[k - 1].second;
    }
    kty[i] = pom[k].second;
  }
}

void skacz() {
  for (int i = 0; i < n; ++i) {
    long long m0 = m;
    int poz = i;
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

