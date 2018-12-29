/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Wyrownywanie terenu                              *
 *   Autor:             Tomasz Idziaszek                                 *
 *   Opis:              Rozwiazanie bledne, wzorcowka bez long longow    *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef int ll;
#define REP(i,n) for(int i=0;i<(n);++i)
#define FORE(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)

const int N = 1000100;
int n;
ll a,b,d[N],g;
ll A[N],B[N],X[N+1],Y[N+1];
ll alfa,beta,D[N+1];
ll inf = 1000000000;

/* A structure which holds a segment of a piecewise-linear function */
struct segment {
   ll sl,beg,num;
   segment(ll sl,ll beg,ll num) : sl(sl), beg(beg), num(num) { }
};

/* Vectors of segments which lie on the left and on the right of
   the minimum of the function */
vector<segment> left[N+1],right[N+1];

/* Extended Euclidean algorithm */
void euclid(ll a, ll b, ll& x, ll& y) {
   if (b == 0) { x = 1; y = 0; }
   else {
      ll xp, yp;
      euclid(b, a%b, xp, yp);
      x = yp;
      y = xp - a/b*yp;
   }
}

/* Mathematically correct floor(a/b) */
inline ll flr(ll a, ll b) {
   if (a>0 || a%b==0) return a/b;
   return a/b-1;
}

/* Value of the function F in point k */
inline ll fun(ll k) {
   return abs(beta + k*b) + abs(alfa - k*a);
}

/* Add a segment */
void add_segment(int i, ll sl, ll beg, ll end) {
   if (end-beg == 0) return;
   if (sl <= 0) left[i].push_back(segment(sl, end, end-beg));
   if (sl >= 0) right[i].push_back(segment(sl, beg, end-beg));
}

int main() {
   scanf("%d%d%d",&n,&a,&b);
   REP(i,n) scanf("%d",&d[i]); 

   if (a < b) swap(a, b);

   /* Check whether solution exists */
   g = __gcd(a,b);
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


   /* Calculate an initial solution */
   ll ex,ey;
   euclid(a,b,ex,ey);
   REP(i,n) {
      A[i] = ex*d[i];
      B[i] = ey*d[i];
   }

   X[0] = A[0]; REP(i,n-1) X[i+1] = A[i+1] - A[i]; X[n] = -A[n-1];
   Y[0] = B[0]; REP(i,n-1) Y[i+1] = B[i+1] - B[i]; Y[n] = -B[n-1];

   /* Calculate the piecewise-linear functions F(k) */
   REP(i,n+1) {

      beta = X[i];
      alfa = Y[i];

      ll b1 = flr(-beta,b);
      ll a1 = flr(alfa,a);
      ll sl = b-a;

      if (a1 < b1) {
         swap(b1, a1);
         sl = a-b;
      }

      add_segment(i, -(a+b), -inf, b1 );

      if ( b1+1 <= a1 ) {
         add_segment(i, fun(b1+1) - fun(b1), b1, b1+1 );
         add_segment(i, sl, b1+1, a1 );
         add_segment(i, fun(a1+1) - fun(a1), a1, a1+1 );
      }
      else add_segment(i, fun(b1+1) - fun(b1), b1, b1+1 );

      add_segment(i, a+b, a1+1, inf );

   }

   ll theans = -1;

   /* Case right */
   {
      ll sum = 0, ans = 0;
      REP(i,n+1) {
         D[i] = right[i].front().beg;
         sum += D[i];
         beta = X[i];
         alfa = Y[i];
         ans += fun(D[i]);
      }
      if (sum > 0) ans = -1;
      else {
         vector<pair<ll,ll> > v;
         REP(i,n+1) FORE(j,right[i]) v.push_back(make_pair(j->sl,j->num));
         sort(v.begin(),v.end());
         FORE(i,v) {
            ll ile = min(i->second, -sum);
            ans += i->first * ile;
            sum += ile;
            if (sum == 0) break;
         }
      }
      if (ans != -1) theans = ans;
   }

   /* Case left */
   {
      REP(i,n+1) reverse(left[i].begin(),left[i].end());
      ll sum = 0, ans = 0;
      REP(i,n+1) {
         D[i] = left[i].front().beg;
         sum += D[i];
         beta = X[i];
         alfa = Y[i];
         ans += fun(D[i]);
      }
      if (sum < 0) ans = -1;
      else {
         vector<pair<ll,ll> > v;
         REP(i,n+1) FORE(j,left[i]) v.push_back(make_pair(-j->sl,j->num));
         sort(v.begin(),v.end());
         FORE(i,v) {
            ll ile = min(i->second, sum);
            ans += i->first * ile;
            sum -= ile;
            if (sum == 0) break;
         }
      }
      if (ans != -1 && (theans == -1 || ans < theans)) theans = ans;
   }

   printf("%d\n",theans/2);
}
