
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 6 - Task MARATON
  Programming language C++
*/

#include <cstdio>

using namespace std;

int n;
char a[30][30+1];

const int dr[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dc[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int main( void ) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) scanf( "%s", a[i] );

   try {
      for( int r1 = 0; r1 < n; ++r1 )
         for( int c1 = 0; c1 < n; ++c1 )
            for( int d = 0; d < 8; ++d ) {
               if( a[r1][c1] == '.' ) continue;
               int r2 = r1 + dr[d], c2 = c1 + dc[d];
               int r3 = r2 + dr[d], c3 = c2 + dc[d];
               if( r3 < 0 || r3 >= n ) continue;
               if( c3 < 0 || c3 >= n ) continue;
               if( a[r1][c1] == a[r2][c2] && a[r2][c2] == a[r3][c3] ) throw a[r1][c1];
            }
      printf( "ongoing\n" );
   } catch( char c ) {
      printf( "%c\n", c );
   }
   return 0;
}
