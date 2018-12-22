#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int a[1000], b[1000];

int sgn( int x ) {
  if( x < 0 ) return -1;
  if( x > 0 ) return +1;
  return 0;
}

int solve( int i, int j ) { 
  if( i == j ) return 0;

  int p = i;
  for( int k = i; k < j; ++k )
    if( abs(a[k]) < abs(a[p]) ) p = k;

  int w = a[p];
  for( int k = i; k < j; ++k ) a[k] -= w;
  return abs(w) + solve( i, p ) + solve( p+1, j );
}

int main( void ) {
  scanf( "%d", &n );
  for( int i = 0; i < n; ++i ) scanf( "%d", &a[i] );
  for( int i = 0; i < n; ++i ) scanf( "%d", &b[i] );
  for( int i = 0; i < n; ++i ) a[i] -= b[i];

  int ans = 0;
  for( int i = 0, j; i < n; i = j ) {
    for( j = i; j < n && sgn(a[i]) * sgn(a[j]) >= 0; ++j );
    ans += solve( i, j );
  }
  printf( "%d\n", ans );

  return 0;
}

