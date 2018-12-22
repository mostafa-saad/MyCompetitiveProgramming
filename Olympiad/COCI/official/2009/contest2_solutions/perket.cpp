#include <cstdio>

#define MAXN 10

int n, k[MAXN], g[MAXN], best = 1000000000;

int diff( int x, int y ) { return x<y ? y-x : x-y; }

void rek( int i, int kis, int gor ) {
   if( i == n ) {
      if( gor > 0 && diff(kis,gor) < best ) best = diff(kis,gor);
   } else {
      rek( i+1, kis, gor );
      rek( i+1, kis*k[i], gor+g[i] );
   }
}

int main(void) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) scanf( "%d%d", &k[i], &g[i] );

   rek( 0, 1, 0 );

   printf( "%d\n", best );
   return 0;
}
