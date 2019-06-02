/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Rozklad Fibonacciego                             *
 *   Autor:             Karol Pokorski                                   *
 *   Zlozonosc czasowa: O(log^2(k))                                      *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long int LL;

const int MAXN = 87;

LL fib[MAXN];

int main() {
  int Q;

  fib[0] = 1;
  fib[1] = 1;
  for (int i = 2; i < MAXN; i++)
    fib[i] = fib[i-1]+fib[i-2];
  
  scanf("%d", &Q);

  while (Q--) {
    LL N;
    int res = 0;

    scanf("%lld", &N);

    while (N > 0) {
      LL n = N;

      for (int i = 0; i < MAXN; i++)
        n = min(n, abs(N-fib[i]));

      N = n;

      res++;
    }

    printf("%d\n", res);
  }

  return 0;
}
