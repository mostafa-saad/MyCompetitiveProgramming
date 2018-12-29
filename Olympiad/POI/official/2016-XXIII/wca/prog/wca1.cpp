/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Wcale nie Nim                                      *
 *   Autor programu:       Pawel Parys                                        *
 *   Opis:                 Rozwiazanie wzorcowe weryfikujace                  *
 *****************************************************************************/


#include <cstdio>
#include <algorithm>

using namespace std;

int N;
int suma;
int tyle1[40];

int najw = 39;

inline void find_max() {
  while (!tyle1[najw])
    --najw;
}

int main() {
  scanf("%d", &N);
  suma = N-1;
  for (int i = 0; i<N; ++i) {
    int x, ile1 = 0;
    scanf("%d", &x);
    while (x) {
      ++suma;
      if (x&1)
        ++ile1;
      else
        ile1 = 0;
      x /= 2;
    }
    ++tyle1[ile1];
  }
  find_max();
  --tyle1[najw];
  for (int a = 0; a<N-1; ++a) {
    find_max();
    if (najw>1) {
      --tyle1[najw];
      ++tyle1[najw-1];
      find_max();
      --tyle1[najw];
    }
    else {
      --tyle1[najw];
      --suma;
    }
  }
  printf("%d\n", suma*2+1);
}
