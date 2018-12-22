#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long llint;

const int K = 20;

int c[K];

int main( void ) {
  int n, x;
  scanf( "%d", &n );
  for( int i = 0; i < n; ++i ) {
    scanf( "%d", &x );
    for( int j = 0; j < K; ++j )
      if( x&(1<<j) ) c[j]++;
  }

  llint ans = 0;
  for( int i = 0; i < K; ++i )
    ans += llint( c[i] )*( n-c[i] )*(1<<i);

  printf( "%lld\n", ans );
  return 0;
}
