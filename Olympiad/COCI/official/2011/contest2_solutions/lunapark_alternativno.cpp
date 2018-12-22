#include <cstdio>
#include <algorithm>

using namespace std;

int R, C;
int zab[1000][1000];

void print( char c, int t = 1 ) {
  for( ; t > 0; --t )
    putchar( c );
}

int main( void ) {
  scanf( "%d %d", &R, &C );
  for( int i = 0; i < R; ++i )
    for( int j = 0; j < C; ++j )
      scanf( "%d", &zab[i][j] );

  if( R%2 == 1 ) {
    for( ; R >= 3; R -= 2 ) {
      print( 'R', C-1 );
      print( 'D' );
      print( 'L', C-1 );
      print( 'D' );
    }
    print( 'R', C-1 );
  }
  else if( C%2 == 1 ) {
    for( ; C >= 3; C -= 2 ) {
      print( 'D', R-1 );
      print( 'R' );
      print( 'U', R-1 );
      print( 'R' );
    }
    print( 'D', R-1 );
  }
  else {
    int x = 0, y = 1;
    for( int i = 0; i < R; ++i )
      for( int j = 0; j < C; ++j )
        if( (i+j)%2 && zab[i][j] < zab[x][y] )
          x = i, y = j;

    int r = 0;
    for( ; r+2 <= x; r += 2 ) {
      print( 'R', C-1 );
      print( 'D' );
      print( 'L', C-1 );
      print( 'D' );
    }

    int c = 0;
    for( ; c+1 < C; ++c ) {
      if( (r^1) != x || c != y ) print( "DU"[r%2] ), r ^= 1;
      print( 'R' );
    }
    if( r%2 == 0 ) print( 'D' ), ++r;

    if( r+1 < R ) {
      print( 'D' ), ++r;
      print( 'L', C-1 );
      print( 'D' ), ++r;

      for( ; r+1 < R; r += 2 ) {
        print( 'R', C-1 );
        print( 'D' );
        print( 'L', C-1 );
        print( 'D' );
      }
      print( 'R', C-1 );
    }
  }

  putchar( '\n' );
  return 0;
}

