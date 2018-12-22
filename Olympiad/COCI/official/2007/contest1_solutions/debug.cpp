
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 1 - Task DEBUG
  Programming language C++
*/

#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long llint;

int n, m;
char a[300][300+1];
llint mask[302][302][4]; // pamti 64 bita od pozicije (r,s) u smjeru d

const int dr[4] = { 1, 0, -1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

// inicijalizira mask[r][c][d]
void init() {
   for( int r = n-1; r >= 0; --r ) {
      for( int c = m-1; c >= 0; --c ) {
         for( int d = 0; d < 2; ++d ) {
            int rr = r+dr[d];
            int cc = c+dc[d];

            if( rr >= 0 && rr < n && cc >= 0 && cc < m )
               mask[r][c][d] = mask[rr][cc][d]<<1;
            else
               mask[r][c][d] = 0;

            mask[r][c][d] |= a[r][c]=='1';
         }
      }
   }
   for( int r = 0; r < n; ++r ) {
      for( int c = 0; c < m; ++c ) {
         for( int d = 2; d < 4; ++d ) {
            int rr = r+dr[d];
            int cc = c+dc[d];

            if( rr >= 0 && rr < n && cc >= 0 && cc < m )
               mask[r][c][d] = mask[rr][cc][d]<<1;
            else
               mask[r][c][d] = 0;

            mask[r][c][d] |= a[r][c]=='1';
         }
      }
   }
}

// provjerava je li okvir (r,c) (r+size,c+size) ok
int check( int r, int c, int size ) {
   if( r < 0 || r+size >= n ) return 0;
   if( c < 0 || c+size >= m ) return 0;

   for( int d = 0; d < 2; ++d ) {
      int r1 = r, c1 = c;
      int r2 = r+size, c2 = c+size;

      for( int s = size+1; s > 0; s -= 64 ) {
         llint x = mask[r1][c1][d];
         llint y = mask[r2][c2][d+2];

         if( s >= 64 ) {
            if( x^y ) return 0;
         } else {
            if( (x^y) & ((1LL<<s)-1) ) return 0;
         }

         r1 += 64*dr[d]; c1 += 64*dc[d];
         r2 -= 64*dr[d]; c2 -= 64*dc[d];
      }
   }

   return 1;
}

int main( void ) {
   scanf( "%d%d", &n, &m );
   for( int r = 0; r < n; ++r ) scanf( "%s", a[r] );

   init();

   int ret = 0;

   for( int r = 0; r < n; ++r ) {
      for( int c = 0; c < m; ++c )
         for( int x = 0; x < 2; ++x ) {
            int max_odavde = min( min( r+1, c+1 ), min( n-r, m-c ) );
            if ( 2*max_odavde+x <= ret ) {
               // Nema smisla pokusavati se siriti iz ovog polja jer je
               // najveci moguci kvadrat nije vec vec nadenog ubojice
               continue;
            }

            int size = x;
            while( check( r-size/2, c-size/2, size ) )
               size += 2;

            ret >?= size-1;
         }


   }

   if ( ret > 1 )
      printf( "%d\n", ret );
   else
      printf( "-1\n" );

   return 0;
}
