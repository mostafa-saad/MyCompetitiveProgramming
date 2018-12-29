/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs13.cpp                                                *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n^2 * log n).         *
 *             Skakanie zabki symulujemy w czasie O(n * log m).          *
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

int perm[2][MAX_N], res[MAX_N];

void skacz() {
	int i1 = 0, i2 = 1;
	long long p2 = 1;
  for (int i = 0; i < n; ++i) {
    perm[0][i]  = kty[i];
		res[i] = i;
	}
	while(p2 <= m) {
		if(p2 & m)
			for(int i = 0; i < n; ++i)
				res[i] = perm[i1][res[i]];
		for(int i = 0; i < n; ++i)
			perm[i2][i] = perm[i1][perm[i1][i]];
		i1 ^= i2;
		i2 ^= i1;
		i1 ^= i2;
		p2 *= 2;
	}
	for(int i = 0; i < n; ++i)
		printf("%d%c", res[i] + 1, (i + 1 < n ? ' ' : '\n'));
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

