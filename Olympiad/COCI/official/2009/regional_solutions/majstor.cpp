#include <cstdio>

#define MAXN 50
#define MAXR 50

int N, R;
char Sven[MAXR+1];
char prijatelj[MAXN][MAXR+1];

int bodovi( int runda, char sven ) {
   int ret = 0;
   for( int i = 0; i < N; ++i ) {
      if( sven == prijatelj[i][runda] ) ret += 1;

      if( sven == 'S' && prijatelj[i][runda] == 'P' ) ret += 2;
      if( sven == 'P' && prijatelj[i][runda] == 'K' ) ret += 2;
      if( sven == 'K' && prijatelj[i][runda] == 'S' ) ret += 2;
   }
   return ret;
}

int max( int a, int b, int c ) { 
   if( a >= b && a >= c ) return a;
   if( b >= a && b >= c ) return b;
   return c;
}

int main( void ) {
   scanf( "%d", &R );
   scanf( "%s", Sven );
   scanf( "%d", &N );
   for( int i = 0; i < N; ++i ) scanf( "%s", prijatelj[i] );

   int A = 0, B = 0;
   for( int r = 0; r < R; ++r ) {
      A += bodovi( r, Sven[r] );
      B += max( bodovi( r, 'S' ), bodovi( r, 'P' ), bodovi( r, 'K' ) );
   }

   printf( "%d\n", A );
   printf( "%d\n", B );
   return 0;
}
