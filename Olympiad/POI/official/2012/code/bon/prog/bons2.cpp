/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Bony                                             *
 *   Autor:             Jakub Pachocki                                   *
 *   Zlozonosc czasowa: O(N^2)                                           *
 *   Opis:              Rozwiazanie powolne, wielokrotnosci przegladamy  *
 *                      zawsze od poczatku                               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cassert>

const int N = 1000000;

bool winning[N + 1];
bool sold[N + 1];

int m, n;
int maxWinning;

long long result[N + 1];
int nResult;

int main() {
  assert(scanf("%d", &m));
  for (int i = 1; i <= m; ++i) {
    int c;
    assert(scanf("%d", &c));
    winning[c] = true;
    maxWinning = c;
  }
  long long clients = 0;
  assert(scanf("%d", &n));
  for (int i = 1; i <= n; ++i) {
    int a;
    assert(scanf("%d", &a));
    int served = 0;
    for (int j = a; j <= maxWinning && served < a; j += a) {
      if (!sold[j]) {
        sold[j] = true;
        ++served;
        if (winning[j]) {
          result[++nResult] = clients + served;
        }
      }
    }
    clients += a;
  }
  printf("%d\n", nResult);
  for (int i = 1; i <= nResult; ++i) {
    printf("%lld\n", result[i]);
  }
}
