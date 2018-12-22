#include <cstdio>
#include <cstring>

typedef long long llint;
const llint mod = 1000000007;

#define MAXI 20

int N, M, I;
int igracka;

llint a[ 1 << MAXI ];

llint modpow2( llint deg ) {
  llint bp = 2, p = 1;
  for( int i = 0; ( 1LL << i ) <= deg; ++i ) {
    if( ( ( deg >> i ) & 1 ) == 1 ) p = ( p * bp ) % mod;
    bp = ( bp * bp ) % mod;
  }
  return p;
}

void solve( int lo, int hi ) {
  if( lo + 1 == hi ) {
    a[lo] = modpow2( a[lo] );
    return;
  }

  int mid = ( lo + hi ) >> 1;

  for( int i = lo; i < mid; ++i ) 
    a[mid + i - lo] += a[i];

  solve( lo, mid );
  solve( mid, hi );

  for( int i = lo; i < mid; ++i ) {
    a[mid + i - lo] -= a[i];
    if( a[mid + i - lo] < 0 ) a[mid + i - lo] += mod;
  }
}

int main( void )
{
  scanf( "%d%d", &N, &M );

  for( int i = 0; i < N; ++i ) {
    scanf( "%d", &I );

    int cmask = 0;

    for( int j = 0; j < I; ++j ) {
      scanf( "%d", &igracka ); --igracka;
      cmask |= ( 1 << igracka );
    }

    ++a[cmask];
  }

  solve( 0, 1 << MAXI );
  printf( "%lld\n", a[( 1 << M ) - 1] );

  return 0;
}
