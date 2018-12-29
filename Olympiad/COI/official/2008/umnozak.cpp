#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef long long llint;

llint memo[18][30][19][13][11];

int f[4] = { 2, 3, 5, 7 };
int k[4] = { 0, 0, 0, 0 };
int code[10][4] = {
   { 0, 0, 0, 0 },
   { 0, 0, 0, 0 },
   { 1, 0, 0, 0 },
   { 0, 1, 0, 0 },
   { 2, 0, 0, 0 },
   { 0, 0, 1, 0 },
   { 1, 1, 0, 0 },
   { 0, 0, 0, 1 },
   { 3, 0, 0, 0 },
   { 0, 2, 0, 0 }
};

llint rec( int digits, llint a, llint pot, llint lo, llint hi ) {   
   llint b = a + pot-1;
   if( a > hi || b < lo ) return 0;
   if( digits == 18 ) return !k[0] && !k[1] && !k[2] && !k[3];   
   
   int memoize = 0;
   if( a >= lo && b <= hi ) memoize = 1;

   if( memoize && memo[digits][k[0]][k[1]][k[2]][k[3]] >= 0 )
      return memo[digits][k[0]][k[1]][k[2]][k[3]];

   pot /= 10;

   llint ret = 0;

   for( int digit = (a!=0); digit <= 9; ++digit ) {
      
      int ok = 1;
      for( int i = 0; i < 4; ++i ) ok &= code[digit][i] <= k[i];
      if( !ok ) continue;

      for( int i = 0; i < 4; ++i ) k[i] -= code[digit][i];
      ret += rec( digits+1, a + digit*pot, pot, lo, hi );
      for( int i = 0; i < 4; ++i ) k[i] += code[digit][i];
   }

   if( memoize ) memo[digits][k[0]][k[1]][k[2]][k[3]] = ret;

   return ret;
}

llint lo, hi;
llint rjesenje;

llint ceil( llint a, llint b ) { return (a+b-1)/b; }
llint floor( llint a, llint b ) { return a/b; }

void gen( llint limit, llint product, int factor ) {
   if( product > 1000000000 || product*product > limit ) return;
   if( factor == 4 ) {
      rjesenje += rec( 0, 0, 1000000000000000000LL, ceil(lo,product), floor(hi,product) );
      return;
   }

   gen( limit, product, factor + 1 );
   ++k[factor];
   gen( limit, product*f[factor], factor );
   --k[factor];
}

int main( void ) {
   scanf( "%lld%lld", &lo, &hi );

   memset( memo, -1, sizeof memo );

   gen( hi, 1, 0 );

   printf( "%lld\n", rjesenje );

   return 0;
}
