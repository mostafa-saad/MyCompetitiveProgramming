
/*
  Croatian Regional Competition in Informatics 2007
  Task TETRIS
  Programming language C++
*/

#include <cstdio>
#include <cstring>

using namespace std;

int S, T;
int h[100];

int check( char *a ) {
   int n = strlen( a );

   int ret = 0;
   for( int i = 0; i+n <= S; ++i ) {
      int ok = 1;
      for( int j = 0; j < n; ++j )
         if( a[j] - h[i+j] != a[0] - h[i] )
            ok = 0;
      if( ok ) ++ret;
   }
   return ret;
}

int main( void ) {

   scanf( "%d%d", &S, &T );
   for( int i = 0; i < S; ++i ) scanf( "%d", &h[i] );

   int ret = 0;
   if( T == 1 ) ret = check( "0" ) + check( "0000" );
   if( T == 2 ) ret = check( "00" );
   if( T == 3 ) ret = check( "001" ) + check( "10" );
   if( T == 4 ) ret = check( "100" ) + check( "01" );
   if( T == 5 ) ret = check( "000" ) + check( "01" ) + check( "101" ) + check( "10" );
   if( T == 6 ) ret = check( "000" ) + check( "00" ) + check( "011" ) + check( "20" );
   if( T == 7 ) ret = check( "000" ) + check( "00" ) + check( "110" ) + check( "02" );

   printf( "%d\n", ret );

   return 0;
}
