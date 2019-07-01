/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Wyrownywanie terenu                              *
 *   Autor:             Tomasz Idziaszek                                 *
 *   Opis:              Rozwiazanie bledne, wypisuje tylko minimalne     *
 *                      rozwiazanie poczatkowe (nie probuje go           *
 *                      poprawiac)                                       *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <cassert>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
typedef long long ll;
const ll inf = 1000000000000000000LL;

const int N=110000;
const int M=110000;

int n;
ll a,b,d[N];
ll x,y,ai[N],bi[N],X[N],Y[N];

void euclid(ll a, ll b, ll& x, ll& y) {
   if (b == 0) { x = 1; y = 0; }
   else {
      ll xp, yp;
      euclid(b, a%b, xp, yp);
      x = yp;
      y = xp - a/b*yp;
   }
}

void smallest(ll& x, ll& y) {
   int sign=1,swp=0;
   if (x <= 0 && y >= 0) { x*=-1; y*=-1; sign*=-1; }
   if (x >= 0 && y <= 0) {
      ll t = min(x/b, -y/a);
      x -= t*b; y += t*a;
      if (abs(x)+abs(y) <= abs(x-b)+abs(y+a)) { x*=sign; y*=sign; return; }
      x -= b; y += a;
   }
   if (x <= 0) { x*=-1; y*=-1; sign*=-1; }
   ll t = y/a;
   x += t*b; y -= t*a;
   if (abs(x)+abs(y) <= abs(x+b)+abs(y-a)) { x*=sign; y*=sign; if (swp) swap(x,y); return; }
   x += b; y -= a;
   x*=sign; y*=sign; if (swp) swap(x,y);
}

int main() {
   scanf("%d%lld%lld",&n,&a,&b);
   REP(i,n) scanf("%lld",&d[i]);
   if (a < b) swap(a,b);

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
   euclid(a,b,x,y);
   REP(i,n) {
      ai[i] = x*d[i];
      bi[i] = y*d[i];

      /* Initial pointwise-minimal solution */
      smallest(ai[i],bi[i]);
   }

   X[0] = ai[0]; REP(i,n-1) X[i+1] = ai[i+1] - ai[i]; X[n] = -ai[n-1];
   Y[0] = bi[0]; REP(i,n-1) Y[i+1] = bi[i+1] - bi[i]; Y[n] = -bi[n-1];

   ll ans = 0;
   REP(i,n+1) ans += abs(X[i]) + abs(Y[i]);
   printf("%lld\n",ans/2);
}
