#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

#define MAX 300000

int n, k, m;
int x[MAX+2];
int next[MAX+2];
int memo[MAX+2][2];
int sorted[MAX+2];
int a[MAX+2], b[MAX+2];

int rec( int i, int vrh, bool reconstruct ) {
   int j = vrh ? next[i] : i+1;
   int hi = vrh ? x[sorted[i]]+k-1 : x[sorted[i]];
   
   if( reconstruct ) {
      for( int t = i; t < j; ++t ) {
         a[sorted[t]] = hi-k+1;
         b[sorted[t]] = hi;
      }
   }
   if( j > m ) return 0;

   if( !reconstruct && memo[i][vrh] >= 0 ) return memo[i][vrh];   

   if( k + rec( j, 1, false ) < x[sorted[j]]-hi + rec( j, 0, false ) ) {
      memo[i][vrh] = k + rec( j, 1, reconstruct );
   } else {
      memo[i][vrh] = x[sorted[j]]-hi + rec( j, 0, reconstruct );
   }

   return memo[i][vrh];
}

bool cmp( int a, int b ) { return x[a] < x[b]; }

int main( void ) {
   scanf( "%d%d", &n, &k );
   scanf( "%d", &m );

   x[0] = -1000000000;
   for( int i = 1; i <= m; ++i ) 
      scanf( "%d", &x[i] );
   x[m+1] = 2000000000;

   for( int i = 0; i < m+2; ++i ) sorted[i] = i;
   sort( sorted, sorted+m+2, cmp );

   next[0] = 1;
   for( int i = 1; i <= m; ++i ) 
      for( next[i] = next[i-1]; x[sorted[next[i]]] - x[sorted[i]] < k; ++next[i] );

   memset( memo, -1, sizeof memo );

   printf( "%d\n", rec( 0, 0, true ) );
   for( int i = 1; i <= m; ++i ) {
      if( a[i] < 1 ) { a[i] = 1; b[i] = k; }
      if( b[i] > n ) { a[i] = n-k+1; b[i] = n; }
      printf( "%d %d\n", a[i], b[i] );
   }
   
   return 0;
}
