
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 3 - Task NPUZZLE
  Programming language C++
*/

#include <cstdio>

char a[4][5];
char b[4][5] = { "ABCD", "EFGH", "IJKL", "MNO#" };

int abs( int x ) { return x < 0 ? -x : x; }

int main( void ) {
   for( int r = 0; r < 4; ++r ) scanf( "%s", a[r] );

   int razbacanost = 0;

   for( int r1 = 0; r1 < 4; ++r1 )
      for( int s1 = 0; s1 < 4; ++s1 )
         for( int r2 = 0; r2 < 4; ++r2 )
            for( int s2 = 0; s2 < 4; ++s2 )
               if( a[r1][s1] == b[r2][s2] )
                  razbacanost += abs(r2-r1) + abs(s2-s1);

   printf( "%d\n", razbacanost );

   return 0;
}
