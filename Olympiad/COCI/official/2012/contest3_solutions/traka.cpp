#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;
typedef long long llint;

#define MAXM 100005
#define MAXN 500005

int M, N;
int T[ MAXM ];
int F[ MAXN ];

struct pravac {
  llint k, l;

  pravac() {}
  pravac( llint K, llint L ) { k = K; l = L; }

  llint plugin( llint F1, llint F2 ) {
    return F1 * k + F2 * l;
  }
};

vector< pravac > p;
pravac h[ MAXM ];
int t;

bool operator<( pravac a, pravac b ) {
  if( a.k == b.k ) return ( a.l > b.l );
  return ( a.k < b.k );
}

llint ccw( pravac a, pravac b, pravac c ) {
  return a.k * ( b.l - c.l ) + b.k * ( c.l - a.l ) + c.k * ( a.l - b.l );
}

pravac query( llint F1, llint F2 ) {
  int lo = 0, hi = t-1, mid;

  while( lo < hi ) {
    mid = ( lo + hi ) >> 1;
    if( h[mid+1].plugin( F1, F2 ) > h[mid].plugin( F1, F2 ) ) lo = mid+1;
    else hi = mid;
  }

  return h[lo];
}

int main( void )
{
  scanf( "%d%d", &M, &N );

  for( int i = 0; i < M; ++i )
    scanf( "%d", T+i );

  for( int i = 0; i < N; ++i )
    scanf( "%d", F+i );

  llint last = 0;
  for( int i = 0; i < M; ++i ) {
    p.push_back( pravac( last + T[i], -last ) );
    last += T[i];
  }

  sort( p.begin(), p.end() );

  h[0] = p[0];
  h[1] = p[1];
  t = 2;

  for( int i = 2; i < M; ++i ) {
    while( t >= 2 && ccw( h[t-2], h[t-1], p[i] ) >= 0 ) {
      --t;
    }
    h[t++] = p[i];
  }

  llint Sol = (llint)last * F[N-1];
  for( int i = 1; i < N; ++i ) {
    pravac q = query( F[i-1], F[i] );
    Sol += q.k * F[i-1] + q.l * F[i];
  }

  printf( "%lld\n", Sol );

  return 0;
}
