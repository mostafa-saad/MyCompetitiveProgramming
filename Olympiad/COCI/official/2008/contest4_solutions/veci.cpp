#include <cstdio>

int freq[10];

int same_digits( int x, int y ) {
   for( int i = 0; i < 10; ++i ) freq[i] = 0;

   while( x > 0 ) { ++freq[x%10]; x /= 10; }
   while( y > 0 ) { --freq[y%10]; y /= 10; }

   for( int i = 0; i < 10; ++i )
      if( freq[i] != 0 ) return 0;

   return 1;
}

int main( void ) {
   int x, y;
   scanf( "%d", &x );

   for( y = x+1; y-x < 1000000 && !same_digits( x, y ); ++y );

   if( y-x >= 1000000 ) printf( "0\n" );
   else printf( "%d\n", y );

   return 0;
}
