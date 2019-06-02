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
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)

const int N = 1000000;
int n,m,f[N],w[N],cnt[N];
long long s,best;

int main() {
  scanf("%d%d",&n,&m);
  REP(i,n) { scanf("%d",&f[i]); --f[i]; }
  REP(i,m) scanf("%d",&w[i]);
  REP(i,n) {
    REP(j,m) cnt[j] = 0;
    s = 0;
    for(int j=i; j<n; ++j) {
      const int F = f[j], W = w[F];
      cnt[F]++;
      if (cnt[F] == 1) s += W;
      else if (cnt[F] == 2) s -= W;
      best = max(best, s);
    }
  }
  printf("%lld\n", best);
}
