/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Rozklad Fibonacciego                             *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(log(k))                                        *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

int rozklad(long long k) {
  long long x = 1, y = 1;
  while (y < k) {
    long long z = x + y;
    x = y;
    y = z;
  }
  int r = 0;
  while (k > 0) {
    /* Niezmiennik: x <= k < y, x i y to kolejne liczby Fibonacciego */
    if (k - x <= y - k) k = k - x;
    else k = y - k;
    ++r;
    while (x >= k) {
      long long z = y - x;
      y = x;
      x = z;
    }
  }
  return r;
}

int main() {
  int p;
  scanf("%d", &p);
  while (p--) {
    long long k;
    scanf("%lld", &k);
    printf("%d\n", rozklad(k));
  }
  return 0;
}
