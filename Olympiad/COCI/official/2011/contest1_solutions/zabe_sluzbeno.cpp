#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int cur[100];
int end[100];

int gcd( int a, int b ) {
  while( a && b )
    if( a >= b ) a %= b;
    else b %= a;
  return a+b;
}

int find( int *niz, int a ) {
  for( int i = 0; i < n; ++i )
    if( niz[i] == a ) return i;
  return -1;
}

int dist( int *niz, int a, int b ) {
  int x = find( niz, a ), y = find( niz, b );
  return (y-x+n)%n;
}

void skoci( int x ) {
  printf( "%d\n", x );
  int p = find( cur, x );
  for( int i = 0; i < x; ++i, p = (p+1)%n )
    swap( cur[p], cur[(p+1)%n] );
}

int main( void ) {
  scanf( "%d", &n );
  for( int i = 0; i < n; ++i ) scanf( "%d", &cur[i] );
  for( int i = 0; i < n; ++i ) scanf( "%d", &end[i] );

  for( int t = n-3; t >= 1; --t ) {
    int x = t+1;
    for( int i = t+1; i <= n-1; ++i )
      if( dist( end, t, i ) < dist( end, t, x ) ) x = i;

    int g = gcd( n-1, t );
    for( ; g != 1; ) {
      int d = dist( cur, t, x ) - 1;
      if( d%g == 0 ) break;
      for( ; dist( cur, t, 1 ) != 1; skoci( 1 ) );
      skoci( t );
    }
    for( ; dist( cur, t, x ) != 1; skoci( t ) );
  }
  for( ; dist( cur, 1, n ) != dist( end, 1, n ); skoci( n ) );

  return 0;
}

