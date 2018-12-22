
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 4 - Task SKENER
  Programming language C++
*/

#include <cstdio>

#define maxr 50

int r, s, zoomr, zooms;
char grid[maxr][maxr+1];

int main(void) {
   scanf( "%d%d%d%d", &r, &s, &zoomr, &zooms );
   for( int i = 0; i < r; i++ ) scanf( "%s", grid[i] );
   for( int i = 0; i < r*zoomr; i++ ) {
      for( int j = 0; j < s*zooms; j++ ) printf( "%c", grid[i/zoomr][j/zooms] );
      printf( "\n" );
   }
   return 0;
}
