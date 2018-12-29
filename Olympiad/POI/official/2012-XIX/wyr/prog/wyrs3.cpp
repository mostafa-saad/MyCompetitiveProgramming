/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Wyrownywanie terenu                              *
 *   Autor:             Tomasz Idziaszek                                 *
 *   Zlozonosc czasowa: O(n M^2)                                         *
 *   Opis:              Rozwiazanie powolne, spamietywanie               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
typedef int ll;
const ll inf = 1000000000;

const int N=210;

int n;
ll a,b,d[N];
ll x,y,ai[N],bi[N];
ll bound;

map<pair<int,int>, ll> memo;

void euclid(ll a, ll b, ll& x, ll& y) {
   if (b == 0) { x = 1; y = 0; }
   else {
      ll xp, yp;
      euclid(b, a%b, xp, yp);
      x = yp;
      y = xp - a/b*yp;
   }
}

ll dyn(int i, int al, int bl) {

   pair<int,int> key = make_pair(i,al);
   if (memo.find(key) != memo.end()) return memo[key];

   if (i==n) {
      return abs(al) + abs(bl);
   }
   else {
      ll minw = inf;

      for(int aii = ai[i], bii = bi[i]; max(abs(aii),abs(bii)) <= bound; aii += b, bii -= a)
         minw = min(minw, dyn(i+1, aii, bii) + abs(aii - al) + abs(bii - bl) );
      for(int aii = ai[i], bii = bi[i]; max(abs(aii),abs(bii)) <= bound; aii -= b, bii += a)
         minw = min(minw, dyn(i+1, aii, bii) + abs(aii - al) + abs(bii - bl) );
      
      return memo[key] = minw;
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
   
   /* Special case when a=b */
   if (a == b) {
      ll ans = abs(d[0]) + abs(d[n-1]);
      REP(i,n-1) ans += abs(d[i+1] - d[i]);
      printf("%d\n",ans/2);
      return 0;
   }

   /* Initial solution */
   bound = max(a, b);
   REP(i,n) bound = max(bound, abs(d[i]));
   bound *= 17;

   euclid(a,b,x,y);
   ai[0] = bi[0] = 0;
   REP(i,n) {
      ai[i] = x*d[i];
      bi[i] = y*d[i];

      /* Find pointwise-minimal solution */
      while ( abs(ai[i])+abs(bi[i]) > abs(ai[i]+b)+abs(bi[i]-a) ) ai[i]+=b, bi[i]-=a;
      while ( abs(ai[i])+abs(bi[i]) > abs(ai[i]-b)+abs(bi[i]+a) ) ai[i]-=b, bi[i]+=a;
   }

   ll ans = dyn(0,0,0)/2;
   printf("%d\n",ans);
}
