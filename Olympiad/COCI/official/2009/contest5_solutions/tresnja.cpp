#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long llint;

llint A, B;
llint p10[16];
llint memo[16][11];

llint intersect( int n, llint prefix ) {
   if( n < 0 ) return 0;
   llint lo = max( prefix * p10[n], A );
   llint hi = min( (prefix+1) * p10[n] - 1, B );
   if( lo > hi ) return 0;
   return hi-lo+1;
}

llint rec( int n, int prev, llint prefix ) {
   llint mini = prefix * p10[n];
   llint maxi = (prefix+1) * p10[n] - 1;

   if( mini > B || maxi < A ) return 0;
   if( mini >= A && maxi <= B && memo[n][prev] != -1 ) return memo[n][prev];

   llint ret = 0;
   for( int digit = 0; digit <= 9; ++digit ) {
      if( digit == prev ) continue;
      
      llint t = prefix;
      for( int k = 1; k <= n; ++k ) {
         t = t*10+digit;
         ret += digit * k * k * (intersect( n-k, t )-intersect( n-k-1, t*10+digit)) + rec( n-k, digit, t );
      }
   }

   if( mini >= A && maxi <= B ) memo[n][prev] = ret;

   return ret;
}

int main( void ) {
   scanf( "%lld%lld", &A, &B );

   p10[0] = 1;
   for( int i = 1; i <= 15; ++i ) p10[i] = p10[i-1] * 10;

   memset( memo, -1, sizeof memo );
   printf( "%lld\n", rec( 15, 10, 0 ) );

   return 0;
}
