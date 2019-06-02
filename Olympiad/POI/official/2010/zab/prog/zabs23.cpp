/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs23.cpp                                                *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n * k).               *
 *             Skakanie zabki symulujemy w czasie O(n * log m).          *
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

