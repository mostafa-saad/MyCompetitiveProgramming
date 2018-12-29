/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Gra w minima (GRA)                               *
 *   Plik:              gra1.cpp                                         *
 *   Autor:             Jakub Onufry Wojtaszczyk                         *
 *   Opis:              Rozwiazanie autorskie.                           *
 *   Zlozonosc czasowa: O(n * log n)                                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(i,n) for (int i=0; i<n; i++)
#define MAX 1001000

int main() {
  int N;
  int inp[MAX];
  int out[MAX];
  scanf("%d", &N);
  REP (i, N) scanf("%d", &inp[i]);
  sort(&inp[0], &inp[N]);
  out[0] = 0;
  REP (i, N) out[i+1] = max(out[i], inp[i] - out[i]);
  printf("%d\n", out[N]);
  return 0;
}  
