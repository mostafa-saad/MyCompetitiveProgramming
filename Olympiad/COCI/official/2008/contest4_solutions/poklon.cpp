#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define MAX 1000000
#define MAXN 100000

struct interval { int lo, hi; };
bool operator < ( const interval &A, const interval &B ) {
   if( A.lo != B.lo ) return A.lo > B.lo;
   if( A.hi != B.hi ) return A.hi < B.hi;
   return 0;
}

int n;
vector<interval> intervals;
int how[MAXN];
int dp[MAXN];

struct fenwick {
   int a[MAX+1];

   fenwick() { memset( a, -1, sizeof a ); }

   int query( int X ) {
      int ret = -1;
      for( int x = X; x > 0; x -= x&-x )
         if( a[x]!=-1 && (ret==-1 || dp[a[x]]>dp[ret]) ) ret = a[x];
      return ret;
   }

   void update( int X, int i ) {
      for( int x = X; x <= MAX; x += x&-x )
         if( a[x] == -1 || dp[i] > dp[a[x]] ) a[x] = i;
   }
} L;

int main( void ) {
   scanf( "%d", &n );

   for( int i = 0; i < n; ++i ) {
      interval I;
      scanf( "%d%d", &I.lo, &I.hi );
      intervals.push_back( I );
   }
   sort( intervals.begin(), intervals.end() );

   int ret = 0;

   for( int i = 0; i < n; ++i ) {
      dp[i] = 1;
      how[i] = -1;

      int x = L.query( intervals[i].hi );

      if( x != -1 ) {
         dp[i] = dp[x] + 1;
         how[i] = x;
      }

      L.update( intervals[i].hi, i );

      if( dp[i] > dp[ret] ) ret = i;
   }

   printf( "%d\n", dp[ret] );
   while( ret != -1 ) {
      printf( "%d %d\n", intervals[ret].lo, intervals[ret].hi );
      ret = how[ret];
   }

   return 0;
}
