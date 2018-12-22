#include <cstdio>
#include <cstring>
const int NULA = 0;
const int MAXN = 365;
const int MOD = 360;

int n, k, q;
int dp[ MAXN ];
int ciklus[ MAXN ];
int kutovi[ 10 ];

int main( void ) {
  scanf( "%d%d", &n, &q ); 
  for( int i = 0; i < n; ++i ) {
    scanf( "%d", kutovi+i );
    kutovi[i] %= MOD;
  }

  dp[0] = 1;

  for( int i = 0; i < n; ++i ) {
    memset( ciklus, 0, sizeof( ciklus ) ); 

    for( int sad = 0; !ciklus[ sad ]; ( sad += kutovi[i] ) %= MOD )
      ciklus[ sad ] = 1;

    for( int j = 0; j < MOD; ++j ) {
      if( dp[j] == 0 ) continue;
      for( int k = 0; k < MOD; ++k ) {
        dp[ ( j + k ) % MOD ]       |= ciklus[ k ];
        dp[ ( j - k + MOD ) % MOD ] |= ciklus[ k ];
      }
    }
  }
  
  for( int i = 0; i < q; ++i ) {
    scanf( "%d", &k );
    k %= MOD;
    puts( dp[ k ] ? "da" : "NE" );
  }


  // for( int i = 0; i < MOD; ++i )
  //   printf( "%d", dp[i] );
  
  return NULA;
}


