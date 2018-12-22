#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long llint;

int n, m;
int zeli[1<<17];

int main( void ) {
  scanf( "%d %d", &m, &n );
  llint sum = -m;
  for( int i = 0; i < n; ++i ) {
    scanf( "%d", &zeli[i] );
    sum += zeli[i];
  }
  sort( zeli, zeli+n );

  llint ans = 0;
  for( int i = 0; i < n; ++i ) {
    llint w = min( 1LL*zeli[i], sum/(n-i) );
    ans += w*w;
    sum -= w;
  }
  printf( "%lld\n", ans );

  return 0;
}

