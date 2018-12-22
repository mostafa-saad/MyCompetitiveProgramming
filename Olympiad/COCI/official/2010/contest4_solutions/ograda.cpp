#include <cstdio>
#include <cstring>
#include <ctime>

#include <functional>
using namespace std;

const int MAXN = 1100100;
const int MAXX = 1000100;
const int oo = 10001001;

template< typename T > class monotone_queue {
  int value[ MAXX ], index[ MAXX ];
  T comp;
  int head, tail;
  
public:
  monotone_queue( void ) : head( 0 ), tail( -1 ) {}

  void push( int val, int ind ) {
    while( head <= tail && comp( value[ tail ], val ) ) --tail;
    ++tail;
    value[ tail ] = val;
    index[ tail ] = ind;
  }

  int pop( int ind ) {
    if( head > tail ) return -1;
    if( index[ head ] == ind ) return value[ head++ ];
    return -1;
  }

  int top( void )   { return value[ head ]; }
};

int visine[ MAXN ];
int nove_visine[ MAXN ];
int opalio[ MAXN ];

int n, m, x;
monotone_queue< greater< int > > Q;
monotone_queue< less< int > > Q2;

int main( void ) {
  scanf( "%d%d", &n, &x );

  for( int i = 0; i < n; ++i )
    scanf( "%d", visine+i );

  for( int i = 0; i < x; ++i ) 
    visine[n+i] = oo;

  for( int i = 0; i < n+x; Q.push( visine[i], i ), ++i ) { 
    if( i < x ) continue;
    nove_visine[i-x] = Q.top();
    Q.pop( i-x );
  }
  
  long long cetkicom = 0;
  
  for( int i = 0; i < n; ++i ) {
    if( i <= n-x ) Q2.push( nove_visine[i], i );
    if( x <= i )   Q2.pop( i-x );
    
    cetkicom = cetkicom + visine[i] - Q2.top();
    opalio[ i ]= Q2.top();
  }
  
  int zadnja_visina = -1;
  int do_kuda = -1;
  int poteza = 0;
  
  for( int i = 0; i < n; ++i ) 
    if( opalio[i] != zadnja_visina || do_kuda < i ) {
      ++poteza;
      zadnja_visina = opalio[i];
      do_kuda = i+x-1;
    }
  
  printf( "%lld\n%d\n", cetkicom, poteza );
  
  fprintf( stderr, "TIME:: %.3lfs\n", clock() / (double)CLOCKS_PER_SEC );
  return 0;
}
