/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Rozklad Fibonacciego                             *
 *   Autor:             Karol Pokorski                                   *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Rozwiazanie prawie wzorcowe                      *
 *                      (podliniowe wzgledem k)                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long int LL;

const int MAXN = 87;
const int MAXR = 21;
const int JUMP = 9;

LL fib[MAXN];
int result;

int Compute(LL N, int R) {
  if (R >= result)
    return MAXR;
  if (N == 0) {
    result = min(result, R);
    return R;
  }

  int p = 0;

  while ((p+JUMP < MAXN) && (N-fib[p+JUMP] > 0))
    p += JUMP;
  while ((p+1 < MAXN) && (N-fib[p+1] > 0))
    p++;

  return min(Compute(N-fib[p], R+1), Compute(fib[p+1]-N, R+1));
}

int main() {
  int Q;

  fib[0] = 1;
  fib[1] = 1;
  for (int i = 2; i < MAXN; i++)
    fib[i] = fib[i-1]+fib[i-2];
  
  scanf("%d", &Q);

  while (Q--) {
    LL N;

    scanf("%lld", &N);

    result = MAXR;
    printf("%d\n", Compute(N, 0));
  }

  return 0;
}
