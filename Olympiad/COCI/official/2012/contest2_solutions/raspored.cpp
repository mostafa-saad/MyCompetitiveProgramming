#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long llint;

#define MAX 200005

int N, Q;
int f[ MAX ];
int T[ 2 * MAX ];
int D[ 2 * MAX ];
int I[ 2 * MAX ];

llint SolT, SolD;
vector< pair< int, int > > v;

struct logaritamska {
  llint t[ 2 * MAX ];

  void update( int x, int v ) {
    for( int i = x + 1; i < 2 * MAX; i += i&-i ) t[i] += v;
  }

  llint query( int x, int y ) {
    if( x > y ) return 0;
    llint ret = 0;
    for( int i = y + 1; i; i -= i&-i ) ret += t[i];
    for( int i = x;     i; i -= i&-i ) ret -= t[i];
    return ret;
  }
} p, s;

int pos( int idx ) { 
  return lower_bound( v.begin(), v.end(), make_pair( -T[idx], idx ) ) - v.begin();
}

void fix( int cpos, int idx, int sgn ) {
  SolT += sgn * llint( p.query( 0, cpos - 1 ) + 1 ) * T[idx];
  SolT += sgn * s.query( cpos + 1, N + Q - 1 );
  SolD += sgn * D[idx];

  p.update( cpos, sgn );
  s.update( cpos, sgn * T[idx] );
}

int main( void )
{
  scanf( "%d%d", &N, &Q );

  for( int i = 0; i < N; ++i ) {
    scanf( "%d%d", D+i, T+i );
    v.push_back( make_pair( -T[i], i ) );
  }

  for( int i = N; i < N+Q; ++i ) {
    scanf( "%d%d%d", I+i, D+i, T+i ); --I[i];
    v.push_back( make_pair( -T[i], i ) );
  }

  sort( v.begin(), v.end() );

  for( int i = 0; i < N; ++i ) {
    fix( pos( i ), i, +1 );
    f[i] = i;
  }

  printf( "%lld\n", SolD - SolT );

  for( int i = N; i < N+Q; ++i ) {
    fix( pos( f[I[i]] ), f[I[i]], -1 );
    fix( pos( i ), i, +1 );
    f[I[i]] = i;

    printf( "%lld\n", SolD - SolT );
  }

  return 0;
}
