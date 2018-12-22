
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 1 - Task OKVIRI
  Programming language C++
*/

#include <cstdio>
#include <cstring>
using namespace std;

char output[5][80];

int abs( int x ) { return x < 0 ? -x : x; }

void crtaj( char x, int c, char y ) {
   output[2][c] = x;
   for( int dr = -2; dr <= 2; ++dr )
      for( int dc = -2; dc <= 2; ++dc )
         if( abs(dr) + abs(dc) == 2 )
            output[2+dr][c+dc] = y;
}

int main( void ) {
   char s[16];
   scanf( "%s", s );

   int n = strlen( s );

   for( int r = 0; r < 5; ++r )
      for( int c = 0; c <= 4*n; ++c )
         output[r][c] = '.';

   for( int i = 0; i < n; ++i  ) crtaj( s[i], 4*i+2, '#' );
   for( int i = 2; i < n; i+=3 ) crtaj( s[i], 4*i+2, '*' );

   for( int r = 0; r < 5; ++r ) printf( "%s\n", output[r] );

   return 0;
}
