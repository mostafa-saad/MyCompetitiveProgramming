/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Bony                                             *
 *   Autor:             Jakub Pachocki                                   *
 *   Zlozonosc czasowa: O(N log N)                                       *
 *   Opis:              Rozwiazanie bledne, zapominamy o long longach    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cassert>

const int N = 1000000;

bool winning[N + 1];
bool sold[N + 1];

int last[N + 1];

int m, n;
int maxWinning;

int result[N + 1];
int nResult;

int main() {
  assert(scanf("%d", &m));
  for (int i = 1; i <= m; ++i) {
    int c;
    assert(scanf("%d", &c));
    winning[c] = true;
    maxWinning = c;
  }
  int clients = 0;
  assert(scanf("%d", &n));
  for (int i = 1; i <= n; ++i) {
    int a;
    assert(scanf("%d", &a));
    if (last[a] == 0) {
      last[a] = a;
    }
    int served = 0;
    for (; last[a] <= maxWinning && served < a; last[a] += a) {
      if (!sold[last[a]]) {
        sold[last[a]] = true;
        ++served;
        if (winning[last[a]]) {
          result[++nResult] = clients + served;
        }
      }
    }
    clients += a;
  }
  printf("%d\n", nResult);
  for (int i = 1; i <= nResult; ++i) {
    printf("%d\n", result[i]);
  }
}
