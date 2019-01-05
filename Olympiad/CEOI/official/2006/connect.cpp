#include <cstdio>
#include <cstring>

using namespace std;

#define MAXN 12
#define MAXM 39

int n, m;
char a[2*MAXN+1][2*MAXM+2];
int how[MAXN][MAXM];
short memo[MAXN][MAXM][1<<MAXN][2];
const short inf = 10000;

char *b[3][11] = {
   { "# #", "# #", "#.#", "# #", "# #", "# #", "#.#", "#.#", "#.#", "# #", "# #" },
   { "   ", ".X ", " X ", " X.", " X ", "...", " . ", ".. ", " ..", " ..", ".. " },
   { "# #", "# #", "# #", "# #", "#.#", "# #", "#.#", "# #", "# #", "#.#", "#.#" },
};

short rec( int r, int c, int mask, int U, int reconstruct ) {
   if( r == n ) return rec( 0, c+1, mask, 0, reconstruct );
   if( c == m ) return 0;

   short &ret = memo[r][c][mask][U];
   if( !reconstruct && ret >= 0 ) return ret;

   ret = inf;

   int L = (mask>>r)&1;
   int R = a[2*r+1][2*c+2] == ' ';
   int D = a[2*r+2][2*c+1] == ' ';
   int X = a[2*r+1][2*c+1] == 'X';

   int h0=0, h1=0, h2=0, h3=0;

   #define tst(t0,t1,t2,t3) { \
      int v = t1 + rec( r+1, c, t2, t3, 0 ); \
      if( v < ret ) { ret = v; h0=t0; h1=t1; h2=t2; h3=t3; } \
   }

   if( !X && !L && !U && 1 && 1 ) tst(  0, 0, mask & ~(1<<r), 0 ); // empty

   if(  X &&  L && !U && 1 && 1 ) tst(  1, 1, mask & ~(1<<r), 0 ); // left
   if(  X && !L &&  U && 1 && 1 ) tst(  2, 1, mask & ~(1<<r), 0 ); // up
   if(  X && !L && !U && R && 1 ) tst(  3, 1, mask |  (1<<r), 0 ); // right
   if(  X && !L && !U && 1 && D ) tst(  4, 1, mask & ~(1<<r), 1 ); // down

   if( !X &&  L && !U && R && 1 ) tst(  5, 2, mask |  (1<<r), 0 ); // left-right
   if( !X && !L &&  U && 1 && D ) tst(  6, 2, mask & ~(1<<r), 1 ); // up-down

   if( !X &&  L &&  U && 1 && 1 ) tst(  7, 2, mask & ~(1<<r), 0 ); // left-up
   if( !X && !L &&  U && R && 1 ) tst(  8, 2, mask |  (1<<r), 0 ); // up-right
   if( !X && !L && !U && R && D ) tst(  9, 2, mask |  (1<<r), 1 ); // right-down
   if( !X &&  L && !U && 1 && D ) tst( 10, 2, mask & ~(1<<r), 1 ); // down-left

   if( reconstruct ) {
      how[r][c] = h0;
      rec( r+1, c, h2, h3, 1 );
   }

   return ret;
}

int main( void ) {
   scanf( "%d%d ", &n, &m );
   for( int r = 0; r < n; ++r ) gets( a[r] );
   n /= 2; m /= 2;

   memset( memo, -1, sizeof memo );
   printf( "%d\n", rec( 0, 0, 0, 0, 1 ) );

   for( int r = 0; r < n; ++r )
      for( int c = 0; c < m; ++c )
         for( int dr = 0; dr < 3; ++dr )
            for( int dc = 0; dc < 3; ++dc )
               if( b[dr][how[r][c]][dc] != ' ' )
                  a[2*r+dr][2*c+dc] = b[dr][how[r][c]][dc];

   for( int r = 0; r <= 2*n; ++r ) puts( a[r] );
   return 0;
}
