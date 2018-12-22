#include <cstdio>

int f( int x, int a, int b ) {
   return (x-1) % (a+b) < a;
}

void solve( int x, int a, int b, int c, int d ) {
   if( f( x, a, b ) + f( x, c, d ) == 0 ) printf( "none\n" );
   if( f( x, a, b ) + f( x, c, d ) == 1 ) printf( "one\n" );
   if( f( x, a, b ) + f( x, c, d ) == 2 ) printf( "both\n" );
}

int main( void ) {
   int A, B, C, D;
   scanf( "%d%d%d%d", &A, &B, &C, &D );

   int P, M, G;
   scanf( "%d%d%d", &P, &M, &G );

   solve( P, A, B, C, D );
   solve( M, A, B, C, D );
   solve( G, A, B, C, D );

   return 0;
}
