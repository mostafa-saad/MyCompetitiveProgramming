#include <cstdio>
#include <cstring>

typedef long long llint;

const int dr[4] = { 0, 1, 0, -1 }; 
const int dc[4] = { 1, 0, -1, 0 };

int N, K, M;
char a[200][200][8];
llint bio[200][200][4][8];
int skret[200][200][4][8];

int main( void ) {
   scanf( "%d%d", &N, &K );

   memset( a, sizeof a, 'S' );

   scanf( "%d", &M );
   for( int i = 0; i < M; ++i ) {
      int r, c;
      scanf( "%d%d", &r, &c ); --r; --c;
      scanf( "%s", a[r][c] );
   }

   llint ret = 0;
   int r = 0, c = 0, d = 0, t = 0, k = 0;

   for( ;; ) {
      if( a[r][c][t] == 'L' ) d = (d+3)%4, ++k;
      if( a[r][c][t] == 'R' ) d = (d+1)%4, ++k;

      if( r + dr[d] < 0 || r + dr[d] >= N ||
          c + dc[d] < 0 || c + dc[d] >= N ) d = (d+2)%4, ++k;
      
      if( bio[r][c][d][t] > 0 ) {
         int ciklus = k-skret[r][c][d][t];
         int left = K-k;         
         
         ret += (left/ciklus) * (ret - bio[r][c][d][t]);
         k += (left/ciklus) * ciklus;
      }
      bio[r][c][d][t] = ret;
      skret[r][c][d][t] = k;

      if( k >= K ) break;

      r += dr[d];
      c += dc[d];
      ++ret;
      if( ++t == 7 ) t = 0;
   }
   
   printf( "%lld\n", ret );

   return 0;
}
   
