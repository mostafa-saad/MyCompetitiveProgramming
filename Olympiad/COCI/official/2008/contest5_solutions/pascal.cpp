#include <cstdio>

int main( void ) {
   int N;
   scanf( "%d", &N );

   int d = 1;
   do {
      d = d + 1;
      if( d*d > N ) d = N;
   } while( N%d != 0 );

   printf( "%d\n", N-N/d );

   return 0;
}
