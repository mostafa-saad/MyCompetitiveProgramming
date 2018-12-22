#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

typedef long long llint;

const int mod = 1000000000;

map< int, int > A, B;

void ucitaj( map< int, int > &M ) {
  int n, x;
  scanf( "%d", &n );
  for( int i = 0; i < n; ++i ) {
    scanf( "%d", &x );
    for( int j = 2; j*j <= x; ++j )
      while( x%j == 0 ) x /= j, M[j]++;
    if( x > 1 ) M[x]++;
  }
}

int main( void ) {
  ucitaj( A );
  ucitaj( B );
  
  llint ans = 1;
  bool vise = false;

  for( map< int, int > :: iterator it = A.begin(); it != A.end(); ++it )
    if( B.count( it->first ) ) {
      int p = it->first;
      int r = min( A[p], B[p] );
  
      for( int i = 0; i < r; ++i ) {
	ans = ans * p;
	if( ans >= mod ) ans %= mod, vise = true;
      }
    }
  
  if( vise ) printf( "%09d\n", (int)ans ); else
    printf( "%d\n", (int)ans );
  return 0;
}
