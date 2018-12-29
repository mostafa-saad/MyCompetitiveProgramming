/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Okropny wiersz                                   *
 *   Autor:             Jakub Pachocki                                   *
 *   Zlozonosc czasowa: O(n log n + q * n^(1 / log log n))               *
 *   Opis:              Rozwiazanie powolne (tablicowanie i sprawdzanie  *
 *                      dzielnikow)                                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

const int B = 197;

const int N = 500005;

vector<int> divisors[N];

int n;

char s[N];

int h[N];
int p[N];

int main() {
  scanf("%d",&n);
  assert(scanf("%s", s + 1));

  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      divisors[j].push_back(i);
    }
  }

  p[0] = 1;
  for (int i = 1; i <= n; ++i) {
    p[i] = p[i - 1] * B;
  }

  h[0] = 0;
  for (int i = 1; i <= n; ++i) {
    h[i] = h[i - 1] + (p[i] * s[i]);
  }

  int nQueries;
  assert(scanf("%d", &nQueries));

  for (int query = 1; query <= nQueries; ++query) {
    int l, r;
    assert(scanf("%d %d", &l, &r));
    int m = r - l + 1;
    for (vector<int>::iterator it = divisors[m].begin(); it != divisors[m].end(); ++it) {
      int d = *it;
      if ((h[r - d] - h[l - 1]) * p[d] == h[r] - h[l + d - 1]) {
        printf("%d\n", d);
        break;
      }
    }
  }
}
