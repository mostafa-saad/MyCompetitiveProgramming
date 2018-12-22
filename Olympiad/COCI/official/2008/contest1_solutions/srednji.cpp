#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>

using namespace std;

int n, b;
int x, delta;

int main( void ) {
   scanf( "%d%d", &n, &b );

   vector<int> a( n );
   for( int i = 0; i < n; ++i ) scanf( "%d", &a[i] );

   x = distance( a.begin(), find( a.begin(), a.end(), b ) );

   delta = 0;
   vector<int> L( 2*n+1, 0 );
   for( int i = x; i >= 0; --i ) {
      delta += (a[i] < a[x]) ? -1 : (a[i] > a[x] ) ? 1 : 0;
      L[n+delta] += 1;
   }

   delta = 0;
   vector<int> R( 2*n+1, 0 );
   for( int i = x; i < n; ++i ) {
      delta += (a[i] < a[x]) ? -1 : (a[i] > a[x] ) ? 1 : 0;
      R[n+delta] += 1;
   }

   int ret = 0;
   for( delta = -n; delta <= n; ++delta )
      ret += L[n+delta] * R[n-delta];
   printf( "%d\n", ret );
   
   return 0;
}
