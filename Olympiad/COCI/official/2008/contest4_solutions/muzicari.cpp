#include <cstdio>
#include <cstring>

#define MAXN 500
#define MAXT 5000

int T, n;
int dp[MAXN+1][MAXT+1];
int pause[MAXN+1];
int group[MAXN+1];

int main( void ) {
   scanf( "%d%d", &T, &n );

   dp[0][0] = 1;

   for( int i = 1; i <= n; ++i ) {
      scanf( "%d", &pause[i] );

      for( int t = 0; t <= T; ++t ) {
         if( dp[i-1][t] ) dp[i][t] = 1;
         if( t >= pause[i] && dp[i-1][t-pause[i]] ) dp[i][t] = 2;
      }
   }

   int i = n, t = T;
   while( !dp[i][t] ) --t;

   for( int i = n; i >= 1; --i )
      if( (group[i] = dp[i][t]) == 2 )
         t -= pause[i];

   int sum1 = 0, sum2 = 0;

   for( int i = 1; i <= n; ++i ) {
      if( i > 1 ) printf( " " );

      if( group[i] == 1 ) {
         printf( "%d", sum1 );
         sum1 += pause[i];
      } else {
         printf( "%d", sum2 );
         sum2 += pause[i];
      }
   }
   printf( "\n" );

   return 0;
}
