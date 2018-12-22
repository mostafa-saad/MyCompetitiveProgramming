#include <cstdio>

int n;
int x[100000], y[100000];
int freqX[100001], freqY[100001];

int main( void ) {
   scanf( "%d", &n );

   for( int i = 0; i < n; ++i ) {
      scanf( "%d%d", &x[i], &y[i] );
      ++freqX[ x[i] ];
      ++freqY[ y[i] ];
   }

   long long ret = 0;
   for( int i = 0; i < n; ++i )
      ret += (freqX[ x[i] ] - 1LL) * (freqY[ y[i] ] - 1LL);

   printf( "%lld\n", ret );

   return 0;
}
