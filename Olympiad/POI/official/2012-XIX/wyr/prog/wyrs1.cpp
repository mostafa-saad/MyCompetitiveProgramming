/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Wyrownywanie terenu                              *
 *   Autor:             Tomasz Idziaszek                                 *
 *   Zlozonosc czasowa: O(n M^2)                                         *
 *   Opis:              Rozwiazanie powolne, programowanie dynamiczne    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
typedef int ll;
const ll inf = 1000000000;

const int N=210;
const int M=210;

int n;
ll a,b,d[N];
ll x,y,ai[N],bi[N],dyn[N][2*M];
ll bound;

void euclid(ll a, ll b, ll& x, ll& y) {
   if (b == 0) { x = 1; y = 0; }
   else {
      ll xp, yp;
      euclid(b, a%b, xp, yp);
      x = yp;
      y = xp - a/b*yp;
   }
}

int main() {
   scanf("%d%d%d",&n,&a,&b);
   if (n > 200) for(;;);
   REP(i,n) scanf("%d",&d[i]);

   /* Check whether solution exists */
   ll g = __gcd(a,b);
   REP(i,n) if (d[i] % g != 0) {
      printf("-1\n");
      return 0;
   }
   REP(i,n) d[i] /= g;
   a /= g;
   b /= g;

   /* Initial solution */
   bound = max(a, b);
   REP(i,n) bound = max(bound, abs(d[i]));

   euclid(a,b,x,y);
   ai[0] = bi[0] = 0;
   REP(i,n) {
      ai[i+1] = x*d[i];
      bi[i+1] = y*d[i];

      /* Initial pointwise-minimal solution */
      while ( abs(ai[i])+abs(bi[i]) > abs(ai[i]+b)+abs(bi[i]-a) ) ai[i]+=b, bi[i]-=a;
      while ( abs(ai[i])+abs(bi[i]) > abs(ai[i]-b)+abs(bi[i]+a) ) ai[i]-=b, bi[i]+=a;
   }

   /* Dynamic programming */
   for(int z=-bound; z<=bound; ++z)
      dyn[n][bound+z] = abs(ai[n] + b*z) + abs(bi[n] - a*z);
   for(int i=n-1; i>=0; --i) {
      for(int z=-bound; z<=bound; ++z) {
         ll minw = inf;
         for(int zp=-bound; zp<=bound; ++zp) {
            minw = min(minw, dyn[i+1][bound+zp]
                  + abs(ai[i+1] + b*zp - (ai[i] + b*z))
                  + abs(bi[i+1] - a*zp - (bi[i] - a*z)));
         }
         dyn[i][bound+z] = minw;
      }
   }

   printf("%d\n",dyn[0][bound+0]/2);
}
