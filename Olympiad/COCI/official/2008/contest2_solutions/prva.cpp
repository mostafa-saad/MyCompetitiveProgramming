#include <cstdio>
#include <cstring>

#define MAX 20

int R, C;
char puzzle[MAX][MAX+1];

char solution[MAX+1] = "~";

int chars;
char word[MAX+1];

void append( char x ) {
   if( x != '#' ) {
      word[chars++] = x;
   } else {
      word[chars] = 0;
      if( chars >= 2 && strcmp( word, solution ) < 0 ) 
         strcpy( solution, word );
      chars = 0;
   } 
}

int main( void ) {
   scanf( "%d%d", &R, &C );
   for( int r = 0; r < R; ++r ) scanf( "%s", puzzle[r] );

   for( int r = 0; r < R; ++r ) {
      for( int c = 0; c < C; ++c ) 
         append( puzzle[r][c] );
      append( '#' );
   }

   for( int c = 0; c < C; ++c ) {
      for( int r = 0; r < R; ++r ) 
         append( puzzle[r][c] );
      append( '#' );
   }

   printf( "%s\n", solution );

   return 0;
}
