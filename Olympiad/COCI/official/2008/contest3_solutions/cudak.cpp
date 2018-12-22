#include <cstdio>
#include <cstring>

typedef long long llint;

llint A, B;
llint pow10[16];
llint memo[16][136];
llint min_solution = -1;

llint rec( llint prefix, int digits, int sum ) {
   if( sum < 0 ) return 0;

   llint mini = prefix;
   llint maxi = prefix + pow10[digits]-1;
   if( mini > B || maxi < A ) return 0;

   if( digits == 0 ) {
      if( sum > 0 ) return 0;      
      if( min_solution == -1 ) min_solution = prefix;
      return 1;
   }

   bool memoize = (mini >= A && maxi <= B);
   if( memoize && memo[digits][sum] != -1 ) return memo[digits][sum];

   llint ret = 0;
   for( int dig = 0; dig < 10; ++dig ) 
      ret += rec( prefix + dig*pow10[digits-1], digits-1, sum-dig );   

   if( memoize ) memo[digits][sum] = ret;
   return ret;
}

int main( void ) {
   pow10[0] = 1;
   for( int i = 1; i <= 15; ++i ) pow10[i] = pow10[i-1] * 10;
   
   int S;
   scanf( "%lld%lld%d", &A, &B, &S );
   
   memset( memo, -1, sizeof memo );

   printf( "%lld\n", rec( 0, 15, S ) );
   printf( "%lld\n", min_solution );

   return 0;
}
