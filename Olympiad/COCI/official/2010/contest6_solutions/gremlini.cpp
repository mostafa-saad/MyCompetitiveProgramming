#include <algorithm>
#include <cstdio>

using namespace std;
typedef long long llint;
const llint oo = 1000000000000000000LL;

inline llint add( llint a, llint b ) { return min( a+b, oo ); }

#define MAX 100

int N;
llint T;
int K[MAX], Y[MAX];
int A[MAX][1000];
int B[MAX][1000];

llint M[50][MAX][MAX];

llint curr[MAX], next[MAX];

int main( void ) {
   scanf( "%d%lld", &N, &T );
   for( int i = 0; i < N; ++i ) {
      scanf( "%d%d", &K[i], &Y[i] );
      for( int j = 0; j < K[i]; ++j ) scanf( "%d", &A[i][j] );
      for( int j = 0; j < K[i]; ++j ) scanf( "%d", &B[i][j] );
   }

   for( int p = 0; (1LL << p) <= T; ++p )
      for( int i = 0; i < N; ++i ) 
         for( int j = 0; j < N; ++j ) 
            M[p][i][j] = oo;

   for( int i = 0; i < N; ++i ) {
      for( int j = 0; j < K[i]; ++j ) {
         int a = A[i][j]-1;
         int b = B[i][j];
         M[0][a][i] = min( M[0][a][i], add( Y[i], b ) ); 
      }
   }

   int p = 0;
   for( ++p; (1LL << p) <= T; ++p )
      for( int i = 0; i < N; ++i ) 
         for( int j = 0; j < N; ++j ) 
            for( int k = 0; k < N; ++k ) 
               M[p][i][j] = min( M[p][i][j], add( M[p-1][i][k], M[p-1][k][j] ) );

   llint ret = 0;
   for( --p; p >= 0; --p ) {
      for( int i = 0; i < N; ++i ) next[i] = oo;
      
      for( int i = 0; i < N; ++i ) 
         for( int j = 0; j < N; ++j ) 
            next[i] = min( next[i], add( curr[j], M[p][i][j] ) );

      if( *min_element( next, next+N ) <= T ) {
         ret += (1LL << p);
         for( int i = 0; i < N; ++i ) curr[i] = next[i];
      }
   }
   printf( "%lld\n", ret );
   
   return 0;
}
