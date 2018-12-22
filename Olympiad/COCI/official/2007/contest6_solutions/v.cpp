
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 6 - Task V.CPP
  Programming language C++
*/

#include <cstdio>
#include <cstring>

using namespace std;

typedef long long llint;

#define GRANICA 100000

llint A, B, X;
int ok[10];

llint memo[12][GRANICA][2]; // koliko jos znamenaka, koliki je ostatak dosad, jesu li dosad sve nule

llint rec( int n, llint prefix ) {

   llint maxi = prefix, mini = prefix;
   for( int i = 0; i < n; ++i ) maxi = maxi*10 + 9;
   for( int i = 0; i < n; ++i ) mini = mini*10 + 0;

   if( maxi < A || mini > B ) return 0;
   if( n == 0 ) return prefix%X==0;

   int memoize = mini >= A && maxi <= B;

   llint & ref = memo[n][prefix%X][prefix==0];
   if( memoize && ref >= 0 ) return ref;

   llint ret = 0;
   for( int dig = 0; dig < 10; ++dig )
      if( ok[dig] || dig==0 && prefix==0 )
         ret += rec( n-1, prefix*10+dig );

   if( memoize ) ref = ret;

   return ret;
}

int main( void ) {
   scanf( "%lld%lld%lld", &X, &A, &B );

   for( char c; scanf( " %c", &c ) == 1; ok[c-'0'] = 1 );

   llint ret = 0;

   if( X >= GRANICA ) {
      for( llint x = X; x <= B; x += X  ) {
         int cool = 1;
         for( llint y = x; cool && y; y /= 10 ) cool &= ok[y%10];
         if( cool && x >= A ) ++ret;
      }
   } else {
      memset( memo, -1, sizeof memo );
      ret = rec( 11, 0 );
   }

   printf( "%lld\n", ret );

   return 0;
}
