#include <algorithm>
#include <cstdio>

#define MAX 100000

using namespace std;

typedef long long llint;

const llint inf = 1000000000000000LL;

llint calc( int a, int b ) {
   if( a > b ) return a - b;
   if( b > a ) return b - a;
   return inf;
}

int n;
int a[MAX], b[MAX];
int perm[3];
llint dp[MAX+1];

int main( void ) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) scanf( "%d%d", &a[i], &b[i] );

   sort( a, a+n );
   sort( b, b+n );

   dp[n] = 0;

   for( int i = n-1; i >= 0; --i ) {
      dp[i] = inf;

      for( int k = 1; k <= 3 && i+k <= n; ++k ) {
         for( int j = 0; j < k; ++j ) perm[j] = j;

         do {
            llint cost = 0;

            for( int j = 0; j < k; ++j )
               cost += calc( a[i+j], b[i+perm[j]] );

            dp[i] = min( dp[i], cost + dp[i+k] );
         } while( next_permutation( perm, perm+k ) );
      }
   }

   printf( "%lld\n", dp[0] );

   return 0;
}
