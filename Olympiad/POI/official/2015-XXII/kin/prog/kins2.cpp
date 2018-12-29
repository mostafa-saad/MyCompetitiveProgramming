/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kinoman                                            *
 *   Autor programu:       Tomasz Idziaszek                                   *
 *   Zlozonosc czasowa:    O(n^2)                                             *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)

const int N = 1000000;
int n,m,f[N],w[N],a[N],b[N];
long long s[N],best;

// To trzeba zamienic na drzewo przedzialowe
void dodaj(int l, int p, int w) {
  for(int i=l; i<=p; ++i) {
    s[i] += w;
    best = max(best, s[i]);
  }
}

int main() {
  scanf("%d%d",&n,&m);
  REP(i,n) { scanf("%d",&f[i]); --f[i]; }
  REP(i,m) scanf("%d",&w[i]);
  REP(i,m) a[i] = b[i] = -1;
  REP(i,n) {
    const int F = f[i], W = w[F];
    dodaj(a[F]+1, i, W);
    dodaj(b[F]+1, a[F], -W);
    b[F] = a[F];
    a[F] = i;
  }

  printf("%lld\n", best);
}
