/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ORK (Orka)                                     *
 *   Plik:                orkb6.cpp                                      *
 *   Autor:               Piotr Stañczyk                                 *
 *   Opis:                Rozwiazanie heurystyczne o zlozonosci O(n*m)   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
#define REP(x,n) for(int x=0;x<(n);++x)

const int MaxN = 2000;
int vals[MaxN][MaxN];

int main() {
  int n,m,k;
  scanf("%d %d %d", &k, &m, &n);
  LL s=0;
  REP(x, n) REP(y, m) {
    scanf("%d", &vals[x][y]);
    s += (LL) vals[x][y];
  }
  LL on = 0, om = 0;
  REP(x, n) {
    LL sum = 0;
    REP(y, m) sum += (LL) vals[x][y];
    on += max((LL)0, sum-k);
  }
  REP(y, m) {
    LL sum = 0;
    REP(x, n) sum += (LL) vals[x][y];
    om += max((LL)0, sum-k);
  }  
  int lRes = (int) max(max((LL) min(n, m), (s+k-1)/k),(LL) min(n+(on+k-1)/k, m+(om+k-1)/k));
  int uRes = n+m-1;
  printf("%d\n", (rand() % (uRes-lRes+1))+lRes);
  return 0;
}
