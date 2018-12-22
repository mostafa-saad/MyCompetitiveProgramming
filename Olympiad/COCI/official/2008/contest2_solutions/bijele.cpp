#include <cstdio>

int main( void ) {
   int target[] = { 1, 1, 2, 2, 2, 8 };

   for( int i = 0; i < 6; ++i ) {
      int x;
      scanf( "%d", &x );

      if( i ) printf( " " );
      printf( "%d", target[i] - x );
   }
   
   printf( "\n" );

   return 0;
}
