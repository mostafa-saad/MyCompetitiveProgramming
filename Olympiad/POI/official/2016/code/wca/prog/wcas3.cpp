/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Wcale nie Nim                                      *
 *   Autor programu:       Pawel Parys                                        *
 *   Opis:                 rozwiazanie wolne                                  *
 *****************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

int N;
int suma;
int ile1[500000];

int find_max() {
  int best = 0;
  for (int i = 0; i<N; ++i)
    if (ile1[i]>ile1[best])
      best = i;
  return best;
}

int main() {
  scanf("%d", &N);
  for (int i = 0; i<N; ++i) {
    int x;
    scanf("%d", &x);
    while (x) {
      ++suma;
      if (x&1)
        ++ile1[i];
      else
        ile1[i] = 0;
      x /= 2;
    }
  }
  for (;;) {
    ile1[find_max()] = 0;
    ++suma;
    int i = find_max();
    if (ile1[i]<=1) break;
    --ile1[i];
  }
  printf("%d\n", suma*2-1);
}
