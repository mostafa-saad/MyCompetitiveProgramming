#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long llint;

const int MAX = 100100;
const int mod = 1000000007;

int n;
llint a[MAX];
llint b[MAX];

int main( void ) {
  scanf( "%d", &n );
  for( int i = 1; i <= n; ++i ) scanf( "%lld", &a[i] );
  for( int i = 1; i <  n; ++i ) scanf( "%lld", &b[i] );

  llint x = 1, y = 0;
  for( int i = 1; i <= n; ++i ) {
    llint xx = ( x*a[i] + x*b[i-1] + y*a[i] + y*(b[i-1]-1) ) % mod;
    llint yy = ( x*b[i] + y*b[i] ) % mod;
    x = xx, y = yy;
  }
  printf( "%lld\n", x );

  return 0;
}

