/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kolekcjoner Bajtemonow                             *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Zlozonosc pamieciowa: O(sqrt(A))                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <bits/stdc++.h>
#include "ckollib.h"

using namespace std;

typedef long long LL;

const int P = 45007, Q = 45011;
int cp[P], cq[Q];

int main(void) {
  int x = 0, cx = 0, y = 0, cy = 0;
  while (true) {
    int k = karta();
    if (k == 0) {
      break;
    }
    if (x == 0 || x == k) {
      x = k;
      ++cx;
    } else if (y == 0 || y == k) {
      y = k;
      ++cy;
    }
    ++cp[k % P];
    ++cq[k % Q];
  }
  if (y == 0) {
    odpowiedz(x);
    return 0;
  }
  int K = max(cx, cy);
  int mp = -1;
  for (int i = 0; i < P; ++i) {
    if (cp[i] % K != 0) {
      mp = i;
    }
  }
  for (int i = 0; ; ++i) {
    int can = i * P + mp;
    if (cq[can % Q] % K != 0) {
      odpowiedz(can);
      return 0;
    }
  }
  assert(0);
  return 0;
}

