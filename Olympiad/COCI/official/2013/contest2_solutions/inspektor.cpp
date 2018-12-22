#include <cstdio>
#include <algorithm>
#include <cstring>
 
using namespace std;
 
typedef long long llint;
typedef pair< int, llint > line;
#define k first
#define l second
 
const int MAXN = 101000;
const int SZ = 256; // bucket size
const llint inf = 2e18;
 
int time = 0;
 
struct bucket {
  line a[SZ];
  int c[SZ]; // lines sorted by k
  int b[SZ]; // envelope
  int m, p, cn;
  bucket() { m = p = cn = 0; }
 
  inline llint ccw( const line &a, const line &b, const line &c ) {
    return (a.k-b.k)*(a.l-c.l) - (a.k-c.k)*(a.l-b.l);
  }
  inline llint eval( const line &a ) { return a.k*llint(time) + a.l; }
  void sweep() {
    while( p+1 < m && eval( a[b[p]] ) < eval( a[b[p+1]] ) ) p++;
  }
  void update( int ind, line l ) {
    for( int i = 0; i < cn-1; ++i )
      if( c[i] == ind ) swap( c[i], c[i+1] );
    if( cn > 0 && c[cn-1] == ind ) cn--; // removing old line
    
    a[ind] = l;
    c[cn++] = ind;
    for( int i = cn-1; i > 0 && a[c[i]] < a[c[i-1]]; --i )
      swap( c[i], c[i-1] );
    
    m = p = 0;
    for( int i = 0; i < cn; ++i ) {
      while( m >= 2 && ccw( a[b[m-2]], a[b[m-1]], a[c[i]] ) >= 0 ) m--;
      b[m++] = c[i];
    }
  }
  llint getmax() {
    if( cn == 0 ) return -inf;
    sweep();
    return eval( a[b[p]] );
  }
} bk[1+MAXN/SZ];
 
int day[MAXN], profit[MAXN], start[MAXN];
 
inline llint calc( int k, int t ) {
  if( day[k] == 0 ) return -inf;
  return llint(t-day[k])*profit[k] + start[k];
}
 
int main( void ) {
  int n, m;
  scanf( "%d %d", &n, &m );
  for( int i = 0; i < m; ++i ) {
    int tip, t, k, z, s, a, b;
    scanf( "%d", &tip );
    
    if( tip == 1 ) {
      scanf( "%d %d %d %d", &t, &k, &z, &s );
      k--, time = t;
      day[k] = t, profit[k] = z, start[k] = s;
      bk[k/SZ].update( k%SZ, line( z, s - llint(t)*z ) );
    }
    if( tip == 2 ) {
      scanf( "%d %d %d", &t, &a, &b ); --a, --b;
      if( a > b ) swap( a, b );
      time = t;
      
      llint maks = -inf;
      
      while( a%SZ != 0 && a <= b ) maks = max( maks, calc( a, t ) ), a++;
      while( a+SZ-1 <= b ) maks = max( maks, bk[a/SZ].getmax() ), a += SZ;
      while( a <= b ) maks = max( maks, calc( a, t ) ), a++;
      
      if( maks == -inf ) printf( "nema\n" ); else
        printf( "%lld\n", maks );
    }
  }
  return 0;
}
