/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ORK (Orka)                                     *
 *   Plik:                ork2.cpp                                       *
 *   Autor:               Piotr Stañczyk                                 *
 *   Opis:                Rozwiazanie optymalne o zlozonosci O(n*m)      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;

#define FOR(x,b,e) for(int x=b;x<=(e);++x)
#define FORD(x,b,e) for(int x=b;x>=(e);--x)
#define REP(x,n) for(int x=0;x<(n);++x)

const int INF = 1000000001;
const int MaxN = 2001;
int vals[MaxN][MaxN], n, m, k;
int summ[MaxN][MaxN];
int sumn[MaxN][MaxN];

int Count(int l, int &used) {
  used = 0;
  int px=1, kx=n, py=1, ky=m, sol=0;
  while(px<=kx && py<=ky) {
    sol++;
    if (sumn[kx][py]-sumn[px-1][py] <= k) py++; else
    if (sumn[kx][ky]-sumn[px-1][ky] <= k) ky--; else
    if (l > 0 && summ[px][ky]-summ[px][py-1] <= k) {
      px++;
      l--;
      used++;
    } else if (summ[kx][ky]-summ[kx][py-1] > k) return INF; else
    kx--;
  }
  return sol;
}

int Rozwiaz() {
  FOR(x, 1, n) FOR(y, 1, m) {
    sumn[x][y] = sumn[x-1][y] + vals[x][y];
    summ[x][y] = summ[x][y-1] + vals[x][y];
  }
  int sol = INF;
  FORD(x,n,0) {
    int u;
    sol = min(sol, Count(x, u));
    x = min(x, u);
  }
  return sol;
}

void Obroc() {
  REP(x, n+1) REP(y, m+1) summ[x][y] = vals[x][y];
  REP(x, n+1) REP(y, m+1) vals[y][x] = summ[x][y];
  swap(n, m);
}

int main() {
  scanf("%d %d %d", &k, &m, &n);
  FOR(x, 0, n) vals[x][0] = 0;
  FOR(x, 0, m) vals[0][x] = 0;
  FOR(x, 1, n) FOR(y, 1, m) scanf("%d", &vals[x][y]);
  int sol = Rozwiaz();
  Obroc();
  sol = min(sol, Rozwiaz());
  printf("%d\n", sol);
  return 0;
}
