#include <cstdio>

#define MAXN 1000

int n, k, sito[MAXN+1];

int solve() {
   for( int i = 2; i <= n; ++i ) {
      if( sito[i] ) continue;
      for( int j = i; j <= n; j += i ) {
         if( sito[j] ) continue;
         
         if( !--k ) return j;
         sito[j] = 1;
      }
   }
}

int main(void) {
   scanf( "%d%d", &n, &k );
   printf( "%d\n", solve() );
   return 0;
}
